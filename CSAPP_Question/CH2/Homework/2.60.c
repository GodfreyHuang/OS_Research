//2.60.c
//Function: The record of CS:APP Homework 2.60
//          Using function "replace_byte" to satisfied question requirement
//Author:   Godfrey
//Date:     2023/06/13
//Need to compile with 2.58

#include <stdio.h>

unsigned replace_byte(unsigned x, int i, unsigned char b);
int is_little_endian(int val); //It needs 2.58 code!

unsigned replace_byte(unsigned x, int i, unsigned char b) {
    unsigned int *ptr = &x;
    unsigned char *ch = (unsigned char *) ptr; //int to char

    if(is_little_endian(12345)) { //The endian that OS used will effect the result.
        printf("%c\n", ch[i]); //Print origin ch[i]
        ch[i] = b; //replace to b
    } 
    else {
        int j = sizeof(unsigned)-i-1;
        ch[j] = b;
    }
    return *ptr;
}

int main() {
    printf("%#x\n", replace_byte(0x12345678, 2, 0xAB));
    printf("%#x\n", replace_byte(0x12345678, 0, 0xAB));

    return 0;
}