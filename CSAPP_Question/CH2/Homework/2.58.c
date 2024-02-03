//2.58.c
//Function: The record of CS:APP Homework 2.58
//          Using function "is_little_endian" to let user know what endian the os used
//Author:   Godfrey
//Date:     2023/06/08

#include <stdio.h>

#include "show_bytes.h"

int is_little_endian(int val);
void show_endian(byte_pointer start, size_t len);

int is_little_endian(int val) {
    show_endian((byte_pointer) &val, sizeof(int));
}

void show_endian(byte_pointer start, size_t len) {
    size_t i; /*print all hex num in start*/
    for(i = 0; i < len; i++)
        printf("%.2x ", start[i]);
    printf("\n");

    if(start[0] == 0x00) /*big-endian*/
        printf("0\n");
    else /*little-endian*/
        printf("1\n");
}

int main() {
    is_little_endian(12345);
    /*
    According to the pic2-6, we can know that 12345's little-endian is 39 30 00 00
    and big-endian is 00 00 30 39. we can use the first hex number to judge which 
    endian is using in the system.
    */
    return 0;
}