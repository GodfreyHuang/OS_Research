//2.59.c
//Function: The record of CS:APP Homework 2.59 
//          Using function "make_new_word" to mask last two hex num
//Author:   Godfrey
//Date:     2023/06/13

#include <stdio.h>

#include "show_bytes.h"

int make_new_word(int x, int y);

int make_new_word(int x, int y) {
	int mask = 0xFF;
	return (~mask & y) | (mask & x); //Using "mask" and &, you can do the job.
}

int main() {
	printf("%#x\n", make_new_word(0x89ABCDEF, 0x76543210));
	return 0;
}