#include <string.h>
#include "list.h"

typedef struct __element {
    char *value;
    struct __element *next;
    struct list_head list;
} list_ele_t;

typedef struct {
    list_ele_t *head; /* Linked list of elements */
    list_ele_t *tail;
    size_t size;
    struct list_head list;
} queue_t;

static list_ele_t *get_middle(struct list_head *list)
{
    struct list_head *fast = list->next, *slow;
    list_for_each (slow, list) {
        //檢視如果fast的指標已經到達開頭list的話則停止, 因目前使用的list為雙向,
        //不會有NULL的情況
        if (fast->next == list ||
            fast->next->next == list)  // COND1 = fast->next == list, COND2 =
                                       // fast->next->next == list
            break;
        fast = fast->next->next;
    }
    return list_entry(slow, list_ele_t,
                      list);  // TTT = slow, 需要回傳slow因此時slow為中間節點
}

static void list_merge(struct list_head *lhs,
                       struct list_head *rhs,
                       struct list_head *head)
{
    INIT_LIST_HEAD(head);
    if (list_empty(lhs)) {
        list_splice_tail(lhs, head);
        return;
    }
    if (list_empty(rhs)) {
        list_splice_tail(rhs, head);
        return;
    }

    while (!list_empty(lhs) && !list_empty(rhs)) {
        char *lv = list_entry(lhs->next, list_ele_t, list)->value;
        char *rv = list_entry(rhs->next, list_ele_t, list)->value;
        struct list_head *tmp = strcmp(lv, rv) <= 0 ? lhs->next : rhs->next;
        list_del(tmp);
        list_add_tail(tmp, head);
    }
    list_splice_tail(list_empty(lhs) ? rhs : lhs, head);
}

void list_merge_sort(queue_t *q)
{
    if (list_is_singular(&q->list))
        return;

    queue_t left;
    struct list_head sorted;
    INIT_LIST_HEAD(&left.list);
    list_cut_position(
        &left.list, &q->list,
        &get_middle(&q->list)
             ->list);  // MMM = &get_middle(&q->list)->list
                       //先獲得queue_t內的中間值,
                       //再將中間值list_ele_t內的list_head list取出來
    list_merge_sort(&left);
    list_merge_sort(q);
    list_merge(&left.list, &q->list, &sorted);
    INIT_LIST_HEAD(&q->list);
    list_splice_tail(&sorted, &q->list);
}