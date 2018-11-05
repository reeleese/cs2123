typedef struct NodeCDT Node;
typedef Node *Tree;
typedef int KeyT;

Tree TreeNew();
void TreeFree(Tree t);
void TreeInsert(Tree t, KeyT val);
Node *TreeFind(Tree t, KeyT target);
void TreeDelete(Tree t, Node *target);
void TreePrintPreorder(Tree t);
void TreePrintInorder(Tree t);
void TreePrintPostorder(Tree t);
void TreePrintLevelorder(Tree t);
KeyT TreeMax(Tree t);
KeyT TreeMin(Tree t);
double TreeAverage(Tree t);
int TreeHeight(Tree t);
int TreeCount(Tree t);
KeyT TreeSum(Tree t);
