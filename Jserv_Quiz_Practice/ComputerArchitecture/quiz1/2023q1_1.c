//riscv64-unknown-elf-gcc -march=rv32i -mabi=ilp32 -S 2023q1_1.c -o 2023q1_1.s
//riscv64-unknown-elf-gcc -march=rv32i -mabi=ilp32 -o 2023q1_1.o 2023q1_1.c
//riscv64-unknown-elf-gcc -march=rv32i -mabi=ilp32 -o 2023q1_1.elf 2023q1_1.c
//riscv64-unknown-elf-objdump -d 2023q1_1.o > 2023q1_1dump.txt
#include <stdint.h>
#include <stdio.h>

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
    uint64_t test1 = 16;
    printf("%d\n", count_leading_zeros(test1)); // 59
    uint64_t test2 = 33;
    printf("%d\n", count_leading_zeros(test2)); // 58
    uint64_t test3 = 108;
    printf("%d\n", count_leading_zeros(test3)); // 57

    return 0;
}