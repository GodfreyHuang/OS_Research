#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>

// test 1
typedef struct __node {                   
    int value;
    struct __node *next;
} node_t;

static inline void list_add_node_t(node_t **list, node_t *node)
{
    node->next = *list;
    *list = node;
}

static inline void list_concat(node_t **left, node_t *right)
{
    while(*left)
        left = &(*left)->next; // LLL
    *left = right;
}

void quicksort(node_t **list)
{
    if(!list)
        return;
    node_t *pivot = *list;
    int val = pivot->value;
    node_t *p = pivot->next;
    pivot->next = NULL;

    node_t *left = NULL, *right = NULL;
    while(p)
    {
        node_t *n = p;
        p = p->next;
        list_add_node_t(n->value > val ? &right : &left, n); // AAA : BBB
    }

    quicksort(&left);
    quicksort(&right);

    node_t *result = NULL;
    list_concat(&result, left);
    list_concat(&result, pivot); // CCC
    list_concat(&result, right); // CCC
    *list = result;
}

static bool list_is_ordered(node_t *list) {
    bool first = true;
    int value;
    while (list) {
        if (first) {
            value = list->value;
            first = false;
        } else {
            if (list->value < value)
                return false;
            value = list->value;
        }
        list = list->next;
    }
    return true;
}

static void list_display(node_t *list) {
    printf("%s IN ORDER : ", list_is_ordered(list) ? "   " : "NOT");
    while (list) {
        printf("%d ", list->value);
        list = list->next;
    }
    printf("\n");
}

node_t *list_make_node_t(node_t *list, int num)
{
    node_t *n = malloc(sizeof(node_t));
    if(!n)
        return NULL;
    n->value = num;
    n->next = NULL;

    node_t **p = &list;
    while(*p)
        p = &(*p)->next;
    *p = n;
    return list;
}

int main(int argc, char **argv) {
    size_t count = 20;
    srand(time(NULL));

    node_t *list = NULL;
    while (count--)
        list = list_make_node_t(list, random() % 1024);

    list_display(list);
    quicksort(&list);
    list_display(list);

    if (!list_is_ordered(list))
        return 1;

    // list_free(&list);
    return 0;
}      