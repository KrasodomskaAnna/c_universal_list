#include "priority_queue_list.h"
#include <stddef.h>
#include <stdlib.h>

struct List* initList(size_t size_data, print_data_t* print_function, comparator_t* comparator_function, dispose_t* dispose) {
    struct List* newList;
    newList = (struct List*)malloc(sizeof(struct List));
    newList->size_data = size_data;
    newList->print_function = print_function;
    newList->comparator_function = comparator_function;
    newList->dispose = dispose;
    return newList;
}

struct node* initNode(struct node* next, struct node* prev, void* value) {
    struct node* newNode;
    newNode = (struct node*)malloc(sizeof(struct node));
    newNode->next = next;
    newNode->prev = prev;
    newNode->value = value;
    return newNode;
}

node* getPrevToAdd(struct List* lista, void* value) {
    node* searched;
    for (searched = lista->head; searched != NULL; searched = searched->next) {
        // if searched->value < value:
        if ((lista->comparator_function)(searched->value, value) < 0)
            return searched->prev;
    }
    return lista->tail;
}

node* getNode(struct List* lista, void* value) {
    node* searched;
    for (searched = lista->head; searched != NULL; searched = searched->next) {
        // if searched->value < value:
        if ((lista->comparator_function)(searched->value, value) == 0)
            return searched;
    }
    return NULL;
}

void add(struct List* lista, void* value) {
    // wstawianie gdy lista pusta
    if(lista->head == NULL) {
        lista->head = initNode(NULL, NULL, value);
        lista->tail = lista->head;
        return;
    }

    node* prev = getPrevToAdd(lista, value);
    node* newNode = initNode(NULL, prev, value);

    // wstawianie na końcu
    if(prev == lista->tail) {
        prev->next = newNode;
        lista->tail = newNode;
        return;
    }

    // wstawianie na początku
    if(prev == NULL) {
        lista->head->prev = newNode;
        newNode->next = lista->head;
        lista->head = newNode;
        return;
    }

    // A->C dodajemy B -> A->B->C
    newNode->next = prev->next;			// B->next = A->next (C)
    prev->next->prev = newNode;			// C->prev = B
    prev->next = newNode;				// A->next = B
}

void deleteFirst(struct List* lista) {
    node* to_delete = lista->head;
    lista->head = lista->head->next;
    if(lista->head == NULL) {
        if(lista->tail == to_delete)
            lista->tail = NULL;
        else
            lista->head = lista->tail;
    }
    else
        lista->head->prev = NULL;
    free(to_delete);
}

void deleteNode(struct List* lista, void* value, bool usun_wszystkie) {
    node* to_delete = getNode(lista, value);
    if(to_delete == NULL) return;

    if(to_delete == lista->head) {
        deleteFirst(lista);

        // jeżeli mamy usuwać wszystkie rekordy o tej samej wartości
        // to trzeba sprawdzić, czy kolejne nie mają takiej wartości
        if(usun_wszystkie) {
            if (lista->head == NULL) return;
            if ((lista->comparator_function)(lista->head->value, value) == 0)
                deleteNode(lista, value, usun_wszystkie);
        }
        return;
    }

    node* prev = to_delete->prev;
    if(prev != NULL)
        prev->next = to_delete->next;
    if(to_delete->next != NULL)
        to_delete->next->prev = prev;
    if(to_delete == lista->tail)
        lista->tail = to_delete->prev;
    free(to_delete);

    // jeżeli mamy usuwać wszystkie rekordy o tej samej wartości
    // to trzeba sprawdzić, czy kolejne nie mają takiej wartości
    if(usun_wszystkie) {
        if (prev == NULL) return;
        if (prev->next == NULL) return;
        if ((lista->comparator_function)(prev->next->value, value) == 0)
            deleteNode(lista, value, usun_wszystkie);
    }
}

void printList(struct List* lista) {
    printf("------------\n");
    node* actual;
    for (actual = lista->head; actual != NULL; actual = actual->next) {
        (lista->print_function)(actual->value);
    }
}

void deleteAll(struct List* lista) {
    if(lista->head == NULL) return;
    while (lista->head->next != NULL)
        deleteFirst(lista);
    deleteFirst(lista);
}