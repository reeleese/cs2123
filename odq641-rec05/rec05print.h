#ifndef _rec05print_h
#define _rec05print_h

#include <string.h>
#include <stdio.h>

int openCritPathInfo(FILE **, FILE **, char *argv[]);
void printHeader(FILE *);
void printFooter(FILE *, int);
void printEvent(FILE *, int, int, int);

#endif
