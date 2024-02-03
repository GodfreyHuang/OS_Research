#include <stdio.h>
#include <stdint.h>

float fp32_to_bf16(float x)                 
{
    float y = x;
    int *p = (int *) &y;
    unsigned int exp = *p & 0x7F800000;
    unsigned int man = *p & 0x007FFFFF;
    if (exp == 0 && man == 0) /* zero */
        return x;
    if (exp == 0x7F800000 /* Fill this! */) /* infinity or NaN */
        return x;

    /* Normalized number */
    /* round to nearest */
    float r = x;
    int *pr = (int *) &r;
    *pr &= 0xFF800000;  /* r has the same exp as x */
    r /= 0x100 /* Fill this! */;
    y = x + r;

    *p &= 0xFFFF0000;

    return y;
}

int main(int argc, char *argv[])
{
    float test1 = 1.200000;
    printf("%f\n", fp32_to_bf16(test1));
    uint32_t u1 = fp32_to_bf16(test1);
    printf("0x%08x\n", u1);

    float test2 = 1.203125;
    printf("%f\n", fp32_to_bf16(test2));   
    uint32_t u2 = fp32_to_bf16(test2);
    printf("0x%08x\n", u2);
    return 0;
}