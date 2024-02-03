/* A work-stealing scheduler is described in
 * Robert D. Blumofe, Christopher F. Joerg, Bradley C. Kuszmaul, Charles E.
 * Leiserson, Keith H. Randall, and Yuli Zhou. Cilk: An efficient multithreaded
 * runtime system. In Proceedings of the Fifth ACM SIGPLAN Symposium on
 * Principles and Practice of Parallel Programming (PPoPP), pages 207-216,
 * Santa Barbara, California, July 1995.
 * http://supertech.csail.mit.edu/papers/PPoPP95.pdf
 *
 * However, that refers to an outdated model of Cilk; an update appears in
 * the essential idea of work stealing mentioned in Leiserson and Platt,
 * Programming Parallel Applications in Cilk
 */

#include <assert.h>
#include <pthread.h>
#include <stdatomic.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

struct work_internal;

/* A 'task_t' represents a function pointer that accepts a pointer to a 'work_t'
 * struct as input and returns another 'work_t' struct as output. The input to
 * this function is always a pointer to the encompassing 'work_t' struct.
 *
 * It is worth considering whether to include information about the executing
 * thread's identifier when invoking the task. This information might be
 * beneficial for supporting thread-local accumulators in cases of commutative
 * reductions. Additionally, it could be useful to determine the destination
 * worker's queue for appending further tasks.
 *
 * The 'task_t' trampoline is responsible for delivering the subsequent unit of
 * work to be executed. It returns the next work item if it is prepared for
 * execution, or NULL if the task is not ready to proceed.
 *
 */

/*
 * “task_t”表示一個函數指標，該指標接受指向“work_t”結構的指標作為輸入，
 * 並返回另一個“work_t”結構作為輸出。此函數的輸入始終是指向包含work_t結構的指標。

 * 值得考慮在調用任務時是否包含有關執行線程標識子的資訊。此資訊可能有助於在交換約簡的情況下支援線程局部累加器。
 * 此外，確定目標工作人員的佇列以追加進一步任務可能很有用。

 * “task_t”指向中斷執行緒的記憶體位置(trampoline)負責交付後續要執行的工作單元。
 * 如果準備執行，則返回下一個工作項;如果任務尚未準備好繼續，則返回 NULL。

 * task_t是會送到CPU內執行的物件，work_t則將task_t包裝成可以執行work_t-stealing演算法的struct。單一個執行緒內可含有多個work_t。
 */
typedef struct work_internal *(*task_t)(struct work_internal *);

typedef struct work_internal {
    task_t code;
    atomic_int join_count;
    void *args[];
} work_t;

/* These are non-NULL pointers that will result in page faults under normal
 * circumstances, used to verify that nobody uses non-initialized entries.
 */
/* 下列為會造成page
 * faults的非NULL指標，用來確保沒有任何work_t會使用到非初始化的項目 */
static work_t *EMPTY = (work_t *) 0x100, *ABORT = (work_t *) 0x200;

/* work_t-stealing deque */
/* work_t組成的雙向隊列deque_t，用來執行work_t-stealing
 * 演算法。array_t是用來讓work_t可使用atomic */
typedef struct {
    atomic_size_t size;
    _Atomic work_t *buffer[];
} array_t;

typedef struct {
    /* Assume that they never overflow */
    atomic_size_t top,
        bottom;  // top等於目前已記錄的資料陣列第一筆資料的位置, bottom為最末
    _Atomic(array_t *) array;
} deque_t;

// 對deque_t內的top, bottom以及work_t陣列進行初始化
void init(deque_t *q, int size_hint)
{
    atomic_init(&q->top, 0);
    atomic_init(&q->bottom, 0);
    array_t *a = malloc(sizeof(array_t) + sizeof(work_t *) * size_hint);
    atomic_init(&a->size, size_hint);
    atomic_init(&q->array, a);
}

