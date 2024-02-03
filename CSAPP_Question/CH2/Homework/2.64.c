//2.64.c
//Function: The record of CS:APP Homework 2.64
/*
Write code to implement the following function:
* Return 1 when any odd bit of x equals 1; 0 otherwise.
* Assume w=32
* int any_odd_one(unsigned x);
Your function should follow the bit-level integer coding rules (page 164),
except that you may assume that data type int has w = 32 bits.
*/
//Author:   Godfrey
//Date:     2023/06/28

#include <stdio.h>

int any_odd_one(unsigned x);

int any_odd_one(unsigned x) {
    unsigned mask = 0x55555555; /* 5 in binary is 0101, which is a good options to check odd one!*/
    return (mask & x) != 0; /* return if there is one or more than one that it has one on odd.
                               If there has no one on odd, it will return 0. */
}

int main() {
    printf("%d\n", any_odd_one(0xaaaaaaaa)); /* 0xa in binary is 1010 */
    printf("%d\n", any_odd_one(0x3)); /* 0x3 in binary is 0011 */
    return 0;
}