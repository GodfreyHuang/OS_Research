// Reference: https://hackmd.io/@sysprog/linux2020-quiz1

#include <stdio.h>

typedef struct __list {
    int data;
    struct __list *next;
} list;

/* Question 1 */
list *sort(list *start) {
    if (!start || !start->next)
        return start;
    list *left = start; //Left amd right will break linked-list in two parts
    list *right = left->next; //Left's start node is start; Right's start node is left->next
    //LL0; //To cut and merge, we need to let left->next to NULL for a cut!
    left->next = NULL; /* <-- LL0 */

    left = sort(left); //Doing dfs for cut until to merge
    right = sort(right);

    for (list *merge = NULL; left || right; ) {
        if (!right || (left && left->data < right->data)) {
            if (!merge) {
                //LL1; //Due to the (left && left->data < right->data), we can know that left is the smallest
                       //And the merge is still NULL. That means merge need init.
                       //Let left become start!
                start = merge = left; /* <-- LL1 */
            } else {
                //LL2; //Merge already init. So left is smaller.
                       //We let merge->next point to left.
                merge->next = left; /* <-- LL2 */
                merge = merge->next;
            }
            //LL3;
            left = left->next; /* <-- LL3 */
        } else {
            if (!merge) {
                //LL4;
                start = merge = right;  /* <-- LL4 */
            } else {
                //LL5;
                merge->next = right;  /* <-- LL5 */
                merge = merge->next;
            }
            //LL6;
            right = right->next;  /* <-- LL6 */
        }
    }
    return start;
}

int main()
{
    return 0;
}