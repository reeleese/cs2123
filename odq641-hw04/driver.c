#include "set.h"
#include <stdio.h>
#include <ctype.h>

void populateSet(setADT A, char* name);
void printCommands();
void printSets(setADT, setADT, setADT);

int main()
{
    setADT A, B, C;
    char user_option;
    int done;

    /* Populate A and B */
    A = setNew();
    B = setNew();
    populateSet(A, "A");
    populateSet(B, "B");

    /* Menu loop */
    done = 0;
    while (!done) {
	C = NULL;
	printf("\nEnter a Command:\n> ");
	scanf(" %c", &user_option);

	switch(toupper(user_option)) {
	  case 'U' : C = setUnion(A, B); printSets(A, B, C); break;
	  case 'I' : C = setIntersection(A, B); printSets(A, B, C); break;
	  case 'D' : C = setDifference(A, B); printSets(A, B, C); break;
	  case 'H' : printCommands(); break;
  	  case 'Q' : done = 1; break;
	  default  : printf("Unrecognized command \"%c.\"\n", user_option);
	             printf("Type 'H' for help.\n");
	}
    }/* while */

    /* Free A and B */
    setFree(A);
    setFree(B);
        
    return 0;
}

/* Fills set A with user input until -1 is entered */
void populateSet(setADT A, char *name)
{
    int num;  
    printf("Give values for %s (enter -1 to end input):\n", name);
    while (1) {
	printf("> ");
	scanf("%d", &num);
	if (num == -1) break;
	setInsertElementSorted(A, num);
    }
}

/* Prints commands for reference */
void printCommands()
{
    printf("You may use any of these commands:\n");
    printf("  U\tUnion of A and B\n");
    printf("  I\tIntersection of A and B\n");
    printf("  D\tDifference of A and B\n");
    printf("  H\tDisplay this menu\n");
    printf("  Q\tQuit\n");
}

/* Print A, B, and (conditionally) C */
void printSets(setADT A, setADT B, setADT C)
{   
    setPrint(A, "A");
    setPrint(B, "B");
    if (C) {
	setPrint(C, "C");
	printf("|C| = %d\n", setCardinality(C));
	setFree(C);
    }
}
