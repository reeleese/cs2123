all: driver

CC = clang
CFLAGS = -Wall -g

tree.o:	tree.h tree.c
	$(CC) $(CFLAGS) -c tree.c

driver.o: tree.h driver.c
	$(CC) $(CFLAGS) -c driver.c

driver:	tree.o driver.o
	$(CC) $(CFLAGS) driver.o tree.o -o driver
