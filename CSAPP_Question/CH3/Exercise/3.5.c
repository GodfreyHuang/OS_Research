/*
You are given the following information. A function with prototype

    void decode1(long *xp, long *yp, long *zp);

is compiled into assembly code, yielding the following:

void decode1(long *xp, long *yp, long *zp)
xp in %rdi, yp in %rsi, zp in %rdx

decode1:
  movq (%rdi), %r8
  movq (%rsi), %rcx
  movq (%rdx), %rax
  movq %r8, (%rsi)
  movq %rcx, (%rdx)
  movq %rax, (%rdi)
  ret

Parameters xp, yp, and zp are stored in registers %rdi, %rsi, and %rdx, respec-
tively.
Write C code for decode1 that will have an effect equivalent to the assembly
code shown.
*/

void decode1(long *xp, long *yp, long *zp)
{
    int temp1 = *xp;
    int temp2 = *yp;
    int temp3 = *zp;
    *yp = temp1;
    *zp = temp2;
    *xp = temp3;
}