//2.69.c
//Function: The record of CS:APP Homework 2.69
/*
* Do rotating left shift. Assume 0 <= n < w
* Examples when x = 0x12345678 and w = 32:
*
n=4 -> 0x23456781, n=20 -> 0x67812345
*/
//Author:   Godfrey
//Date:     2023/07/02

#include <stdio.h>
#include <assert.h>

unsigned rotate_left(unsigned x, int n);

unsigned rotate_left(unsigned x, int n) {
    int y = sizeof(int) << 3;  //Get the num 32.
    unsigned move = (unsigned)x >> (y - n); //x shift 32 - n bits. Just like the return value of 2.68
    return (x << n) + move; //0x12345678, 4 -> do x << n -> 0x23456780 -> do add move -> 0x23456780 + 0x00000001
                            // -> get ans 0x23456781
}

int main() {
	assert(rotate_left(0x12345678, 4) == 0x23456781);
	assert(rotate_left(0x12345678, 20) == 0x67812345);
    return 0;
}