void resize(deque_t *q)
{
    array_t *a = atomic_load_explicit(
        &q->array, memory_order_relaxed);  //獲得&q->array內的數值
    size_t old_size = a->size;
    size_t new_size = old_size * 2;  //新的array大小直接給予原版2倍大小
    array_t *new = malloc(sizeof(array_t) +
                          sizeof(work_t *) * new_size);  //新開一個array_t
    atomic_init(&new->size, new_size);                   //初始化new
    size_t t = atomic_load_explicit(&q->top, memory_order_relaxed);
    size_t b = atomic_load_explicit(&q->bottom, memory_order_relaxed);
    for (size_t i = t; i < b; i++)
        new->buffer[i % new_size] =
            a->buffer[i % old_size];  //將a的內容搬移到new

    atomic_store_explicit(
        &q->array, new,
        memory_order_relaxed);  //把&q->array的數值存成new, a被捨棄
    /* The question arises as to the appropriate timing for releasing memory
     * associated with the previous array denoted by *a. In the original Chase
     * and Lev paper, this task was undertaken by the garbage collector, which
     * presumably possessed knowledge about ongoing steal operations by other
     * threads that might attempt to access data within the array.
     *
     * In our context, the responsible deallocation of *a cannot occur at this
     * point, as another thread could potentially be in the process of reading
     * from it. Thus, we opt to abstain from freeing *a in this context,
     * resulting in memory leakage. It is worth noting that our expansion
     * strategy for these queues involves consistent doubling of their size;
     * this design choice ensures that any leaked memory remains bounded by the
     * memory actively employed by the functional queues.
     */
    /* 在釋放*a與前一組陣列的記憶體之時間點時遭遇到問題，在論文內提及到此工作是由垃圾回收器來
       實作的，因垃圾回收器或可利用從執行緒獲得的陣列資料來知道執行緒正在執行的竊取動作。

       在此敘述中，因令一個執行緒可能在讀取*a的資料，所以我們不能回應*a的記憶體再分配。因此只能
       在此種情況放棄釋放*a的記憶體空間，從而導致記憶體洩漏。對記憶體的延伸策略是將其大小持續翻倍
       ，此設計選擇鵲報任何洩漏的記憶體都不會超出功能隊列使用的記憶體範圍。
    */
}

//取得work_t
work_t *take(deque_t *q)
{
    size_t b = atomic_load_explicit(&q->bottom, memory_order_relaxed) - 1;
    array_t *a = atomic_load_explicit(&q->array, memory_order_relaxed);
    atomic_store_explicit(&q->bottom, b,
                          memory_order_relaxed);  //將q內的bottom數值縮減
    atomic_thread_fence(memory_order_seq_cst);    //同步記憶體
    size_t t = atomic_load_explicit(&q->top, memory_order_relaxed);
    work_t *x;
    if (t <= b) {
        /* Non-empty queue */
        x = atomic_load_explicit(&a->buffer[b % a->size], memory_order_relaxed);
        if (t == b) {
            /* Single last element in queue */
            if (!atomic_compare_exchange_strong_explicit(
                    &q->top, &t, t + 1,  // AAAA = t + 1
                    memory_order_seq_cst, memory_order_relaxed))
                /* Failed race */
                x = EMPTY;
            atomic_store_explicit(&q->bottom, b + 1,
                                  memory_order_relaxed);  // BBBB = b + 1
        }
    } else { /* Empty queue */
        x = EMPTY;
        atomic_store_explicit(&q->bottom, b + 1,
                              memory_order_relaxed);  // CCCC = b + 1
    }
    return x;
}

//將w放進q
void push(deque_t *q, work_t *w)
{
    size_t b = atomic_load_explicit(&q->bottom, memory_order_relaxed);
    size_t t = atomic_load_explicit(&q->top, memory_order_acquire);
    array_t *a = atomic_load_explicit(&q->array, memory_order_relaxed);
    if (b - t > a->size - 1) { /* Full queue */
        resize(q);
        a = atomic_load_explicit(&q->array, memory_order_relaxed);
    }
    atomic_store_explicit(&a->buffer[b % a->size], w, memory_order_relaxed);
    atomic_thread_fence(memory_order_release);
    atomic_store_explicit(&q->bottom, b + 1,
                          memory_order_relaxed);  // DDDD = b + 1
}

//進行竊取行為
work_t *steal(deque_t *q)
{
    size_t t = atomic_load_explicit(&q->top, memory_order_acquire);
    atomic_thread_fence(memory_order_seq_cst);
    size_t b = atomic_load_explicit(&q->bottom, memory_order_acquire);
    work_t *x = EMPTY;
    if (t < b) {
        /* Non-empty queue */
        array_t *a = atomic_load_explicit(&q->array, memory_order_consume);
        x = atomic_load_explicit(&a->buffer[t % a->size], memory_order_relaxed);
        if (!atomic_compare_exchange_strong_explicit(
                &q->top, &t, t + 1, memory_order_seq_cst,
                memory_order_relaxed))  // EEEE = t + 1
            /* Failed race */
            return ABORT;
    }
    return x;
}

