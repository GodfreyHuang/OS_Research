//2.65.c
//Function: The record of CS:APP Homework 2.65
/*
Write code to implement the following function:
* Return 1 when x contains an odd number of 1s; 0 otherwise.
* Assume w=32 
* int odd_ones(unsigned x);
Your function should follow the bit-level integer coding rules (page 164),
except that you may assume that data type int has w = 32 bits.
Your code should contain a total of at most 12 arithmetic, bitwise, and logical
operations.
*/
//Author:   Godfrey
//Date:     2023/06/28

#include <stdio.h>

int odd_ones(unsigned x);

int odd_ones(unsigned x) {
    unsigned num = x >> 16;    /*shift logically*/
    printf("%.8x\n", num);
    x ^= x >> 16;
    printf("%.8x\n\n", x);

    num = x >> 8;
    printf("%.8x\n", num); 
    x ^= x >> 8;
    printf("%.8x\n\n", x);

    num = x >> 4;
    printf("%.8x\n", num); 
    x ^= x >> 4;
    printf("%.8x\n\n", x);

    num = x >> 2;
    printf("%.8x\n", num); 
    x ^= x >> 2;
    printf("%.8x\n\n", x);

    num = x >> 1;
    printf("%.8x\n", num); 
    x ^= x >> 1;
    printf("%.8x\n\n", x);

    return x & 0x1; /*check last hex num:
                        If last hex = xxx0. It will return 0; 1 otherwise.
                    */
}

int main() {
    printf("%d\n\n", odd_ones(0x01011111));
    printf("%d\n\n", odd_ones(0x01010100));
    return 0;
}