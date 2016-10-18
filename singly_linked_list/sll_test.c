#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//#define NDEBUG
#include <assert.h>

#include "singly_linked_list_voidptr.h"


int main(int argc, char** argv)
{
    Node *node, *ptr, *prev;

    char *a = "Huehe";
    char *b = "Sialala";
    char *c = "Bul";

    List *list = calloc(1, sizeof(List));

    put_element_last(list, a);
    put_element_last(list, b);
    put_element_last(list, c);
    put_element(list, 1, "Eeeej");

    assert(list->size == 4);
    assert(strcmp((char *)get_element_last(list), "Bul") == 0);
    assert(strcmp((char *)get_element(list, 1), "Eeeej") == 0);
    assert(strcmp((char *)get_node(list, 0)->data, "Huehe") == 0);
    assert(list->size == 4);

    assert(strcmp((char *)remove_element_by_nr(list, 2), "Sialala") == 0);
    assert(list->size == 3);
    assert(find_element(list, "Sialala", strcmp) == NULL);
    assert(find_node(list, "Bul", strcmp) != NULL);

    node = find_node(list, "Eeeej", strcmp);
    assert(node != NULL);
    assert(remove_element(list, node) != NULL);
    assert(list->size == 2);

    assert(remove_element_by_nr(list, 2) == NULL);

    put_element(list, 1, "Lol");
    assert(list->size == 3);

    list_for_each_safe(list->head, ptr, node) {
        remove_node(list, ptr);
    }
    assert(list->size == 0);
    assert(list->head == NULL);
    assert(get_element_last(list) == NULL);

    assert(put_element_last(list, "Ajaj") == 0);
    assert(put_element(list, 6, "Gogol") == 0);
    assert(put_element(list, -2, "aaa") < 0);
    assert(list->size == 2);

    assert(get_element_last(list) != NULL);
    assert(get_element(list, 1) != NULL);
    assert(get_element(list, 4) == NULL);

    assert(remove_element(list, NULL) == NULL);
    assert(remove_element2(list, NULL, NULL) == NULL);
    assert(remove_element_by_nr(NULL, 1) == NULL);
    assert(remove_node(list, NULL) == NULL);
    assert(remove_node2(list, NULL, NULL) == NULL);
    assert(remove_node_by_nr(NULL, 1) == NULL);

    put_element_last(list, "zoo");
    put_element_last(list, "fffff");

    list_for_each_safe_with_prev(list->head, ptr, prev, node) {
        remove_node2(list, ptr, prev);
    }
    assert(list->size == 0);

    return 0;
}
