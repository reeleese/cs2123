#include "tree.h"
#include <stdio.h>
#include <string.h>

int equal(char *a, char *b);
void listCommands();
void print(int x);

int main()
{
    char command[100];
    int arg, done;
    Tree myTree;
    
    myTree = TreeNew();

    done = 0;
    while (!done) {
        printf("Enter a command:\n>");
        scanf("%s", command);
        
        if (equal(command, "insert")) {
            scanf("%d", &arg);
            TreeInsert(&myTree, arg);
        } else if (equal(command, "find")) {
            scanf("%d", &arg);
            TreeFind(myTree, arg)? printf("Found.\n") : printf("Not Found.\n");
        } else if (equal(command, "delete")) {
            scanf("%d", &arg);
            TreeDelete(&myTree, arg);
        } else if (equal(command, "inorder")) {
            TreeInorder(myTree, print);
            printf("\n");
        } else if (equal(command, "preorder")) {
            TreePreorder(myTree, print);
            printf("\n");
        } else if (equal(command, "postorder")) {
            TreePostorder(myTree, print);
            printf("\n");
        } else if (equal(command, "levelorder")) {
            TreePrintLevelorder(myTree);
        } else if (equal(command, "max")) {
            printf("MAX = %d\n", TreeMax(myTree));
        } else if (equal(command, "min")) {
            printf("MIN = %d\n", TreeMin(myTree));
        } else if (equal(command, "average")) {
            printf("AVERAGE = %.3lf\n", TreeAverage(myTree));
        } else if (equal(command, "height")) {
            printf("HEIGHT = %d\n", TreeHeight(myTree));
        } else if (equal(command, "count")) {
            printf("COUNT = %d\n", TreeCount(myTree));
        } else if (equal(command, "sum")) {
            printf("SUM = %d\n", TreeSum(myTree));
        } else if (equal(command, "quit")) {
            TreeFree(myTree);
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
    printf("  insert...\tInserts a value\n");
    printf("  find...\tDetermine if a value lies in the tree\n");
    printf("  delete...\tDelete a value from the tree\n");
    printf("  inorder\tDisplay an inorder traversal of the tree\n");
    printf("  preorder\tDisplay a preorder traversal of the tree\n");
    printf("  postorder\tDisplay a postorder traversal of the tree\n");
    printf("  levelorder\tDisplay a levelorder traversal of the tree\n");
    printf("  max\t\tGet the max value\n");
    printf("  min\t\tGet the min value\n");
    printf("  average\tGet the average value\n");
    printf("  height\tGet the height of the tree\n");
    printf("  count\t\tGet the number of nodes in the tree\n");
    printf("  sum\t\tGet the sum of all values\n");
    printf("  quit\t\tQuit this program\n");
}

void print(int x)
{
    printf("%d ", x);
}
