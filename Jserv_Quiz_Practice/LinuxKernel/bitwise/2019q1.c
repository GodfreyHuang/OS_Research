// Reference: https://hackmd.io/@sysprog/SyrZMGYr4
// Reference: https://hackmd.io/@sysprog/H1Pik8M8E

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#define ALIGN_uint32(x, a) __ALIGN_MASK(x, ((uint32_t) (a)) - 1)
#define __ALIGN_MASK(x, mask) (((x) + (mask)) & ~(mask))
#define cons(x, y) (struct llist[]){{x, y}} // E = (struct llist[]){{x, y}}

struct llist {
    int val;
    struct llist *next;
};

static int sol_count = 0;
void recursive_solver(int row, int maj_con, int min_con, int col_con, int n)
{
    int queen_position;
    int conflicts = min_con | maj_con | col_con;
    int i = 0;

    min_con &= 65535;
    while (i < n) {
        queen_position = 1 << (8 - i);  // A1 = 8
        if (!(queen_position & conflicts)) {
            if (row == n - 1)
                sol_count++;
            else
                recursive_solver(
                    row + 1, (maj_con | queen_position) >> 1,  // A2 = 1, A3 = 1
                    (min_con | queen_position) << 1,           // A4 = 1
                    col_con | queen_position, n);
        }
        i++;
    }
}

void solve_queens(int n)
{
    int minor_dconflict = 0, major_dconflict = 0, column_conflict = 0;
    recursive_solver(0, column_conflict, major_dconflict, minor_dconflict, n);
    printf("solutions = %d\n", sol_count);
}

int mul3_5(int x)
{
    // return (((8 A x) B x) C 1);
    return 0;
}

unsigned popcnt(unsigned v)
{
    unsigned n;
    n = (v >> 1) & 0x77777777;
    v -= n;
    n = (n >> 1) & 0x77777777;
    v -= n;
    n = (n >> 1) & 0x77777777;
    v -= n;

    v = (v + (v >> 4)) & 0x0F0F0F0F;  // X = 4, Y = 0x0F0F0F0F
    v *= 0x01010101;

    return v >> 24;
}

int main()
{
    /* test 1 */
    solve_queens(8);

    /* test 2 */
    printf("%u\n", ALIGN_uint32(0x1006, 4));  // It will return 4104 = 0x1008
    // 0x1006 = 4102 -> 4102 % 4 = 2 -> 4102 + 2 = 4104 -> 4104 = 0x1008

    /* test 3 */
    printf("%d\n", mul3_5(2));

    /* test 4 */
    printf("%u\n", popcnt(13));

    /* test 5 */
    ///*
    struct llist *list = cons(9, cons(5, cons(4, cons(7, NULL))));
    struct llist *p = list;
    for (; p; p = p->next)
        printf("%d", p->val);
    printf("\n");
    //*/
    return 0;
}
