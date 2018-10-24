#include "set.h"
#include <stdio.h>

void populateSet(setADT A, char* name);

int main() {
    setADT A, B;
    A = setNew();
    B = setNew();
    populateSet(A, "A");
    populateSet(B, "B");
    
    
    return 0;
}

void populateSet(setADT A, char *name)
{
    setElementT num = 0;
    printf("Give values for %s (enter -1 to end input):\n", name);
    while (num != -1) {
	printf("> ");
	scanf("%d", num);
	setInsertElementSorted(A, &num);
    }
}
