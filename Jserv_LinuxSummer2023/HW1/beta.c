#include <stdint.h>
#include <stdio.h>
#include <unistd.h>

static inline uintptr_t align_up(uintptr_t sz, size_t alignment);

static inline uintptr_t align_up(uintptr_t sz, size_t alignment)
{
    uintptr_t mask = alignment - 1;
    if ((alignment & mask) == 0) {
        return (sz + mask) & (~mask);  // MMMM = (sz + mask) & (~mask)
    }
    return (((sz + mask) / alignment) * alignment);
}

int main(int argc, const char *argv[])
{
    printf("%lu\n", align_up(120, 4));
    printf("%lu\n", align_up(121, 4));
    printf("%lu\n", align_up(122, 4));
    printf("%lu\n", align_up(123, 4));
    printf("%lu\n", align_up(125, 4));
    printf("%lu\n", align_up(126, 4));
    printf("%lu\n", align_up(127, 4));
    printf("%lu\n", align_up(128, 4));
    printf("%lu\n", align_up(129, 4));
    return 0;
}