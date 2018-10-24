CC = clang
CFLAGS = -g -Wall

all: array list

setArrayImp.o: setArrayImp.c set.h
	$(CC) $(CFLAGS) -c setArrayImp.c

setLinkedList.o: setLinkedListImp.c set.h
	$(CC) $(CFLAGS) -c setLinkedList.c

driver.o: driver.c set.h
	$(CC) $(CFLAGS) -c driver.c

array: driver.o setArrayImp.o
	$(CC) $(CFLAGS) driver.o setArrayImp.o -o driver-array

list: driver.o setLinkedListImp.o
	$(CC) $(CFLAGS) driver.o setLinkedListImp.o -o driver-list
