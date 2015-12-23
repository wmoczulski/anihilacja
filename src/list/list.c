#include <stdlib.h>
#include <stdio.h>
#include "list.h"
#include "../config/config.h"
#include "../debug/debug.h"

list *list_new() {
    list *result = malloc(sizeof(list));
    result->first = NULL;
    result->last = NULL;
    return result;
}

void list_empty(list *list1) {
    while (list1->first != NULL) {
        list1->first = list1->first->next;
        if (list1->first->prev != NULL) {
            free(list1->first->prev->ptr);
            free(list1->first->prev);
        }
    }
}

void list_delete(list *list1) {
    list_empty(list1);
    free(list1);
}


list_node *list_node_new(void *pVoid) {
    list_node *result = malloc(sizeof(list_node));
    result->next = NULL;
    result->prev = NULL;
    result->ptr = pVoid;
    result->parent = NULL;
    return result;
}

void list_node_delete(list_node *node) {
    if (node == NULL) {
        return;
    }

    if (node->parent != NULL) {
        if (node->parent->first == node) {
            node->parent->first = node->next;
        }
        if (node->parent->last == node) {
            node->parent->last = node->prev;
        }
    }
    if (node->prev != NULL) {
        node->prev->next = node->next;
    }
    if (node->next != NULL) {
        node->next->prev = node->prev;
    }
    free(node);
}

void list_add_first(list *list1, list_node *node) {
    node->next = list1->first;
    list1->first = node;
    if (list1->last == NULL) {
        list1->last = node;
    }
    node->parent = list1;
}

void list_add_last(list *list1, list_node *node) {
    node->prev = list1->last;
    list1->last = node;
    if (list1->first == NULL) {
        list1->first = node;
    }
    node->parent = list1;
}

list_node *list_get_first(list *list1) {
    return list1->first;
}

list_node *list_get_last(list *list1) {
    return list1->last;
}

int list_size(list *list1) {
    int size = 0;
    list_node *node = list1->first;
    while (node != NULL) {
        size++;
        node = node->next;
    }
    return size;
}

list_node *list_find_by_ptr(list *list1, void *pVoid) {
    list_node *node = list1->first;
    while (node != NULL) {
        if(node->ptr == pVoid){
            return node;
        }
        node = node->next;
    }
    return NULL;
}
