#include "set.h"
#include <stdio.h>
#include <stdlib.h>

void _expandArray(setADT);

#define initial_size 100

struct setCDT {
    setElementT *elements;
    int size;
    int capacity;
};

setADT setNew()
{
    setADT A;
    A = (setADT) malloc(sizeof(struct setCDT));
    if (A == NULL)
	return NULL;

    A->elements = (setElementT *) malloc(initial_size * sizeof(setElementT));
    if (A->elements == NULL) {
	setFree(A);
	return NULL;
    }

    A->capacity = initial_size;
    A->size = 0;
    return A;
}

void setFree(setADT A)
{
    free(A->elements);
    free(A);
}

int setInsertElementSorted(setADT A, setElementT item)
{
    int i, j;
    setElementT *arr;
    arr = A->elements;

    /* Resize A->elements if necessary */
    if (A->size == A->capacity)
	_expandArray(A);
    
    /* Find position to insert item */
    for (i=0; i<A->size; ++i) {
	if (arr[i] == item)
	    return A->size;
	if (arr[i] > item)
	    break;
    }

    /* shift values forward to accomodate item. Then, insert item */
    for (j=A->size; j>i; --j)
	arr[j] = arr[j-1];
    arr[j] = item;
    
    return ++A->size;
}

setADT setUnion(setADT A, setADT B)
{
    
    return NULL;
}

setADT setIntersection(setADT A, setADT B)
{
    int i, j;
    setElementT *aArr, *bArr;
    setADT C;
    
    C = setNew();
    aArr = A->elements;
    bArr = B->elements;

    /* For all setElementT x in A and B, insert x into C */
    for (i=0; i<A->size; ++i) {
	for (j=0; j<B->size; ++j) {
	    if (aArr[i] == bArr[j])
		setInsertElementSorted(C, aArr[i]);
	}
    }
    
    return C;
}

setADT setDifference(setADT A, setADT B)
{
    int i, j, flag=0;
    setElementT *aArr, *bArr;
    setADT C;

    C = setNew();
    aArr = A->elements;
    bArr = B->elements;

    for (i=0; i<A->size; ++i) {
	for (j=0; j<B->size; ++j) {
	    if (aArr[i] == bArr[j]) {
		flag = 1;
		break;
	    }
	}
	flag? flag=0 : setInsertElementSorted(C, aArr[i]);
    }
    
    return C;
}

int setCardinality(setADT A)
{
    return A->size;
}

void setPrint(setADT A, char *name)
{
    if (A->size == 0) {
	printf("%s: <empty>\n", name);
	return;
    }
	
    int i;
    printf("%s:", name);
    for (i=0; i<A->size; ++i) {
	printf(" %d,", A->elements[i]);
    }
    printf("\b \n");
}

void _expandArray(setADT A)
{
    int i, newSize;
    setElementT *arr;

    /* Allocate new array */
    newSize = A->size * 2;
    arr = (setElementT *) malloc(sizeof(setElementT));
    if (arr == NULL) {
	printf("ERROR: Out of memory\n Exiting...\n");
	exit(-1);
    }

    /* Populate new array */
    for (i=0; i<A->size; ++i) {
	arr[i] = A->elements[i];
    }

    /* Update A->elements */
    A->capacity = newSize;
    free(A->elements);
    A->elements = arr;
}
