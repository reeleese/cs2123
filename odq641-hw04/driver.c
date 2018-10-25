#include "set.h"
#include <stdio.h>

void populateSet(setADT A, char* name);

int main() {
    setADT A, B;
    A = setNew();
    B = setNew();
    
    populateSet(A, "A");
    populateSet(B, "B");

    setPrint(A, "A");
    
    setFree(A);
    setFree(B);
    return 0;
}

void populateSet(setADT A, char *name)
{
    int num = 0;
    printf("Give values for %s (enter -1 to end input):\n", name);
    while (1) {
	printf("> ");
	scanf("%d", &num);
	if (num == -1) break;
	setInsertElementSorted(A, num);
    }
}
