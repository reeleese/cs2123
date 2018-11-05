#include "tree.h"
#include <stdio.h>
#include <string.h>

int equal(char *a, char *b);
void listCommands();

int main()
{
    char command[100];
    int arg, done;
    Tree myTree;
    Node *target;

    myTree = TreeNew();

    done = 0;
    while (!done) {
	printf("Enter a command:\n >");
	scanf("%s", command);
	printf("%s\n", command);
	
	if (equal(command, "insert")) {
	    scanf("%d", &arg);
	    TreeInsert(myTree, arg);
	} else if (equal(command, "find")) {
	    scanf("%d", &arg);
	    TreeFind(myTree, arg)? printf("Found.\n") : printf("Not Found.\n");
	} else if (equal(command, "delete")) {
	    scanf("%d", &arg);
	    if ((target = TreeFind(myTree, arg)) != NULL)
		TreeDelete(myTree, target);
	    else
		printf("%d is not in the tree.\n", arg);
	} else if (equal(command, "inorder")) {
	    TreePrintInorder(myTree);
	} else if (equal(command, "preorder")) {
	    TreePrintPreorder(myTree);
	} else if (equal(command, "postorder")) {
	    TreePrintPostorder(myTree);
	} else if (equal(command, "levelorder")) {
	    TreePrintLevelorder(myTree);
	} else if (equal(command, "max")) {
	    printf("MAX = %d\n", TreeMax(myTree));
	} else if (equal(command, "min")) {
	    printf("MIN = %d\n", TreeMin(myTree));
	} else if (equal(command, "average")) {
	    printf("AVERAGE = %lf\n", TreeAverage(myTree));
	} else if (equal(command, "height")) {
	    printf("HEIGHT = %d\n", TreeHeight(myTree));
	} else if (equal(command, "count")) {
	    printf("COUNT = %d\n", TreeCount(myTree));
	} else if (equal(command, "sum")) {
	    printf("SUM = %d\n", TreeSum(myTree));
	} else if (equal(command, "quit")) {
	    done = 1;
	} else if (equal(command, "help")) {
	    listCommands();
	} else { /* Unrecognized command */
	    printf("Unrecognized command. ");
	    printf("Type \"help\" for a list of commands.\n");
	}
    }
}

int equal (char *a, char *b)
{
    if (strcmp(a, b) == 0)
	return 1;
    return 0;
}

void listCommands()
{
    printf("Commands:\n");
}
