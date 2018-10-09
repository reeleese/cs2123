#include <stdlib.h>
#include <stdio.h>
#include "list.h"
int main()
{
    int i;
    listADT X, Y;
    X = NewList();
    Y = NewList();

    /* Populate lists X and Y */
    listElementT userInput;
    for (i = 0; i < 6; ++i) {
	printf("Number %d: ", i+1);
	scanf("%d", &userInput);
	list_insert_sorted(X, userInput);
	list_insert_unsorted(Y, userInput);
    }

    /* Print X and Y */
    list_print_values(X, "X");
    list_print_values(Y, "Y");

    /* Print averages for X and Y */
    double X_average, Y_average;
    X_average = list_average(X);
    Y_average = list_average(Y);
    printf("X average: %g\n", X_average); 
    printf("Y average: %g\n", Y_average); 

    /* Get values to remove from X and Y. Remove them */
    listElementT X_target, Y_target;
    printf("Value to delete from X: ");
    scanf("%d", &X_target);
    printf("Value to delete from Y: ");
    scanf("%d", &Y_target);

    list_delete_by_value(X, X_target);
    list_delete_by_value(Y, Y_target);

    /* Print X and Y */
    list_print_values(X, "X");
    list_print_values(Y, "Y");
    
    /* Copy first 3 elements of X to new list Z and print Z */
    listADT Z;
    Z = list_n_copy(X, 3);
    list_print_values(Z, "Z");

    /* Print average for Z */
    double Z_average;
    Z_average = list_average(Z);
    printf("Z average: %g\n", Z_average);
    
    /* Free lists*/
    FreeList(X);
    FreeList(Y);
    FreeList(Z);

   return 0;
}
