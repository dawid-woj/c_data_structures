#include "singly_linked_list_voidptr.h"

#include <stdlib.h>


Node * create_node(void *data, Node *next, List *list) {
    Node *node = malloc(sizeof(Node));
    node->data = data;
    node->list = list;
    node->next = next;
    return node;
}

Node * get_node(List *list, int nr) {
    Node *ptr;
    int i = 0;

    if (list == NULL || list->size <= nr)
        return NULL;

    ptr = list->head;
    while (i < nr) {
        ptr = ptr->next;
        i++;
    }

    return ptr;
}

void * get_element(List *list, int nr) {
    Node *node = get_node(list, nr);
    if (node == NULL)
        return NULL;
    return node->data;
}

void * get_element_last(List *list) {
    if (list == NULL)
        return NULL;
    return get_element(list, list->size-1);
}

int put_element(List *list, int nr, void *data) {
    Node *prev, *ptr, *node;
    int i = 0;

    if (list == NULL || nr < 0)
        return -1;

    if (list->size < nr)
        nr = list->size;

    if (list->head == NULL) {
        list->head = create_node(data, NULL, list);
    } else if (nr == 0) {
        node = create_node(data, list->head, list);
        list->head = node;
    } else {
        prev = list->head;
        ptr = list->head;
        while (i < nr) {
            prev = ptr;
            ptr = ptr->next;
            i++;
        }
        node = create_node(data, ptr, list);
        prev->next = node;
    }

    list->size++;

    return 0;
}

int put_element_last(List *list, void *data) {
    if (list == NULL)
        return -1;
    return put_element(list, list->size, data);
}

Node * remove_node_by_nr(List *list, int nr) {
    Node *prev, *ptr;
    void *data;
    int i = 0;

    if (list == NULL || list->head == NULL || nr < 0 || nr >= list->size)
        return NULL;

    if (nr == 0) {
        ptr = list->head;
        list->head = list->head->next;
    } else {
        prev = list->head;
        ptr = list->head;
        while (i < nr) {
            prev = ptr;
            ptr = ptr->next;
            i++;
        }
        prev->next = ptr->next;
    }
    ptr->next = NULL;
    ptr->list = NULL;

    list->size--;

    return ptr;
}

void * remove_element_by_nr(List *list, int nr) {
    void *data;
    Node *node = remove_node_by_nr(list, nr);
    if (node == NULL)
        return NULL;

    data = node->data;
    free(node);
    node = NULL;

    return data;
}

Node * remove_node(List *list, Node *node) {
    Node *ptr, *prev;
    int found = 0;

    if (list == NULL || list->head == NULL || node == NULL
            || node->list != list)
        return NULL;

    if (node == list->head) {
        found = 1;
        list->head = node->next;
        ptr = node;
    } else {
        list_for_each_with_prev(list->head, ptr, prev) {
            if (ptr == node) {
                found = 1;
                prev->next = ptr->next;
                break;
            }
        }
    }

    if (found) {
        ptr->list = NULL;
        ptr->next = NULL;
        list->size--;
        return ptr;
    } else
        return NULL;
}

Node * remove_node2(List *list, Node *node, Node *prev) {
    if (list == NULL || list->head == NULL || node == NULL
            || prev == NULL || node->list != list
            || prev->list != list)
        return NULL;

    prev->next = node->next;
    node->list = NULL;
    node->next = NULL;
    list->size--;

    return node;
}

void * remove_element(List *list, Node *node) {
    void *data;
    Node *n = remove_node(list, node);
    if (n == NULL)
        return NULL;

    data = n->data;
    free(n);
    n = NULL;

    return data;
}

void * remove_element2(List *list, Node *node, Node *prev) {
    void *data;
    Node *n = remove_node2(list, node, prev);
    if (n == NULL)
        return NULL;

    data = n->data;
    free(n);
    n = NULL;

    return data;
}

Node * find_node(List *list, void *other,
                    int(*compare)(const void *a1, const void *a2)) {
    Node *ptr;
    if (list == NULL || other == NULL || compare == NULL)
        return NULL;

    list_for_each(list->head, ptr) {
        if (compare(ptr->data, other) == 0)
            return ptr;
    }
    return NULL;
}

void * find_element(List *list, void *other,
                    int(*compare)(const void *a1, const void *a2)) {
    Node *node = find_node(list, other, compare);
    if (node == NULL)
        return NULL;
    return node->data;
}
