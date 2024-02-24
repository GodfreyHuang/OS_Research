/*
Consider the following code, in which we have omitted the expression being
computed:
*/
short arith2(short x, short y, short z)
{
    short t1 = x | y;
    short t2 = t1 >> 3;
    short t3 = ~t2;
    short t4 = z - t3;
    return t4;
}

/*
short arith2(short x, short y, short z)
x in %rdi, y in %rsi, z in %rdx
arith2:
    orq   %rsi, %rdi
    sarq  $3, %rdi
    notq  %rdi
    movq  %rdx, %rax
    subq  %rdi, %rax
    ret   
*/