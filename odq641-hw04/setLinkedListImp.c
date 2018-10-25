#include "set.h"
#include <stdio.h>
#include <stdlib.h>

typedef struct NodeS {
    setElementT data;
    struct NodeS *next;
} Node;

struct setCDT {
    Node *head;
    int size;
};

setADT setNew()
{
    setADT A;
    A = (setADT) malloc(sizeof(struct setCDT));
    if (A == NULL)
	return NULL;
    
    A->size = 0;
    A->head = NULL;
    return A;
}

void setFree(setADT A)
{
    Node *cp, *prev;
    cp = A->head;
    
    while(cp) {
	prev = cp;
	cp = cp->next;
	free(prev);
    }
    free(A);
}

int setInsertElementSorted(setADT A, setElementT item)
{
    return -1;
}

setADT setUnion(setADT A, setADT B)
{
    return NULL;
}

setADT setIntersection(setADT A, setADT B)
{
    return NULL;
}

setADT setDifference(setADT A, setADT B)
{
    return NULL;
}

int setCardinality(setADT A)
{
    return -1;
}

void setPrint(setADT A, char *name)
{
    printf("print!\n");
}
