typedef struct NodeCDT Node;
typedef Node *Tree;
typedef int KeyT;

/* Gives a new, emoty tree */
Tree TreeNew();

/* Frees a Tree. Don't forget to NULL your pointers */
void TreeFree(Tree t);

/* Inserts new node in the tree. Make sure to give Tree reference as argument */
void TreeInsert(Tree *tptr, KeyT val);

/* Finds a node in the tree and returns 1 if found, 0 if not found */
int TreeFind(Tree t, KeyT target);

/* Deletes a node from a tree. Make sure to give Tree reference as argument */
int TreeDelete(Tree *t, KeyT target);

/* These functions do traversals on the tree, passing each node value to func */
void TreePreorder(Tree t, void (*func)(KeyT));
void TreeInorder(Tree t, void (*func)(KeyT));
void TreePostorder(Tree t, void (*func)(KeyT));

/* Prints the tree in level order */
void TreePrintLevelorder(Tree t);

/* Return some significant values from your tree with these functions */
KeyT TreeMax(Tree t);
KeyT TreeMin(Tree t);
double TreeAverage(Tree t);
int TreeHeight(Tree t);
int TreeCount(Tree t);
KeyT TreeSum(Tree t);
