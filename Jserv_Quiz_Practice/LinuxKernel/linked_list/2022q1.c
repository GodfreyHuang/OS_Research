// Reference: https://hackmd.io/@sysprog/linux2022-quiz1

#include <stdio.h>

// test1
#include <stddef.h>
#include <stdlib.h>

struct hlist_node { 
    struct hlist_node *next, **pprev; 
};
struct hlist_head { 
    struct hlist_node *first; 
};
typedef struct { 
    int bits; 
    struct hlist_head *ht; 
} map_t;

#define MAP_HASH_SIZE(bits) (1 << bits)

map_t *map_init(int bits) {
    map_t *map = malloc(sizeof(map_t));
    if (!map)
        return NULL;

    map->bits = bits;
    map->ht = malloc(sizeof(struct hlist_head) * MAP_HASH_SIZE(map->bits));
    if (map->ht) {
        for (int i = 0; i < MAP_HASH_SIZE(map->bits); i++)
            (map->ht)[i].first = NULL;
    } else {
        free(map);
        map = NULL;
    }
    return map;
}

struct hash_key {
    int key;
    void *data;
    struct hlist_node node;
};

#define container_of(ptr, type, member)               \
    ({                                                \
        void *__mptr = (void *) (ptr);                \
        ((type *) (__mptr - offsetof(type, member))); \
    })

#define GOLDEN_RATIO_32 0x61C88647
static inline unsigned int hash(unsigned int val, unsigned int bits) {
    /* High bits are more random, so use them. */
    return (val * GOLDEN_RATIO_32) >> (32 - bits);
}

static struct hash_key *find_key(map_t *map, int key) {
    struct hlist_head *head = &(map->ht)[hash(key, map->bits)];
    for (struct hlist_node *p = head->first; p; p = p->next) {
        struct hash_key *kn = container_of(p, struct hash_key, node);
        if (kn->key == key)
            return kn;
    }
    return NULL;
}

void *map_get(map_t *map, int key)
{
    struct hash_key *kn = find_key(map, key);
    return kn ? kn->data : NULL;
}

void map_add(map_t *map, int key, void *data)
{
    struct hash_key *kn = find_key(map, key);
    if (kn)
        return;

    kn = malloc(sizeof(struct hash_key));
    kn->key = key, kn->data = data;

    struct hlist_head *h = &map->ht[hash(key, map->bits)];
    struct hlist_node *n = &kn->node, *first = h->first;
    n->next = first; // AAA
    if (first)
        first->pprev = &n->next;
    n->pprev = &h->first; // BBB
}

void map_deinit(map_t *map)
{
    if (!map)
        return;

    for (int i = 0; i < MAP_HASH_SIZE(map->bits); i++) {
        struct hlist_head *head = &map->ht[i];
        for (struct hlist_node *p = head->first; p;) {
            struct hash_key *kn = container_of(p, struct hash_key, node);
            struct hlist_node *n = p;
            p = p->next;

            if (!n->pprev) /* unhashed */
                goto bail;

            struct hlist_node *next = n->next, **pprev = n->pprev;
            *pprev = next;
            if (next)
                next->pprev = pprev;
            n->next = NULL, n->pprev = NULL;

        bail:
            free(kn->data);
            free(kn);
        }
    }
    free(map);
}

int *twoSum(int *nums, int numsSize, int target, int *returnSize)
{
    map_t *map = map_init(10);
    *returnSize = 0;
    int *ret = malloc(sizeof(int) * 2);
    if (!ret)
        goto bail;

    for (int i = 0; i < numsSize; i++) {
        int *p = map_get(map, target - nums[i]);
        if (p) { /* found */
            ret[0] = i, ret[1] = *p;
            printf("found = %d, %d\n", i, *p);
            *returnSize = 2;
            break;
        }

        p = malloc(sizeof(int));
        *p = i;
        map_add(map, nums[i], p);
    }

bail:
    map_deinit(map);
    return ret;
}
// test 1 end

