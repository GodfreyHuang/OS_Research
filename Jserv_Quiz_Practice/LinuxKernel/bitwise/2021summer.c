// Reference: https://hackmd.io/@sysprog/linux2021-summer-quiz

#include <stdio.h>
#include <stdint.h>
#include <unistd.h>
  
#define __DECLARE_ROTATE(bits, type)                   \
    static inline type rotl##bits(const type v, int c) \
    {                                                  \
        const int mask = (bits) - (1);                 \
        c &= mask;                                     \
                                                       \
        return (v << c) | v >> ((mask + 1) - c);                      \
    }                                                  \
                                                       \
    static inline type rotr##bits(const type v, int c) \
    {                                                  \
        const int mask = (bits) - (1);                 \
        c &= mask;                                     \
                                                       \
        return (v >> c) | v << ((mask + 1) - c);                      \
    }

#define DECLARE_ROTATE(bits) __DECLARE_ROTATE(bits, uint##bits##_t)

DECLARE_ROTATE(8);

static inline uintptr_t align_up(uintptr_t sz, size_t alignment);
void test_fork();

static inline uintptr_t align_up(uintptr_t sz, size_t alignment) {
    uintptr_t mask = alignment - 1;
    if((alignment & mask) == 0) {
        return (sz + mask) & (~mask);
    }
    return (((sz + mask) / alignment) * alignment);
}

// Reference: https://coolshell.cn/articles/7965.html
void test_fork() {
    //int count = 0;
    for(int i = 0; i < 2; i++) {
        fork();
        printf("-");
        //++count;
        fflush(stdout);
    }
    printf("\n");
    //printf("%d\n", count);

}

int main(int argc, const char * argv[]) {
    ///*
    //Alpha
    uint8_t getAnsL = rotl8(162, 3);
    printf("%u\n", getAnsL);
    uint8_t getAnsR = rotr8(162, 3);
    printf("%u\n", getAnsR);
    //Beta
    printf("%lu\n", align_up(120, 4));
    printf("%lu\n", align_up(121, 4));
    printf("%lu\n", align_up(122, 4));
    printf("%lu\n", align_up(123, 4));
    printf("%lu\n", align_up(125, 4));
    printf("%lu\n", align_up(126, 4));
    printf("%lu\n", align_up(127, 4));
    printf("%lu\n", align_up(128, 4));
    printf("%lu\n", align_up(129, 4));
    //*/
    //Gamma
    test_fork();
    
    return 0;
}
