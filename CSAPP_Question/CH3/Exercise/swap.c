void swap1(long *xp, long *yp)
{
    long t0 = *xp;
    long t1 = *yp;
    *xp = t1;
    *yp = t0;
}

long swap2(long *xp, long y)
{
    long x = *xp;
    *xp = y;
    return x;
}