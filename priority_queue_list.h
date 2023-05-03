#ifndef LAB1_LISTA_PRIORITY_QUEUE_LIST_H
#define LAB1_LISTA_PRIORITY_QUEUE_LIST_H
#include <stddef.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include <pthread.h>

typedef struct node node;
struct node {
    node* next;
    node* prev;
    void* value;
};

typedef void (print_data_t)(void*);
typedef int (comparator_t)(void*, void*);
typedef void (dispose_t)(void*);
struct List {
    node* head;
    node* tail;
    size_t size_data;
    print_data_t* print_function;
    comparator_t* comparator_function;
    dispose_t* dispose;
};

struct List* initList(size_t size_data, print_data_t* print_function, comparator_t* comparator_function, dispose_t* dispose);

struct node* initNode(struct node* next, struct node* prev, void* value);

node* getPrevToAdd(struct List* lista, void* value);

void add(struct List* lista, void* value);

void deleteFirst(struct List* lista);

void deleteNode(struct List* lista, void* value, bool usun_wszystkie);

void printList(struct List* lista);

void deleteAll(struct List* lista);

#endif //LAB1_LISTA_PRIORITY_QUEUE_LIST_H
