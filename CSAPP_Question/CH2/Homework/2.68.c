//2.68.c
//Function: The record of CS:APP Homework 2.68
/*
* Mask with least signficant n bits set to 1
* Examples: n = 6 --> 0x3F, n = 17 --> 0x1FFFF
* Assume 1 <= n <= w
*/
//Author:   Godfrey
//Date:     2023/07/02

#include <stdio.h>
#include <assert.h>

int lower_one_mask(int n);

int lower_one_mask(int n) {
    int x = -1; // The mask of 0xFFFFFFFF.
    int y = sizeof(int) << 3; //Get the num 32.

    return (unsigned)x >> (y - n); //x shift 32 - n bits.
}

int main() {
	assert(lower_one_mask(6) == 0x3F);
	assert(lower_one_mask(17) == 0x1FFFF);

    return 0;
}