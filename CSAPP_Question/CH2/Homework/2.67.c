//2.67.c
//Function: The record of CS:APP Homework 2.67
/*
You are given the task of writing a procedure int_size_is_32() that yields 1
when run on a machine for which an int is 32 bits, and yields 0 otherwise. You are
not allowed to use the sizeof operator.
*/
//Author:   Godfrey
//Date:     2023/06/29

#include <stdio.h>

int int_size_is_32();

int int_size_is_32() {
    /* Set most significant bit (msb) of 32-bit machine */
    int set_msb = 1 << 31;
    /* Shift past msb of 32-bit word */
    //int beyond_msb = 1 << 32; <- This is bad, cause left shift >= width of type.
    int beyond_msb = set_msb << 1; //The better way, let set_msb left shift 1 bit.

    /*set_msb is nonzero when word size >= 32
      beyond_msb is zero when word size <= 32 */
    return set_msb && !beyond_msb;
}

int main() {
    printf("%d\n", int_size_is_32());
    return 0;
}