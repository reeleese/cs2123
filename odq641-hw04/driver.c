#include "set.h"
#include <stdio.h>
#include <ctype.h>

void populateSet(setADT A, char* name);
void printCommands();

int main()
{
    setADT A, B, C;
    char user_option;
    A = setNew();
    B = setNew();
    
    /* Get user input to populate A and B */
    populateSet(A, "A");
    populateSet(B, "B");

    /* Menu loop */
    int done = 0;
    while (!done) {
	C = NULL;
	printf("Command: ");
	scanf(" %c", &user_option);

	switch(toupper(user_option)) {
	  case 'U' : C = setUnion(A, B); break;
	  case 'I' : C = setIntersection(A, B); break;
	  case 'D' : C = setDifference(A, B); break;
	  case 'H' : printCommands(); break;
  	  case 'Q' : done = 1; break;
	  default  : printf("Unrecognized command \"%c\"\n", user_option);
	}
        
	setPrint(A, "A");
	setPrint(B, "B");
	if (C) {
	    setPrint(C, "C");
	    printf("Cardinality of C: %d\n", setCardinality(C));
	    setFree(C);
	}
    }

    /* Free A and B */
    setFree(A);
    setFree(B);
        
    return 0;
}

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

void printCommands()
{
    printf("Q\tQuit\n");
    printf("U\tUnion\n");
    printf("I\tIntersection\n");
    printf("D\tDifference\n");
    printf("H\tDisplay this menu\n");
}
