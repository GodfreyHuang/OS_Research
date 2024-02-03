#include <stdio.h>

typedef unsigned char *byte_pointer;

void show_bytes(byte_pointer start, size_t len);

void show_int(int x);

void show_float(float x);

void show_short(short x); //Add for 2.57

void show_long(long x); //Add for 2.57

void show_double(double x); //Add for 2.57

void show_pointer(void *x);