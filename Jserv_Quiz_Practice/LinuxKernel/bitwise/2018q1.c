// Reference: https://hackmd.io/@sysprog/rJh9U4Guf?type=view

#include <stdio.h>
#include <stdlib.h>

int isMultN(unsigned int n);
int isMult5(unsigned int n);
int mul(int n, int m);

int isMultN(unsigned int n)
{
    int odd_c = 0, even_c = 0; /* variables to count odd and even SET bits */
    // printf("odd_c = %d, even_c = %d\n", odd_c, even_c);
    if (n == 0)  // return true if difference is 0.
        return 1;
    if (n == 1)  // return false if the difference is not 0.
        return 0;

    while (n) {
        if (n & 1)  // odd bit is SET, increment odd_C
            odd_c++;
        n >>= 1;

        if (n & 1)  // even bit is SET, increment even_c
            even_c++;
        n = n >> 1;
    }
    printf("odd_c = %d, even_c = %d\n", odd_c, even_c);
    /* Recursive call till you get 0/1 */
    return (isMultN(abs(odd_c - even_c)));
}

int isMult5(unsigned int n)
{
    int ret = 0;
    if (n == 0 || n == 5)  // 確認可被5整除
        return 1;
    if (n < 5)  // 剩下mod 5的數則代表不能被5整除
        return 0;
    while (
        n) /*
              將n的每一個位元都拿出來檢查 檢查可被5整除的數值一次需要檢查4次
              每一次檢查確認該位元為1時增加的數值不一樣，因為各二進制代表數值與5除的餘數關係如下:
              2^0 % 5 = 1, 2^1 % 5 = 2, 2^2 % 5 = 4, 2^3 % 5 = 3,
              2^4 % 5 = 1, 2^5 % 5 = 2, 2^6 % 5 = 4, 2^7 % 5 = 3, ...
              可發現每4個二進制次方形成一個循環，若要計算某數X是否為5的倍數時，就一次讀入一個循環的bit，
              將mod過後的數乘上加權後呼叫遞迴繼續執行
           */
    {
        if (n & 1)  // 如果LSB是1
            ret++;  // 1
        n >>= 1;    // 更新LSB
        if (n & 1)
            ret += 2;  // 2
        n >>= 1;       // 更新LSB
        if (n & 1)
            ret += 4;  // 4
        n >>= 1;       // 更新LSB
        if (n & 1)
            ret += 3;  // 3
        n >>= 1;       // 更新LSB
    }
    return (isMult5(abs(ret - 5)));  // 持續計算直到獲得解
}

int mul(int n, int m)
{
    int ret = 0;
    for (int c = 0; m; c++, m /= 2)
        if (!(m % 2 - 1))
            ret += n << c;  // c是m被拆解成2進制的數值,
                            // 如果m是基數代表最右邊的位元有1, 需要做2次方加法
    return ret;
}

int main()
{
    /* test 1 */
    printf("isMultN(9) = %d\n", isMultN(9));  // N = 3
    /* test 1: bonus */
    // 將N改寫為其他質數再改寫對應的程式碼
    printf("isMult5(9) = %d\n", isMult5(9));
    printf("isMult5(45) = %d\n", isMult5(45));

    /* test 2 */
    // If B is power of 2. Does A%B = A & (B - 1) correct?
    // Ans is YES.
    /*
      Explain in Chinese:
    A % B = A除與B的餘數
    A內大於等於B的數 = X, A內小於B的數 = low
    A = X + low
    A除以B後會把X都去除, 而小於B的部份無法處理, 因此成為餘數
    所以low = A%B

    若B為2次方數, 可以將B-1當作遮罩, 把A內比B小的數值都保留下來, 其他數值都刪除,
    就可以獲得餘數!
    */

    /* test 3 */
    printf("%d\n", 1 << 2 + 3 << 4);  // 1 << 5 << 4 = 1000000000(b) = 512

    /* test 4 */
    /* Doing * (-6) in Bitwise */
    /*
      Explain in Chinese:
    在CS:APP的第二章練習題2.40即有相同題目
    根據2.3.6 常數計算的說明
    x * 14 in Bitwise:
    因14 = 2^3 + 2^2 + 2^1,
    x * 14 = x * 2^3 + x * 2^2 + x * 2^1
           = (x << 3) + (x << 2) + (x << 1)
           = x * 2^4 - x * 2^1

    x * (-6) in Bitwise
    因-6 = 2^1 - 2^3
    x * (-6) = x * 2^1 - x * 2^3
             = (x << 1) - (x << 3) <- Ans
    */

    /* test 5 */
    printf("%d\n", mul(2, 3));

    return 0;
}