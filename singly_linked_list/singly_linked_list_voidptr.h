#ifndef _SLL_VOID_H_
#define _SLL_VOID_H_

typedef struct List List;
typedef struct Node Node;

/* ---- Node ---- */

struct Node {
    void *data;
    Node *next;
    List *list;
};

Node * create_node(void *data, Node *next, List *list);

/* ---- List ---- */

struct List {
    Node *head;
    int size;
};

#define list_for_each(from, ptr) \
    for (ptr = from; ptr != NULL; ptr = ptr->next)

#define list_for_each_with_prev(from, ptr, prev) \
    for (ptr = from, prev = from; ptr != NULL; prev = ptr, ptr = ptr->next)

#define list_for_each_safe(from, ptr, n) \
    for (ptr = from, n = ptr->next; ptr != NULL; ptr = n, \
    n = (ptr != NULL) ? ptr->next : NULL)

#define list_for_each_safe_with_prev(from, ptr, prev, n) \
    for (ptr = from, prev = from, n = ptr->next; ptr != NULL; ptr = n, prev = ptr, \
    n = (ptr != NULL) ? ptr->next : NULL)


Node * get_node(List *list, int nr);
void * get_element(List *list, int nr);
void * get_element_last(List *list);

int put_element(List *list, int nr, void *data);
int put_element_last(List *list, void *data);

Node * remove_node_by_nr(List *list, int nr);
void * remove_element_by_nr(List *list, int nr);
Node * remove_node(List *list, Node *node);
Node * remove_node2(List *list, Node *node, Node *prev);
void * remove_element(List *list, Node *node);
void * remove_element2(List *list, Node *node, Node *prev);

Node * find_node(List *list, void *other,
                    int(*compare)(const void *a1, const void *a2));
void * find_element(List *list, void *other,
                    int(*compare)(const void *a1, const void *a2));

#endif //_SLL_VOID_H_
