// Using the command below to use futex:
// clang -std=c11 -Wall -g -O2 -D_GNU_SOURCE -fsanitize=thread -DUSE_LINUX
// test_pi.o -o test_pi -lpthread cc -std=c11 -Wall -g -O2 -D_GNU_SOURCE
// -fsanitize=thread -DUSE_LINUX pi.c -c -o test_pi.o -lpthread

/* originated from here:
 * https://github.com/qwe661234/MuThreadPackage/blob/main/Tests/test-04-priority-inversion-PI.c
 */

#include <pthread.h>
#include <sched.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "atomic.h"
#include "mutex.h"
//#include "muRemake.h"

#define THREADCOUNT 3

static pthread_mutex_t mutex_normal_1, mutex_normal_2;

/* Mutex attribute's protocol */
enum {
    TBTHREAD_PRIO_NONE,
    TBTHREAD_PRIO_INHERIT = 3,
    TBTHREAD_PRIO_PROTECT = 6,
};

/* Scheduler inheritance */
enum {
    TBTHREAD_INHERIT_SCHED,
    TBTHREAD_EXPLICIT_SCHED,
};

void TASK1()
{
    pthread_mutex_lock(&mutex_normal_1);
    printf("1\n");
    pthread_mutex_unlock(&mutex_normal_1);
}

void TASK2()
{
    pthread_mutex_lock(&mutex_normal_2);
    sleep(1);
    printf("2\n");
    pthread_mutex_unlock(&mutex_normal_2);
}

void TASK3()
{
    pthread_mutex_lock(&mutex_normal_1);
    sleep(1);
    printf("3\n");
    pthread_mutex_unlock(&mutex_normal_1);
}

static void (*TASKS[])() = {
    TASK1,
    TASK2,
    TASK3,
};

int main()
{
    int st;
    pthread_t th[THREADCOUNT];
    pthread_attr_t attr;
    pthread_mutexattr_t mattr;
    pthread_attr_init(&attr);
    struct sched_param param;

    pthread_mutexattr_setprotocol(&mattr, TBTHREAD_PRIO_INHERIT);
    pthread_mutex_init(&mutex_normal_1, &mattr);
    pthread_mutex_init(&mutex_normal_2, &mattr);
    pthread_attr_setschedpolicy(&attr, SCHED_FIFO);
    pthread_attr_setinheritsched(&attr, TBTHREAD_EXPLICIT_SCHED);

    for (int i = THREADCOUNT - 1; i >= 0; --i) {
        param.sched_priority = (THREADCOUNT - i) * 10;
        pthread_attr_setschedparam(&attr, &param);
        st = pthread_create(&th[i], &attr, (void *) TASKS[i], NULL);
        if (st != 0) {
            printf("Failed to spawn thread %d: %s\n", i, strerror(-st));
            return 1;
        }
        // pthread_join(&th[i], NULL);
    }

    // for (int i = THREADCOUNT - 1; i >= 0; --i) {
    //     st = pthread_join(&th[i], NULL);
    //     printf("st = %d\n", st);
    // }

    sleep(2);

    for (int i = THREADCOUNT - 1; i >= 0; --i) {
        st = pthread_join(th[i], NULL);
        printf("st = %d\n", st);
    }

    return 0;
}