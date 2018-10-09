#ifndef _list_h_
#define _list_h_

typedef int listElementT;
typedef struct listCDT *listADT; // listADT is a pointer type!

listADT NewList();
listADT list_n_copy(listADT a, int n);
void FreeList(listADT a);
void list_insert_sorted(listADT a, listElementT val); 
void list_insert_unsorted(listADT a, listElementT val); 
void list_print_values(listADT a, char *name);
double list_average(listADT a);

#endif 
