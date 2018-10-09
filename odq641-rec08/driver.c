#include <stdlib.h>
#include <stdio.h>
#include "list.h"
int main()
{
   listADT X;
   X = NewList(); 
   list_insert_sorted(X, 9); //  why not list_insert_sorted(&X, 9);

   return 0;
}
