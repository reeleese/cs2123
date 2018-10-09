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

listADT list_n_copy(listADT a, int x)
{
    int i;
    myDataT *from, *to, *to_prev;
    listADT b;
    b = NewList();

    /* Special Cases */
    if (a == NULL)
	return NULL;

    if (b == NULL)
	return NULL;

    if (x < 1) 
	return b;

    /* Make b->start */
    to = (myDataT *) malloc(sizeof(myDataT));
    b->start = to;

    /* Copy first element from a to b*/
    from = a->start;
    to->x = from->x;
    to_prev = to;
    from = from->next;

    /* Copy rest of a (less than x) to b */
    for (i=1; from && i<x; ++i) {
	to = (myDataT *) malloc(sizeof(myDataT));
	to->x = from->x;
	to_prev->next = to;
	to_prev = to;
        from = from->next;
    }

    /* Make to last element in b and return*/
    to->next = NULL;
    b-> end = to;
    return b;
}

void FreeList(listADT a)
{
    myDataT *curr, *prev;
    curr = a->start;

    while (curr) {
	prev = curr;
	curr = curr->next;
	free(prev);
    }

    free(a);
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
    if (a == NULL) {
	printf("%s: <NULL>\n", name);
	return;
    }
    
    myDataT *index;

    printf("%s:", name);
    for (index = a->start; index; index = index->next) {
	printf(" %d", index->x);
    }
    
    printf("\n");
}

double list_average(listADT a)
{
    if (a == NULL)
	return 0.0;
    
    myDataT *index;
    double sum, count;
    sum = count = 0;

    for (index = a->start; index; index = index->next) {
	sum += index->x;
	++count;
    }

    return sum / count;
}

void list_delete_by_value(listADT a, listElementT val)
{
    myDataT *prev;
    myDataT *index;

    /* Find index of val */
    for(index = a->start; index; index = index->next) {
	if (index->x = val)
	    break;
	prev = index;
    }

    /* Cut out index of val */
    if (index) {
	prev->next = index->next;
	free(index);
    }
}


