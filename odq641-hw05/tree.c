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

void printLevel(Tree t, int h)
{
    if (t == NULL) return;

    if (h == 1)
        printf("%3d ", t->key);

    else if (h > 1) {
        printLevel(t->left, h-1);
        printLevel(t->right, h-1);
    }
}

void DeleteHelper(Tree *t)
{
    Node *target, *plmd_r, *lmd_r;
    target = *t;
    
    if (target->left == NULL && target->right == NULL)
        *t = NULL;
    else if (target->left == NULL)
        *t = target->right;
    else if (target->right == NULL)
        *t = target->left;
    else {
        plmd_r = target;
        lmd_r = target->right;

        /* find the left-most right descendant and its parent */
        while (lmd_r->left) {
            plmd_r = lmd_r;
            lmd_r = lmd_r->left;
        }

        /* Just in case we never entered the while loop */
        if (plmd_r == target)
            plmd_r->right = lmd_r->right;
        else
            plmd_r->left = lmd_r->right;

        /* Place lmd_r in target's position */
        lmd_r->left = target->left;
        lmd_r->right = target->right;
        *t = lmd_r;
    }
    free(target); 
}

/* PUBLIC */
Tree TreeNew()
{
    return NULL;
}

void TreeFree(Tree t)
{
    if (t == NULL) return;
    TreeFree(t->left);
    TreeFree(t->right);
    free(t);
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

int TreeDelete(Tree *t, KeyT target)
{
    Node *ptr = *t;

    if (ptr == NULL)
        return 0;
    else if (target < ptr->key)
        return TreeDelete(&ptr->left, target);
    else if (target > ptr->key)
        return TreeDelete(&ptr->right, target);

    DeleteHelper(t);
    return 1;
       
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
    (*func)(t->key);
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
    int i, height;
    height = TreeHeight(t);
    for (i=1; i<=height; ++i)
        printLevel(t, i);
    printf("\n");
}

KeyT TreeMax(Tree t)
{
    if (t == NULL) return 0; /* empty tree */
    if (t->right == NULL) return t->key; /* found the right-most node */
    return TreeMax(t->right); /* continue searching */
}

KeyT TreeMin(Tree t)
{
    if (t == NULL) return 0; /* empty tree */
    if (t->left == NULL) return t->key; /* found the left-most node */
    return TreeMin(t->left); /* continue searching */
}

double TreeAverage(Tree t)
{
    if (t == NULL) return 0;
    return TreeSum(t) / TreeCount(t);
}

int TreeHeight(Tree t)
{
    int max, h1, h2;
    if (t == NULL) return 0;

    h1 = TreeHeight(t->left);
    h2 = TreeHeight(t->right);

    max = h1>h2? h1 : h2;
    return 1 + max;
}

int TreeCount(Tree t)
{
    if (t == NULL) return 0;
    return 1 + TreeCount(t->left) + TreeCount(t->right);
}

KeyT TreeSum(Tree t)
{
    if (t == NULL) return 0;
    return t->key + TreeSum(t->left) + TreeSum(t->right);  
}

