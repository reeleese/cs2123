#include "tree.h"
#include <stdio.h>
#include <stdlib.h>

struct NodeCDT {
    KeyT key;
    struct NodeCDT *left, *right;
};

/* PRIVATE */
Node *NodeNew(KeyT key)
{
    Node *new;
    new = (Node *) malloc(sizeof(Node));
    if (new == NULL) {
        printf("No more memory.\n");
        exit(-1);
    }
    new->key = key;
    new->left = new->right = NULL;
    return new;
}

/* PUBLIC */
Tree TreeNew()
{
    return NULL;
}

void TreeFree(Tree t)
{
    
}

void TreeInsert(Tree *tptr, KeyT val)
{
    Tree tmp, t;
    t = *tptr;

    /* BASE CASE: We found the position to insert val */
    if (t == NULL) {
        tmp = NodeNew(val);
        *tptr = tmp;
    }

    /* INDUCTIVE CASE: Keep looking */
    else {
        if (t->key == val) {/* mini base case */
            return; 
        } else if (val < t->key) {
            TreeInsert(&t->left, val);
        } else {
            TreeInsert(&t->right, val);
        }
    }
}

Node *TreeFind(Tree t, KeyT target)
{
    /* BASE CASE: target is not in the tree*/
    if (t == NULL) {
        return NULL;
    }
    
    /* INDUCTIVE CASE: Keep looking */
    else {
        if (t->key == target) {/* mini base case */
            return t; 
        } else if (target < t->key) {
            return TreeFind(t->left, target);
        } else {
            return TreeFind(t->right, target);
        }
    }
}

void TreeDelete(Tree t, Node *target)
{
    
}

void TreePreorder(Tree t, void (*func)(KeyT) )
{
    if (t == NULL) return;
    (*func)(t->key);
    TreePreorder(t->left, func);
    TreePreorder(t->right, func);  
}

void TreeInorder(Tree t, void (*func)(KeyT) )
{
    if (t == NULL) return;
    TreeInorder(t->left, func);
    printf("%d ", t->key);
    TreeInorder(t->right, func);
}

void TreePostorder(Tree t, void (*func)(KeyT) )
{
    if (t == NULL) return;
    TreePostorder(t->left, func);
    TreePostorder(t->right, func);
    (*func)(t->key);
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

