#ifndef _list_h_
#define _list_h_

typedef int listElementT;
typedef struct listCDT *listADT; // listADT is a pointer type!

/* Returns a new list */
listADT NewList();

/* Copies the first n items from a and returns a new list with those items */
listADT list_n_copy(listADT a, int n);

/* Frees memory allocated for a */
void FreeList(listADT a);

/* inserts val into a such that the item before val < val < item after val */
void list_insert_sorted(listADT a, listElementT val);

/* inserts val at the beginning of a */
void list_insert_unsorted(listADT a, listElementT val);

/* Prints values of a on one line, preceded by "name: " */
void list_print_values(listADT a, char *name);

/* Returns the average of all items in a */
double list_average(listADT a);

/* Removes an item equal to val if it is in the list */
void list_delete_by_value(listADT a, listElementT val);

#endif 
