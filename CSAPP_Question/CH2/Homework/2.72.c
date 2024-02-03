//2.72.c
//Function: The record of CS:APP Homework 2.72
/*You are given the task of writing a function that will copy an integer val into a
buffer buf, but it should do so only if enough space is available in the buffer.*/
/* Copy integer into buffer if space is available */
/* WARNING: The following code is buggy */
//void copy_int(int val, void *buf, int maxbytes) {
//    if (maxbytes-sizeof(val) >= 0)
//    memcpy(buf, (void *) &val, sizeof(val));
//}
//Author:   Godfrey
//Date:     2023/07/13

#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>

void copy_int(int val, void *buf, int maxbytes);

void copy_int(int val, void *buf, int maxbytes) {
    if(maxbytes - sizeof(val) >= 0) //If the maxbytes is big enough to include sizeof val
        memcpy(buf, (void *) &val, sizeof(val));
}

int main() {
    int maxbytes = sizeof(int) * 10;
    void *buf = malloc(maxbytes);
    int val = 0x12345678;

    copy_int(val, buf, maxbytes);
    assert(*(int *) buf == val);

    val = 0xFFFFFFFF;
    copy_int(val, buf, 0);
    assert(*(int *) buf != val);

    free(buf);
    return 0;
}