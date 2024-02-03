// Reference: https://hackmd.io/@sysprog/linux2020-quiz3

#include <stddef.h>
#include <stdint.h>
#include <stdio.h>

typedef struct __list list;
struct __list {
    int data;
    struct __list *addr;
};

#define XOR(a, b) ((list *) ((uintptr_t) (a) ^ (uintptr_t) (b)))

struct node {
    int data;
    struct node *next;
} *head;

void insert_example(struct node *newt)
{
    struct node *node = head, *prev = NULL;
    while (node != NULL && node->data < newt->data) {
        prev = node;
        node = node->next;
    }
    newt->next = node;
    if (prev == NULL)
        head = newt;
    else
        prev->next = newt;
}

void insert(struct node *newt)
{
    struct node **link = &head;
    while (*link && (*link)->data < newt->data)
        link = &(*link)->next;
    newt->next = *link;
    *link = newt;
}

/*
void insert_node(list **l, int d) {
    list *tmp = malloc(sizeof(list));
    tmp->data = d;

    if (!(*l)) {
        tmp->addr = NULL;
    } else {
        (*l)->addr = XOR(tmp, (*l)->addr);
        tmp->addr = *l;
    }
    *l = tmp;
}

void delete_list(list *l) {
    while (l) {
        list *next = l->addr;
        if (next)
            next->addr = XOR(next->addr, l);
        free(l);
        l = next;
    }
}
*/
list *sort(list *start);

list *sort(list *start)
{
    if (!start || !start->addr)
        return start;

    list *left = start, *right = start->addr;
    left->addr = NULL;
    right->addr = XOR(right->addr, left);

    left = sort(left);
    right = sort(right);

    for (list *merge = NULL; left || right;) {
        if (!right || (left && left->data < right->data)) {
            list *next = left->addr;
            if (next)
                next->addr = XOR(left, next->addr);

            if (!merge) {
                start = merge = left;
                merge->addr = NULL;
            } else {
                merge->addr = XOR(merge->addr, left);  // LL1
                left->addr = merge;                    // LL2
                merge = left;
            }
            left = next;
        } else {
            list *next = right->addr;
            if (next)
                next->addr = XOR(right, next->addr);

            if (!merge) {
                start = merge = right;
                merge->addr = NULL;
            } else {
                merge->addr = XOR(merge->addr, right);  // RR1
                right->addr = merge;                    // RR2
                merge = right;
            }
            right = next;
        }
    }

    return start;
}

int main()
{
    return 0;
}