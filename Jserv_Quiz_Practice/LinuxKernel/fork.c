#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

int main(void)
{
    for (int i = 0; i < 2; i++) {
        fork();
        printf("-\n");
        fflush(stdout);
        // printf("ppid=%d, pid=%d, i=%d\n", getppid(), getpid(), i);
    }
    // printf("\n");
    // sleep(10);
    // fflush(stdout);
    return 0;
}