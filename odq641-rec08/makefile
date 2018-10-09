all: driver

# Cleanup
tidy:
	rm -f ,* .,* *~ core a.out graphics.ps

scratch: tidy
	rm -f *.o *.a $(PROGRAMS)

# Compiler Flags
CC = gcc
CFLAGS = -g -Wall

# C Compilations
list.o: list.h list.c
	gcc -c list.c

driver.o: driver.c list.h
	gcc -c driver.c

# Executable
driver:	list.o driver.o
	gcc -o driver driver.o list.o
