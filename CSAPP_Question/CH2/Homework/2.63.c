//2.63.c
//Function: The record of CS:APP Homework 2.63
/*
Fill in code for the following C functions. Function srl performs a logical right
shift using an arithmetic right shift (given by value xsra), followed by other oper-
ations not including right shifts or division. Function sra performs an arithmetic
right shift using a logical right shift (given by value xsrl), followed by other
operations not including right shifts or division. You may use the computation
8*sizeof(int) to determine w, the number of bits in data type int. The shift
amount k can range from 0 to w − 1.
*/
//Author:   Godfrey
//Date:     2023/06/26

#include <stdio.h>

unsigned srl(unsigned x, int k);
int sra(int x, int k);

unsigned srl(unsigned x, int k) {
    /*Perform shift arithmetically*/
    unsigned xsra = (int)x >> k;
    int mask = -1;
    mask = mask << ((sizeof(int) << 3) - k);
    return ~mask & xsra;
}

int sra(int x, int k) {
    /*Perform shift logically*/
    int xsrl = (unsigned)x >> k;
    unsigned mask = 1;
    int *p = &x;
    char *temp = (void *)p; //int* to char*
    int high = (((mask << 7) & temp[sizeof(int) - 1]) == 128);
    high = -high << ((sizeof(int) << 3) - k);
    return high | xsrl;
}

int main() {
	int x = 0x12345678;
	int y = -1;
	printf("%#x\n", srl((unsigned) x, 8));
	printf("%#x\n", sra(x, 8));
	printf("%#x\n", srl((unsigned) y, 8));
	printf("%#x\n", sra(y, 8));
	return 0;
    return 0;
}