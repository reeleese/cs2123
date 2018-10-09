#ifndef _list_h_
#define _list_h_

typedef int listElementT;
typedef struct listCDT *listADT; // listADT is a pointer type!

listADT NewList();
void list_insert_sorted(listADT a, listElementT val); 
void list_insert_unsorted(listADT a, listElementT val); 
     // just add val to end of the list
#endif 
