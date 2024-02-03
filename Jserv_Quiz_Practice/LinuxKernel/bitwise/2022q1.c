// Reference: https://hackmd.io/@sysprog/linux2022-quiz2

#include <stdint.h>
#include <stdio.h>
#include <stddef.h>

uint32_t average_1(uint32_t a, uint32_t b)
{
    return (a >> 1) + (b >> 1) + (a & b & 1);  // EXP1 = a & b & 1(?), 推測用途為補上a/2 + b/2的個位數(?)
}

uint32_t average_2(uint32_t a, uint32_t b)
{
    return (a & b) + ((a ^ b) >> 1);  // EXP2 = a & b, EXP3 = a ^ b
    // return 0;
}

uint32_t min(int32_t a, int32_t b) 
{
    int32_t diff = (a - b);
    return b + (diff & (diff >> 31)); 
    // 移動 31 位元後做 and 來測試 diff 是不是正數
    // 如果 diff 是正數，代表 a > b, 要回傳 b 才能得到 min 值，因此最高位元為 0 的時候做算術右移 diff 會與 0 做 and 動作並得到 b + 0 的結果
    // 反過來說若 diff 是負數，代表 a < b, 要回傳 a, b就必須要扣掉 diff 才能獲得 a, 此時 diff >> 31 會得到 -1, 以二補數系統來說會獲得整個都是 1 的 32 位元數
    // 與 diff 做 and 運算後我們即可得到完整的負值，將 b 減去差值後就可以得到 a
}

uint32_t max(uint32_t a, uint32_t b)
{
    return a ^ ((a ^ b) & -(a <= b)); // EXP4 = a ^ b, EXP5 = a <= b;
    // 必須在 a <= b 的情況下 a ^ b 才能獲得 a 與 b 的差，取得這個差後與 a 做 xor 運算就能獲得 b; 
    // 如果 a > b 的話直接輸出 a 即可，讓與 a 做 xor 運算的值為0即可輸出 a
}

// 有號數挑戰
int32_t max_sign(int32_t a, int32_t b)
{
    return a ^ ((a ^ b) & -(a <= b));
}

// 最大公因數
uint64_t gcd64(uint64_t u, uint64_t v)
{
    if (!u || !v)
        return u | v;
    while (v) {                               
        uint64_t t = v;
        v = u % v;
        u = t;
    }
    return u;
}

uint64_t gcd64_bit(uint64_t u, uint64_t v)
{
    if (!u || !v) // 如果其中一個是 0 (或是都是 0)
        return u | v; // 將其中一個非 0 的直接輸出
    int shift;
    for (shift = 0; !((u | v) & 1); shift++) 
    {
        u /= 2;
        v /= 2;
    }
    // printf("%ld %ld\n", u, v);
    while (!(u & 1))
        u /= 2;
    // printf("init = %ld %ld\n", u, v);
    do {
        while (!(v & 1))
            v /= 2;
        if (u < v) 
        {
            v -= u;
        } 
        else 
        {
            uint64_t t = u - v;
            u = v;
            v = t;
        }
        // printf("do = %ld %ld\n", u, v);
    } while (u == v); // COND => u == v

    return u << shift; // RET => u << shift
}

size_t naive(uint64_t *bitmap, size_t bitmapsize, uint32_t *out)
{
    size_t pos = 0;
    for (size_t k = 0; k < bitmapsize; ++k) {
        uint64_t bitset = bitmap[k];
        size_t p = k * 64;
        for (int i = 0; i < 64; i++) {
            if ((bitset >> i) & 0x1)
                out[pos++] = p + i;
        }
    }
    return pos;
}

size_t improved(uint64_t *bitmap, size_t bitmapsize, uint32_t *out)
{
    size_t pos = 0;
    uint64_t bitset;
    for (size_t k = 0; k < bitmapsize; ++k) {
        bitset = bitmap[k];
        while (bitset != 0) {
            uint64_t t = 0; // EXP6 = 
            int r = __builtin_ctzll(bitset);
            out[pos++] = k * 64 + r;
            bitset ^= t;                           
        }
    }
    return pos;
}

int main()
{
    /* test 1 */
    // UINT32_MAX = 4294967295
    printf("%u\n", (UINT32_MAX + UINT32_MAX) / 2);      // overflow
    printf("%u\n", average_1(UINT32_MAX, UINT32_MAX));  // get correct value
    // If you won't do (a & b & 1), the answer will be 4294967294, not the
    // correct answer 4294967295
    printf("%u\n", average_2(UINT32_MAX, UINT32_MAX));

    /* test 2 */
    // test min
    printf("min = %d\n", min(10, 100));
    printf("min = %d\n", min(1000, 100));
    // max
    printf("max = %d\n", max(5, 10));
    printf("max = %d\n", max(100, 5));
    // max with sign
    printf("max_sign = %d\n", max_sign(-10, 100));

    /* test 3 */
    printf("gcd64 : %ld\n", gcd64(16, 24));
    printf("gcd64_bit : %ld\n", gcd64_bit(16, 24));

    /* test 4 */
    

    return 0;
}