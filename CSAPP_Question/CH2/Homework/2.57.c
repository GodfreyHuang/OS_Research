//2.57.c
//Function: The record of CS:APP Homework 2.57
//          Add show_short, show_long, show_double in show_bytes.h, show_bytes.c
//Author:   Godfrey
//Date:     2023/06/07

#include <stdio.h>

#include "show_bytes.h"

void test_show_bytes(int val);

void test_show_bytes(int val) {
    int ival = val;
    float fval = (float)ival;
    int *pval = &ival;
    short sval = (short)ival;
    long lval = (long)ival;
    double dval = (double)ival;
    show_int(ival);
    show_float(fval);
    show_pointer(pval);
    show_short(sval);
    show_long(lval);
    show_double(dval);
}

int main() {
    test_show_bytes(12345);
}