#include <stdlib.h>
#include "priority_queue_list.h"

typedef struct process process;
struct process {
	char name[40];
};

void print_process(void* data) {
	process* pr = (process*)data;
	printf("%s\n", pr->name);
}

int comparator(void* x, void* y) {
    return strcmp(x, y);
}

void dispose(void* data) {
    void* to_delete = data;
    data = NULL;
    free(to_delete);
}

int
main(int argc, char** argv) {
	struct List* lista = initList(sizeof(struct process), print_process, comparator, dispose);

	process* p1, * p2, * p3;
	p1 = (process*)malloc(sizeof(process));
#pragma warning(suppress : 4996)
	strcpy(p1->name, "Firefox");
	p2 = (process*)malloc(sizeof(process));
#pragma warning(suppress : 4996)
	strcpy(p2->name, "Geany IDE");
	p3 = (process*)malloc(sizeof(process));
#pragma warning(suppress : 4996)
	strcpy(p3->name, "Important Calculations");

	add(lista, p1);
	add(lista, p2);
	add(lista, p3);
	printList(lista);

	printf("\n");
	deleteNode(lista, p1, 0);
	printList(lista);

	printf("\n");
	add(lista, p2);
	printList(lista);

	printf( "\n" );
	deleteNode( lista, p3, 0 );
	printList( lista );

	printf( "\n" );
	deleteNode( lista, p2, 1 );
	printList( lista );

	deleteAll( lista );
	printList( lista );

	free(p1);
	free(p2);
	free(p3);

	return 0;
}