#define N_THREADS 24
deque_t *thread_queues;

atomic_bool done;

/* Returns the subsequent item available for processing, or NULL if no items
 * are remaining.
 */
static work_t *do_one_work(int id, work_t *work)
{
    printf("work item %d running item %p\n", id, work);
    return (*(work->code))(work);
}

void do_work(int id, work_t *work)
{
    while (work)
        work = do_one_work(id, work);
}

/* Returns the next item to be processed, or NULL if there are no remaining
 * items.
 */
work_t *join_work(work_t *work)
{
    int old_join_count = atomic_fetch_sub(&work->join_count, 1);
    if (old_join_count == 1)
        return work;
    return NULL;
}

//被pthread呼叫執行的程式
void *thread(void *payload)
{
    int id = *(int *) payload;
    deque_t *my_queue = &thread_queues[id];
    while (true) {
        work_t *work = take(my_queue);
        if (work != EMPTY) {
            do_work(id, work);
        } else {
            /* Currently, there is no work present in my own queue */
            work_t *stolen = EMPTY;
            for (int i = 0; i < N_THREADS; ++i) {
                if (i == id)
                    continue;
                stolen = steal(&thread_queues[i]);
                if (stolen == ABORT) {
                    i--;
                    continue; /* Try again at the same i */
                } else if (stolen == EMPTY)
                    continue;

                /* Found some work to do */
                break;
            }
            if (stolen == EMPTY) {
                /* Despite the previous observation of all queues being devoid
                 * of tasks during the last examination, there exists
                 * a possibility that additional work items have been introduced
                 * subsequently. To account for this scenario, a state of active
                 * waiting is adopted, wherein the program continues to loop
                 * until the global "done" flag becomes set, indicative of
                 * potential new work additions.
                 */
                if (atomic_load(&done))
                    break;
                continue;
            } else {
                do_work(id, stolen);
            }
        }
    }
    printf("work item %d finished\n", id);
    return NULL;
}

work_t *print_task(work_t *w)
{
    int *payload = (int *) w->args[0];
    int item = *payload;
    printf("Did item %p with payload %d\n", w, item);
    work_t *cont = (work_t *) w->args[1];
    free(payload);
    free(w);
    return join_work(cont);
}

work_t *done_task(work_t *w)
{
    free(w);
    atomic_store(&done, true);
    return NULL;
}

int main(int argc, char **argv)
{
    /* Check that top and bottom are 64-bit so they never overflow */
    static_assert(sizeof(atomic_size_t) == 8,
                  "Assume atomic_size_t is 8 byte wide");

    pthread_t threads[N_THREADS];
    int tids[N_THREADS];
    thread_queues = malloc(N_THREADS * sizeof(deque_t));
    int nprints = 10;

    atomic_store(&done, false);
    work_t *done_work = malloc(sizeof(work_t));
    done_work->code = &done_task;
    done_work->join_count = N_THREADS * nprints;

    for (int i = 0; i < N_THREADS; ++i) {
        tids[i] = i;
        init(&thread_queues[i], 8);
        for (int j = 0; j < nprints; ++j) {
            work_t *work = malloc(sizeof(work_t) + 2 * sizeof(int *));
            work->code = &print_task;
            work->join_count = 0;
            int *payload = malloc(sizeof(int));
            *payload = 1000 * i + j;
            work->args[0] = payload;
            work->args[1] = done_work;
            push(&thread_queues[i], work);
        }
    }

    for (int i = 0; i < N_THREADS; ++i) {
        if (pthread_create(&threads[i], NULL, thread, &tids[i]) != 0) {
            perror("Failed to start the thread");
            exit(EXIT_FAILURE);
        }
    }

    for (int i = 0; i < N_THREADS; ++i) {
        if (pthread_join(threads[i], NULL) != 0) {
            perror("Failed to join the thread");
            exit(EXIT_FAILURE);
        }
    }
    printf("Expect %d lines of output (including this one)\n",
           2 * N_THREADS * nprints + N_THREADS + 2);

    return 0;
}