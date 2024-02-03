//2.71.c
//Function: The record of CS:APP Homework 2.71
/*
/* Declaration of data type where 4 bytes are packed
into an unsigned */
//typedef unsigned packed_t;
/* Extract byte from word. Return as signed integer */
//int xbyte(packed_t word, int bytenum);
//Author:   Godfrey
//Date:     2023/07/03

#include <stdio.h>
#include <assert.h>

typedef unsigned packed_t;
int xbyte(packed_t word, int bytenum);

int xbyte(packed_t word, int bytenum) {
    //return (word >> (bytenum << 3)) & 0xFF;
    unsigned num = word >> (bytenum << 3) & 0xFF;
    int i = (sizeof(int) - 1) >> 3;
    num = num << i;
    return (int) num >> i;
}

int main() {
	unsigned x = 0xFF11;
	
	assert(xbyte(x, 0) == 0x11);
	assert(xbyte(x, 1) == -1); //this will cause dump!

    return 0;
}