//2.62.c
//Function: The record of CS:APP Homework 2.62
/*
Write a function int_shifts_are_arithmetic() that yields 1 when run on a
machine that uses arithmetic right shifts for data type int and yields 0 otherwise.
Your code should work on a machine with any word size. Test your code on several
machines.
*/
//Author:   Godfrey
//Date:     2023/06/19

#include <stdio.h>

int int_shifts_are_arithmetic(int input);

int int_shifts_are_arithmetic(int input) {
    //int num = -1;
    int check = input >> 2;
    return input == check;
}

int main() {
    int result1 = int_shifts_are_arithmetic(-1);
    printf("%d\n", result1);
    int result2 = int_shifts_are_arithmetic(0);
    printf("%d\n", result2);
    int result3 = int_shifts_are_arithmetic(1);
    printf("%d\n", result3);
    return 0;
}