#include "set.h"
#include <stdio.h>

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
    
    return NULL;
}

void setFree()
{

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
