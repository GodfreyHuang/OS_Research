//2.61.c
//Function: The record of CS:APP Homework 2.61
/*
Write C expressions that evaluate to 1 when the following conditions are true and
to 0 when they are false. Assume x is of type int.
A. Any bit of x equals 1.
B. Any bit of x equals 0.
*/
//Author:   Godfrey
//Date:     2023/06/14

#include <stdio.h>

int cExpression(int n); //Check four conditions
int xor(unsigned int a, unsigned int b); //xor for mask

int cExpression(int n) {
    int origin = n;
    int result1 = 0, result2 = 0, result3 = 0, result4 = 0;
    unsigned int mask_checkAllBits = 0xFFFFFFFF; //Check all 
    unsigned int mask_checkLast = 0x0000000F; //Check last
    unsigned int mask_checkFront = 0xF0000000; //Check first

    result1 = !xor(n, mask_checkAllBits); //Check any bits in n is 1
    result2 = !xor(n, ~mask_checkAllBits); //Check any bits in n is 0
    result3 = !xor((n & mask_checkLast), mask_checkLast); //Check lowest bit is 1
    //To do this, we need to mask all bits without the lowest.
    result4 = !xor((n & mask_checkFront), 0x0); //Check highest bit is 0.
    //To do this, we need to mask all bits without the highest.
    printf("%d %d %d %d\n", result1, result2, result3, result4);
    
    return result1 || result2 || result3 || result4;
}

int xor(unsigned int a, unsigned int b) {
    return ((a & ~b) | (~a & b));
}

int main() {
    int testData0 = 0xFFFFFFFF;
    int testData1 = 0x00000000;
    int testData2 = 0xFFFFFFFF;
    int testData3 = 0x00000000;
    int testData4 = 0xFFFFFFFF;
    int testData5 = 0x0F0F0F0F;
    int testData6 = 0xFFFFFFF0;

    printf("%x, %d\n", testData0, cExpression(testData0));
    printf("%x, %d\n", testData1, cExpression(testData1));
    printf("%x, %d\n", testData2, cExpression(testData2));
    printf("%x, %d\n", testData3, cExpression(testData3));

    return 0;
}