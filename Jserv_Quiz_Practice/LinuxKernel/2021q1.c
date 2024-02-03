#include "2021q1.h"
#include <assert.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static bool validate(queue_t *q)
{
    struct list_head *node;
    list_for_each (node, &q->list) {
        if (node->next == &q->list)
            break;
        if (strcmp(list_entry(node, list_ele_t, list)->value,
                   list_entry(node->next, list_ele_t, list)->value) > 0)
            return false;
    }
    return true;
}

static queue_t *q_new()
{
    queue_t *q = malloc(sizeof(queue_t));
    if (!q)
        return NULL;

    q->head = q->tail = NULL;
    q->size = 0;
    INIT_LIST_HEAD(&q->list);
    return q;
}

static void q_free(queue_t *q)
{
    if (!q)
        return;

    list_ele_t *current = q->head;
    while (current) {
        list_ele_t *tmp = current;
        current = current->next;
        free(tmp->value);
        free(tmp);
    }
    free(q);
}

bool q_insert_head(queue_t *q, char *s)
{
    if (!q)
        return false;

    list_ele_t *newh = malloc(sizeof(list_ele_t));
    if (!newh)
        return false;

    char *new_value = strdup(s);
    if (!new_value) {
        free(newh);
        return false;
    }

    newh->value = new_value;
    newh->next = q->head;
    q->head = newh;
    if (q->size == 0)
        q->tail = newh;
    q->size++;
    list_add_tail(&newh->list, &q->list);

    return true;
}

uint16_t func(uint16_t N)
{
    /* change all right side bits to 1 */
    N |= N >> 1;
    N |= N >> 2;  // X = 2
    N |= N >> 4;  // Y = 4
    N |= N >> 8;  // Z = 8
    /*
    If N = 0x8000;  -> 1000 0000 0000 0000
       N |= N >> 1; -> 1100 0000 0000 0000
       N |= N >> 2; -> 1111 0000 0000 0000
       N |= N >> 4; -> 1111 1111 0000 0000
       N |= N >> 8; -> 1111 1111 1111 1111
    */
    return (N + 1) >> 1;
}

int main(void)
{
    /* test 1 */
    FILE *fp = fopen("cities.txt", "r");
    if (!fp) {
        perror("failed to open cities.txt");
        exit(EXIT_FAILURE);
    }

    queue_t *q = q_new();
    char buf[256];
    while (fgets(buf, 256, fp))
        q_insert_head(q, buf);
    fclose(fp);

    list_merge_sort(q);
    assert(validate(q));

    q_free(q);

    /* test 2 */
    printf("%u\n", func(0x8000));

    return 0;
}