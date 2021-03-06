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
    /* Allocate A */
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

    /* For each Node in A, free it */
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
    Node *new, *curr, *prev;
    curr = prev = NULL;

    /* Find position to insert item */
    for (curr = A->head; curr; curr = curr->next) {
	if (curr->data == item)
	    return A->size;
	if (curr->data > item)
	    break;
	prev = curr;
    }

    /* Allocate new node*/
    new = (Node *) malloc(sizeof(Node));
    if (new == NULL) {
	printf("ERROR: Out of memory\n Exiting...\n");
	exit(-1);
    }
    new->data = item;

    /* Insert item */
    if (prev == NULL) {
	A->head = new;
    } else {
	prev->next = new;
    }
    new->next = curr;
	
    return ++A->size;
}

setADT setUnion(setADT A, setADT B)
{
    Node *cpA, *cpB;
    setADT C;

    C = setNew();

    /* For all setElementT x in A, insert x into C */
    for (cpA=A->head; cpA; cpA = cpA->next)
	setInsertElementSorted(C, cpA->data);

    /* For all setElementT x in B, insert x into C */
    for (cpB=B->head; cpB; cpB = cpB->next)
	setInsertElementSorted(C, cpB->data);  
    /* Note: this works only because insert ignores duplicate values :D */
    
    return C;
}

setADT setIntersection(setADT A, setADT B)
{
    Node *cpA, *cpB;
    setADT C;

    C = setNew();

    /* For all setElementT x in A, insert x into C iff x in B */
    for (cpA=A->head; cpA; cpA = cpA->next) {
	for (cpB=B->head; cpB; cpB = cpB->next) {
	    if (cpA->data == cpB->data) {
		setInsertElementSorted(C, cpA->data);
		break;
	    }
	}
    }
	    
    return C;
}

setADT setDifference(setADT A, setADT B)
{
    int flag=0;
    Node *cpA, *cpB;
    setADT C;

    C = setNew();

    /* For each element in A, compare it with each element in B */
    for (cpA=A->head; cpA; cpA=cpA->next) {
	for (cpB=B->head; cpB; cpB = cpB->next) {
	    if (cpA->data == cpB->data) {
		flag = 1;
		break;
	    }
	}
	/* If A[i] appeared in B, do not add it to C. Else, add it */
	flag? flag=0 : setInsertElementSorted(C, cpA->data);
    }
    
    return C;
}

int setCardinality(setADT A)
{
    return A->size;
}

void setPrint(setADT A, char *name)
{
    /* Special case: |A| = 0 */
    if (A->size == 0) {
	printf("%s = {}\n", name);
	return;
    }

    /* Print all element in A */
    Node *cp;
    printf("%s = {", name);
    for (cp = A->head; cp; cp = cp->next) {
	printf("%d, ", cp->data);
    }

    /* Remove trailing comma and add lcosing bracket*/
    printf("\b\b} \n");
}
