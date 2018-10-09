#include <stdlib.h>
#include <stdio.h>
#include "list.h"
int main()
{
    int i;
    listADT X, Y;
    X = NewList();
    Y = NewList();

    listElementT userInput;
    for (i = 0; i < 6; ++i) {
	printf("Number %d: ", i);
	scanf("%d", &userInput);
	list_insert_sorted(X, userInput);
	list_insert_unsorted(Y, userInput);
    }
    
    list_insert_sorted(X, 9); //  why not list_insert_sorted(&X, 9);

   return 0;
}