// using for test linked-list
struct ListNode {
    int val;
    struct ListNode *next;
};

void addToList(struct ListNode **head, int num)
{
    struct ListNode *n = malloc(sizeof(struct ListNode));
    if(!n)
        return;
    n->val = num;
    n->next = NULL;

    while(*head)
        head = &(*head)->next;
    *head = n;
}

void printList(struct ListNode* head)
{
    while(head)
    {
        printf("%d ", head->val);
        head = head->next;
    }
    printf("\n");
}

// test 2
struct ListNode *deleteDuplicates_recursion(struct ListNode *head)
{
    if (!head)
        return NULL;

    if (head->next && (head->val == head->next->val)) {  //COND1
        /* Remove all duplicate numbers */
        while (head->next && (head->val == head->next->val)) //COND2
            head = head->next;
        return deleteDuplicates_recursion(head->next);
    }

    head->next = deleteDuplicates_recursion(head->next);
    return head;
}

struct ListNode* deleteDuplicates_while(struct ListNode* head) {
    struct ListNode** node = &head;
    while(*node)
    {
        if((*node)->next && ((*node)->val == (*node)->next->val))
        {
            while((*node)->next && ((*node)->val == (*node)->next->val))
                *node = (*node)->next;
            *node = (*node)->next;
        }
        else
            node = &(*node)->next;
    }

    return head;
}

// doubly-linked list structure
#include "list.h"

typedef struct{
    int value;
    struct list_head list;
} element_t;

void deleteDuplicates_iterative(struct list_head *head)
{
    if(!head)
        return;
    struct list_head *cur, *safe;
    list_for_each_safe (cur, safe, head) {
        if (list_entry(cur, element_t, list)->value == list_entry(safe, element_t, list)->value) {
            while(safe != head && 
                list_entry(cur, element_t, list)->value == list_entry(safe, element_t, list)->value) {
                    list_del(cur);
                    cur = safe;
                    safe = safe->next;
            }
            list_del(cur);
        } 
    }
}

void deleteDuplicates_recursion_circularlist(struct list_head *cur, struct list_head *head)
{
    if(cur == head) 
        return;
    if ((cur->next != head && list_entry(cur, element_t, list)->value == list_entry(cur->next, element_t, list)->value) 
    || (cur->prev != head && list_entry(cur, element_t, list)->value == list_entry(cur->prev, element_t, list)->value)) {
        deleteDuplicates_recursion_circularlist(cur->next, head);
        list_del(cur);
    } 
    deleteDuplicates_recursion_circularlist(cur->next, head);
}
// test 2 end

// test 3
typedef struct {
    int capacity, count;             
    struct list_head dhead, hheads[];
} LRUCache;
    
typedef struct {
    int key, value;
    struct list_head hlink, dlink;
} LRUNode;

LRUCache *lRUCacheCreate(int capacity)
{   
    LRUCache *obj = malloc(sizeof(*obj) + capacity * sizeof(struct list_head));
    obj->count = 0;
    obj->capacity = capacity;
    INIT_LIST_HEAD(&obj->dhead);
    for (int i = 0; i < capacity; i++)
        INIT_LIST_HEAD(&obj->hheads[i]);
    return obj;
}

void lRUCacheFree(LRUCache *obj)
{       
    LRUNode *lru, *n;
    list_for_each_entry_safe (lru, n, &obj->dhead, dlink) { // MMM1 = list_for_each_entry_safe
        list_del(&lru->dlink);
        free(lru);
    }
    free(obj); 
}   

int lRUCacheGet(LRUCache *obj, int key)
{
    LRUNode *lru;
    int hash = key % obj->capacity;
    list_for_each_entry (lru, &obj->hheads[hash], hlink) { // MMM2 = list_for_each_entry
        if (lru->key == key) {
            list_move(&lru->dlink, &obj->dhead);
            return lru->value;
        }
    }
    return -1;
}

