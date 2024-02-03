//2.70.c
//Function: The record of CS:APP Homework 2.70
/*
/*
* Return 1 when x can be represented as an n-bit, 2’s-complement
* number; 0 otherwise
* Assume 1 <= n <= w
*/
//Author:   Godfrey
//Date:     2023/07/02

#include <stdio.h>
#include <assert.h>

int fits_bits(int x, int n);

/* Test if x >> (n - 1) is in the range of -128 ~ 127 */
int fits_bits(int x, int n) {
    int pos = x >> (n - 1);
    int neg = pos;
    return pos == 0 || neg == -1;
}   

int main() {
	assert(fits_bits(1, 1) == 0);
	assert(fits_bits(-2, 2));
	assert(fits_bits(2, 3));
	assert(fits_bits(-130, 8) == 0);
	assert(fits_bits(-128, 8));
	assert(fits_bits(128, 8) == 0);
    assert(fits_bits(127, 8));

    return 0;
}