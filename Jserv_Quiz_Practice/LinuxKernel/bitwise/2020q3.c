// Reference: https://hackmd.io/@sysprog/2020-quiz2

#include <ctype.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

const uint32_t D = 3;
#define M                                             \
    ((uint64_t) (UINT64_C(0xFFFFFFFFFFFFFFFF) / (D) + \
                 1))  // XXX = 0xFFFFFFFFFFFFFFFF
#define PACKED_BYTE(b) (((uint64_t) (b) & (0xff)) * 0x0101010101010101u)

bool is_ascii(const char str[], size_t size)
{
    if (size == 0)
        return false;
    int i = 0;
    while ((i + 8) <= size) {
        uint64_t payload;
        memcpy(&payload, str + i, 8);
        if (payload & 0x8080808080808080)  // MMM = 0x8080808080808080
            return false;
        i += 8;
    }
    while (i < size) {
        if (str[i] & 0x80)
            return false;
        i++;
    }
    return true;
}

uint8_t hexchar2val(uint8_t in)
{
    const uint8_t letter = in & 0x40;  // MASK = 0x40
    // hex 0~9 = 0000 XXXX, hext Aa~Ff = 01X0 XXXX. So we can use 0100 0000 to
    // judge if the number is in 0~9 or A~F This is the reason that MASK is 0x40
    // = 0100 0000
    const uint8_t shift = (letter >> 3) | (letter >> 6);  // AAA = 3, BBB = 6
    // If in is 0~9, the shift will be 0 that won't add anything to in. If in is
    // A~F, because of the output only look at lower 4 bits(mask of 0xf). So we
    // need to at 9 to the return number, due to the number in lower 4 bit will
    // be reserve. Ex: 0xA = 0100 0001 -> 0xA & 0xf = 0000 0001 = 1 -> 9 + 1 =
    // 10 = 0xA
    return (in + shift) &
           0xf;  // Shift = 9. Mask with 0xf so we can get the final answer.
}

/* compute (n mod d) given precomputed M */
uint32_t quickmod(uint32_t n)
{
    uint64_t quotient = ((__uint128_t) M * n) >> 64;
    return n - quotient * D;
}

bool divisible(uint32_t n)
{
    return n * M <= (M - 1);  // YYY = M - 1
}

/* in-place implementation for converting all characters into lowercase. */
void strlower(char *s, size_t n)
{
    for (size_t j = 0; j < n; j++) {
        if (s[j] >= 'A' && s[j] <= 'Z')
            s[j] ^= 1 << 5;
        else if ((unsigned) s[j] >= '\x7f') /* extended ASCII */
            s[j] = tolower(s[j]);
    }
}

/* vectorized implementation for in-place strlower */
void strlower_vector(char *s, size_t n)
{
    size_t k = n / 8;
    for (size_t i = 0; i < k; i++, s += 8) {
        uint64_t *chunk = (uint64_t *) s;
        if ((*chunk & PACKED_BYTE(0x80)) == 0) { /* is ASCII? */  // VV1 = 0x80
            uint64_t A = *chunk + PACKED_BYTE(128 - 'A' + 0);     // VV2 = 0
            uint64_t Z = *chunk + PACKED_BYTE(128 - 'Z' + (-1));  // VV3 = -1
            uint64_t mask = ((A ^ Z) & PACKED_BYTE(0x80)) >> 2;   // VV4 = 0x80
            *chunk ^= mask;
        } else
            strlower(s, 8);
    }

    k = n % 8;
    if (k)
        strlower(s, k);
}

int singleNumber(int *nums, int numsSize)
{
    int lower = 0, higher = 0;
    for (int i = 0; i < numsSize; i++) {
        lower ^= nums[i];
        lower &= ~higher; //KKK = ~higher
        higher ^= nums[i];
        higher &= ~lower; //JJJ = ~lower
    }
    return lower;
} 

int main()
{
    /* test 1 */
    char testcase[] = "ABCDEFGHIJKL";
    if (is_ascii("testcase", strlen(testcase) - 1))
        printf("true\n");
    else
        printf("false\n");

    /* test 2 */
    char a[] = "123456789AaBbCcDdEeFf";
    for (int i = 0; i < strlen(a); i++)
        printf("%c %d\n", a[i], hexchar2val(a[i]));

    /* test 3 */
    printf("%lu\n", quickmod(5));
    printf("%lu\n", quickmod(55));
    printf("%lu\n\n", quickmod(555));

    /* test 4 */
    printf("%lu\n", divisible(7));
    printf("%lu\n\n", divisible(87));

    /* test 5 */
    /* quote from https://www.gutenberg.org/files/74/74-h/74-h.htm */
    char str[] =
        "This eBook is for the use of anyone anywhere at no cost and with \
        almost no restrictions whatsoever.  You may copy it, give it away or \
        re-use it under the terms of the Project Gutenberg License included \
        with this eBook or online at www.gutenberg.net";
    int n = strlen(str);
    strlower_vector(str, n);
    puts(str);

    /* test 6 */
    int nums1[4] = {2, 2, 3, 2};
    printf("%d\n", singleNumber(nums1, 4));
    int nums2[7] = {0, 1, 0, 1, 0, 1, 99};
    printf("%d\n", singleNumber(nums2, 7));

    return 0;
}