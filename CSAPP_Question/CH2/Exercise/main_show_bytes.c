//main_show_bytes.c
//Function: Doing practice in text content of chapter2
//Author:   Godfrey

#include <stdio.h>
#include <string.h>

#include "show_bytes.h"

//CS:APP Chapter2 pic2-5 example
void test_show_bytes(int val);
//CS:APP Chapter2 Ex2-6
void int_dex_to_bin(int val);

void test_show_bytes(int val) {
    int ival = val;
    float fval = (float) ival;
    int *pval = &ival;
    show_int(ival);
    show_float(fval);
    show_pointer(pval);
}

void int_dex_to_bin(int val) {
    char str[32];
    int i, result = 0;
    //int dex to bin
    for(i = 31; i >= 0; i--) { //using bitwise
        result = val >> i;
        //(result & 1) ? printf("1") : printf("0"); 
        if(result & 1)
            str[31-i] = '1';
        else
            str[31-i] = '0';
    }
    printf(" ");
    for(i = 0; i < 32; i++)
        printf("%c", str[i]);
    printf("\n");
}

int main() {
    //Print pic2-6 information
    printf("Print pic2-6 information:\n");
    test_show_bytes(12345);
    /*
    The value that c program print:
     39 30 00 00
     00 e4 40 46
     d4 2b 7b 82 fd 7f 00 00 <-- It will change when doing different execute.
    */

    //Exercise 2.5
    printf("\nPractice Quection 2.5:\n");
    int val = 0x87654321; //hex num
    byte_pointer valp = (byte_pointer) &val; //byte_pointer point to val
    show_bytes(valp, 1); //21
    show_bytes(valp, 2); //21 43
    show_bytes(valp, 3); //21 43 65
    show_bytes(valp, 4); //21 43 65 87 <- print all hex num
    /*   Little-endian   Big-endian
     A        21             87 
     B       21 43         87  65
     C      21 43 65     87  65  43
    */

    //Exercise 2.6
    //I only write how to dex to bin in interger
    printf("\nPractice Quection 2.6:\n");
    int test1 = 3510593;
    //float test2 = 3510593.0;
    int_dex_to_bin(test1); //print 00000000001101011001000101000001

    //Exercise 2.7
    printf("\nPractice Quection 2.7:\n");
    const char *s = "abcdef";
    show_bytes((byte_pointer) s, strlen(s)); //Print ascii code

    //Exercise 2.8
    printf("\nPractice Quection 2.8:\n");
    int a = 0b01101001, b = 0b01010101;
    int_dex_to_bin(a);   //00000000000000000000000001101001
    int_dex_to_bin(b);   //00000000000000000000000001010101  
    int_dex_to_bin(~a);  //11111111111111111111111110010110
    int_dex_to_bin(~b);  //11111111111111111111111110101010
    int_dex_to_bin(a&b); //00000000000000000000000001000001
    int_dex_to_bin(a|b); //00000000000000000000000001111101
    int_dex_to_bin(a^b); //00000000000000000000000000111100
 
    return 0;
}