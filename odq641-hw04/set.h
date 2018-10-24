#ifndef _set_h
#define _set_h

typedef int setElementT;
typedef struct setCDT *setADT;

setADT setNew();
void setFree();

int setInsertElementSorted(setADT A, setElementT item);

setADT setUnion(setADT A, setADT B);
setADT setIntersection(setADT A, setADT B);
setADT setDifference(setADT A, setADT B);

int setCardinality(setADT A);
void setPrint(setADT A, char *name);

#endif
