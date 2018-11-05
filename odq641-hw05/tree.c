#include "tree.h"
#include <stdio.h>
#include <stdlib.h>

typedef struct NodeS {
    KeyT key;
    struct NodeS *left, *right;
} NodeCDT;


Tree TreeNew()
{
    return NULL;
}

void TreeFree(Tree t)
{

}

void TreeInsert(Tree t, KeyT val)
{
    
}

Node *TreeFind(Tree t, KeyT target)
{
    return NULL;
}

void TreeDelete(Tree t, Node *target)
{
    
}
void TreePrintPreorder(Tree t)
{

}

void TreePrintInorder(Tree t)
{

}

void TreePrintPostorder(Tree t)
{

}

void TreePrintLevelorder(Tree t)
{

}

KeyT TreeMax(Tree t)
{
    return -1;
}

KeyT TreeMin(Tree t)
{
    return -1;
}

double TreeAverage(Tree t)
{
    return -1.0; 
}

int TreeHeight(Tree t)
{
    return -1;
}

int TreeCount(Tree t)
{
    return -1;
}

KeyT TreeSum(Tree t)
{
    return -1;
}