void lRUCachePut(LRUCache *obj, int key, int value)
{
    LRUNode *lru;
    int hash = key % obj->capacity;
    list_for_each_entry (lru, &obj->hheads[hash], hlink) { // MM3 = list_for_each_entry
        if (lru->key == key) {
            list_move(&lru->dlink, &obj->dhead);
            lru->value = value;
            return;
        }
    }

    if (obj->count == obj->capacity) {
        lru = list_last_entry(&obj->dhead, LRUNode, dlink); // MM4 = list_last_entry
        list_del(&lru->dlink);
        list_del(&lru->hlink);
    } else {
        lru = malloc(sizeof(LRUNode));
        obj->count++;
    }
    lru->key = key;
    list_add(&lru->dlink, &obj->dhead);
    list_add(&lru->hlink, &obj->hheads[hash]);
    lru->value = value;
}
// test 3 end

// test 4
struct seq_node {
    int num;
    struct list_head link;
};                                                                                                                                                            
            
static struct seq_node *find(int num, int size, struct list_head *heads)
{   
    struct seq_node *node;
    int hash = num < 0 ? -num % size : num % size;
    list_for_each_entry (node, &heads[hash], link) {
        if (node->num == num)
            return node;
    }
    return NULL;
}

int longestConsecutive(int *nums, int n_size)
{
    int hash, length = 0;
    struct seq_node *node;
    struct list_head *heads = malloc(n_size * sizeof(*heads));

    for (int i = 0; i < n_size; i++)
        INIT_LIST_HEAD(&heads[i]);

    for (int i = 0; i < n_size; i++) {
        if (!find(nums[i], n_size, heads)) {
            hash = nums[i] < 0 ? -nums[i] % n_size : nums[i] % n_size;
            node = malloc(sizeof(*node));
            node->num = nums[i];
            list_add(&node->link, &heads[hash]);
        }
    }

    for (int i = 0; i < n_size; i++) {
        int len = 0;
        int num;
        node = find(nums[i], n_size, heads);
        while (node) {
            len++;
            num = node->num;
            list_del(&node->link);

            int left = num, right = num;
            while ((node = find(--left, n_size, heads))) { // LLL = --left
                len++;
                list_del(&node->link);
            }

            while ((node = find(++right, n_size, heads))) { // RRR = ++right
                len++;
                list_del(&node->link);
            }

            length = len > length ? len : length;
        }
    }

    return length;
}
// test 4 end

int main(int argc, char *argv[])
{
    // test1
    // int *getTwoSum;
    // int getReturnSize = 0;
    // int testcase[4] = {2, 7, 11, 15};
    // getTwoSum = twoSum(testcase, 4, 9, &getReturnSize);
    // printf("%d %d\n", getTwoSum[0], getTwoSum[1]);

    // test2
    // int dataset[] = {1, 2, 3, 3, 4, 4, 5};
    // struct ListNode* root = NULL;
    // for(int i = 0; i < (sizeof(dataset)/sizeof(int)); ++i)
    //     addToList(&root, dataset[i]);

    // printList(root);

    // deleteDuplicates_recursion(root);
    // printList(root);

    // test 3
    LRUCache *testL = lRUCacheCreate(3);
    lRUCachePut(testL, 1, 1);
    lRUCachePut(testL, 2, 2);
    lRUCachePut(testL, 3, 3);
    lRUCachePut(testL, 2, 3);
    lRUCachePut(testL, 4, 4);
    printf("get key 1 = %d\n", lRUCacheGet(testL, 1));
    printf("get key 2 = %d\n", lRUCacheGet(testL, 2));
    printf("get key 3 = %d\n", lRUCacheGet(testL, 3));
    printf("get key 4 = %d\n", lRUCacheGet(testL, 4));
    lRUCacheFree(testL);

    return 0;
}