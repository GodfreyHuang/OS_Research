#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>

typedef uint64_t ticks;
static inline ticks getticks(void)
{
    uint64_t result;
    uint32_t l, h, h2;
    asm volatile(
        "rdcycleh %0\n"
        "rdcycle %1\n"
        "rdcycleh %2\n"
        "sub %0, %0, %2\n"
        "seqz %0, %0\n"
        "sub %0, zero, %0\n"
        "and %1, %1, %0\n"
        : "=r"(h), "=r"(l), "=r"(h2));
    result = (((uint64_t) h) << 32) | ((uint64_t) l);
    return result;
}

uint16_t count_leading_zeros(uint64_t x)
{
    x |= (x >> 1);
    x |= (x >> 2);
    x |= (x >> 4);
    x |= (x >> 8);
    x |= (x >> 16);
    x |= (x >> 32);

    /* count ones (population count) */
    x -= ((x >> 1) & 0x5555555555555555);
    x = ((x >> 2) & 0x3333333333333333) + (x & 0x3333333333333333); // test1 = 20, test2 = 36
    x = ((x >> 4) + x) & 0x0f0f0f0f0f0f0f0f;                        // test1 = 5, test2 = 6
    //printf("x = %ld\n", x);
    x += (x >> 8);
    x += (x >> 16);
    x += (x >> 32);
    // printf("x = %ld\n", x);
    return (64 - (x & 0x7f));
}

int main(int argc, char *argv[])
{
    uint64_t testdata[] = {16, 33, 108};
    for(int i = 0; i < sizeof(testdata)/sizeof(uint64_t); ++i)
    {
        ticks t0 = getticks();
        uint64_t t = testdata[i];
        uint16_t clz = count_leading_zeros(t);
        printf("MSB: %d\n", 64 - clz);
        ticks t1 = getticks();
        printf("elapsed cycle: %" PRIu64 "\n", t1 - t0);    //cycle number
    }
    return 0;
}