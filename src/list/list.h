#ifndef ANIHILACJA_LIST_H
#define ANIHILACJA_LIST_H


typedef struct list list;
typedef struct list_node list_node;

struct list {
    list_node *first;
    list_node *last;
};
struct list_node {
    list *parent;
    list_node *prev;
    list_node *next;
    void *ptr;
};

list *list_new();

void list_delete(list *);

list_node *list_node_new(void *);

void list_node_delete(list_node *);

void list_add_first(list *, list_node *);

void list_add_last(list *, list_node *);

list_node *list_get_first(list *);

list_node *list_get_last(list *);

void list_empty(list *);

int list_size(list *);


#endif //ANIHILACJA_LIST_H
