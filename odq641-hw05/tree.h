typedef struct NodeCDT Node;
typedef Node *Tree;
typedef int KeyT;

Tree TreeNew();
void TreeFree(Tree t);

void TreeInsert(Tree *tptr, KeyT val);
Node *TreeFind(Tree t, KeyT target);
int TreeDelete(Tree *t, KeyT target);

void TreePreorder(Tree t, void (*func)(KeyT));
void TreeInorder(Tree t, void (*func)(KeyT));
void TreePostorder(Tree t, void (*func)(KeyT));
void TreePrintLevelorder(Tree t);

KeyT TreeMax(Tree t);
KeyT TreeMin(Tree t);
double TreeAverage(Tree t);
int TreeHeight(Tree t);
int TreeCount(Tree t);
KeyT TreeSum(Tree t);
