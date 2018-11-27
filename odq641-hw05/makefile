CC = gcc
CFLAGS = -Wall -g

all: driver

tidy:
	rm -f ,* .,* *~ core a.out graphics.ps

scratch: tidy
	rm -f *.o *.a driver-list driver-array
	rm -r *.dSYM

tree.o:	tree.h tree.c
	$(CC) $(CFLAGS) -c tree.c

driver.o: tree.h driver.c
	$(CC) $(CFLAGS) -c driver.c

driver:	tree.o driver.o
	$(CC) $(CFLAGS) driver.o tree.o -o driver
