#include <stdlib.h>
#include <stdio.h> 
#include "list.h"

typedef struct point {
   listElementT x; 
   struct point *next;
} myDataT;

struct listCDT {
    myDataT *start; // myDataT *header;
    myDataT *end;   // myDataT *foother;
};

listADT NewList()
{
   listADT tmp;
   tmp = (listADT) malloc(sizeof(struct listCDT)); // New(listADT);

   if (tmp==NULL) return NULL;                  

   tmp->start = tmp->end = NULL;
   return tmp;
}

void list_insert_sorted(listADT a, int val)
{
    myDataT *b, *prev, *curr;

    b = (myDataT *) malloc(sizeof(myDataT)); 
    if (b==NULL) return;
    b->x = val;   
    b->next = NULL;

    prev = NULL;
    curr = a->start; 
    while(curr) {
	if (curr->x >= b->x ) break;
	prev = curr;
	curr = curr->next;
    }
    if(prev == NULL) {
	b->next = a->start;
	a->start = b;
    } else{ 
	b->next = prev->next;
	prev->next = b;
    }
    if (b->next == NULL) {
	a->end = b;
    }
}

void list_insert_unsorted(listADT a, int val) 
// add val at the end of the link list
{ 
    myDataT *b;

    b = (myDataT *) malloc(sizeof(myDataT)); 
    if (b==NULL) return;
    b->x = val;   
    b->next = NULL;

    if(a->start == NULL) {
	a->start = b;
    } else{ 
	a->end->next = b;   
    }
    a->end = b;
}

void list_print_values(listADT a, char *name)
{
    myDataT *index;

    printf("%s:", name);
    for (index = a->start; index; index = index->next) {
	printf(" %d", index->x);
    }
    printf("\n");
}



