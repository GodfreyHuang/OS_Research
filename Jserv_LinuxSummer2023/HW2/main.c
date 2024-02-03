#include <pthread.h>
#include <stdbool.h>
#include <stdlib.h>

#include "cond.h"
#include "futex.h"
#include "mutex.h"

//記錄mutex lock與condvar的結構
struct clock {
    mutex_t mutex;
    cond_t cond;
    int ticks;  //用int來記錄的"記號"
};

//初始化clock的設定
static void clock_init(struct clock *clock)
{
    mutex_init(&clock->mutex);
    cond_init(&clock->cond);
    clock->ticks = 0;  //"記號"預設為0
}

//將condvar設定成wait狀態, 回傳clock存的記號與輸入記號的比大小bool結果
static bool clock_wait(struct clock *clock, int ticks)
{
    mutex_lock(&clock->mutex);
    while (clock->ticks >= 0 && clock->ticks < ticks)
        cond_wait(&clock->cond, &clock->mutex);
    bool ret = clock->ticks >= ticks;
    mutex_unlock(&clock->mutex);
    return ret;
}

// clock的記號累加
static void clock_tick(struct clock *clock)
{
    mutex_lock(&clock->mutex);
    if (clock->ticks >= 0)
        ++clock->ticks;
    mutex_unlock(&clock->mutex);
    cond_broadcast(&clock->cond, &clock->mutex);
}

// clock記號設定成-1
static void clock_stop(struct clock *clock)
{
    mutex_lock(&clock->mutex);
    clock->ticks = -1;
    mutex_unlock(&clock->mutex);
    cond_broadcast(&clock->cond, &clock->mutex);
}

/* A node in a computation graph */
// 將clock包裝成linked-list使用的node結構
struct node {
    struct clock *clock;  // clock
    struct node *parent;  //上一個指向的node
    mutex_t mutex;        //存放atomic int的mutex_t結構
    cond_t cond;          //存放atomic int的cond_t結構
    bool ready;           //記錄是否於準備狀態的bool
};

//初始化node並將此node與輸入的parnet做連結
static void node_init(struct clock *clock,
                      struct node *parent,
                      struct node *node)
{
    node->clock = clock;
    node->parent = parent;
    mutex_init(&node->mutex);
    cond_init(&node->cond);
    node->ready = false;
}

//對list內的node下達wait並令其處於等待被執行的狀態
static void node_wait(struct node *node)
{
    mutex_lock(&node->mutex);
    while (!node->ready)
        cond_wait(&node->cond, &node->mutex);
    node->ready = false;
    mutex_unlock(&node->mutex);
}

//對list內的node下達signal開始執行
static void node_signal(struct node *node)
{
    mutex_lock(&node->mutex);
    node->ready = true;
    mutex_unlock(&node->mutex);
    cond_signal(&node->cond, &node->mutex);
}

//主要被pthread執行的函式
static void *thread_func(void *ptr)
{
    struct node *self = ptr;
    bool bit = false;

    for (int i = 1; clock_wait(self->clock, i); ++i) {
        if (self->parent)
            node_wait(self->parent);

        if (bit) {
            node_signal(self);  // true的話呼叫
        } else {
            clock_tick(self->clock);  //對指向的clock內的ticks進行操作
        }
        bit = !bit;  // bit會一直更改狀態, false <-> true循環往復
    }

    node_signal(self);
    return NULL;
}

//執行的主要測試程式
int main(void)
{
    struct clock clock;  //宣告並初始化clock
    clock_init(&clock);

#define N_NODES 16
    struct node nodes[N_NODES];  //宣告一個由node組成的單向linked-list
    node_init(&clock, NULL, &nodes[0]);  //先初始化head, parent指向NULL
    for (int i = 1; i < N_NODES; ++i)  //初始化除head以外的node並建立link
        node_init(&clock, &nodes[i - 1], &nodes[i]);

    pthread_t threads[N_NODES];  //建立pthread_t的thread pool
    for (
        int i = 0; i < N_NODES;
        ++i) {  //依序初始化pthread並讓每個node都被一個pthread包含進去且執行thread_func
        if (pthread_create(&threads[i], NULL, thread_func, &nodes[i]) != 0)
            return EXIT_FAILURE;  //如果建立失敗直接跳出錯誤
    }

    clock_tick(&clock);  //對clock的ticks進行累加操作
    clock_wait(&clock,
               1 << N_NODES);  //對clock操作wait, 並輸入8做為比較(1 << 16 = 8)
    clock_stop(&clock);  //將ticks設定成-1

    for (int i = 0; i < N_NODES; ++i) {
        if (pthread_join(threads[i], NULL) !=
            0)  //執行所有pthread的join, 收回每一個pthread
            return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}