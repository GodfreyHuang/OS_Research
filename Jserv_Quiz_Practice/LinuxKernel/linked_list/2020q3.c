#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

typedef struct __node 
{
    int val;
    struct __node *next;
} node_t;

void add_entry(node_t **head, int newVal)
{
    node_t **indirect = head;
    node_t *n = malloc(sizeof(node_t));
    n->val = newVal;
    n->next = NULL;

    assert(n); // AA1;
    while(*indirect)
        indirect = &(*indirect)->next;
    *indirect = n; // AA2
}

node_t *find_entry(node_t *head, int num)
{
    node_t *current = head;
    for(; current && current->val != num; current = current->next)
        ;
    return current;
}

void remove_entry(node_t **head, node_t *entry)
{
    node_t **indirect = head;
    while((*indirect) != entry)
        indirect = &(*indirect)->next;
    *indirect = entry->next;
    free(entry);
}

node_t *swap_pair(node_t *head)
{
    for(node_t **node = &head; *node && (*node)->next; node = &(*node)->next->next) // BB1 = node = &(*node)->next->next
    {
        node_t *tmp = *node;
        (*node) = (*node)->next; 
        tmp->next = (*node)->next;
        (*node)->next = tmp;
    }
    return head;
}

node_t *reverse(node_t *head)
{
    node_t *cursor = NULL;
    while(head)
    {
        node_t *next = head->next;
        head->next = cursor; // CCC
        cursor = head; // CCC
        head = next;
    }
    return cursor;
}

void print_list(node_t *head)
{
    for (node_t *current = head; current; current = current->next)
        printf("%d ", current->val);
    printf("\n");
}

int main(int argc, char const *argv[])
{
    node_t *head = NULL;

    print_list(head);

    add_entry(&head, 72);
    add_entry(&head, 101);
    add_entry(&head, 108);
    add_entry(&head, 109);
    add_entry(&head, 110);
    add_entry(&head, 111);

    print_list(head);

    node_t *entry = find_entry(head, 101);
    remove_entry(&head, entry);

    entry = find_entry(head, 111);
    remove_entry(&head, entry);

    print_list(head);

    /* swap pair.
     * See https://leetcode.com/problems/swap-nodes-in-pairs/
     */
    head = swap_pair(head);
    print_list(head);

    head = reverse(head);
    print_list(head);

    return 0;
}