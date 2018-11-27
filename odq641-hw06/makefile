all: graph

# Compiler Flags
CC = gcc -I booklib
CFLAGS = -g -Wall

# Cleanup
tidy:
	rm -f ,* .,* *~ core a.out graphics.ps

scratch: tidy
	rm -f *.o *.a driver

# C compilations
stack.o: stack.c stack.h
	$(CC) $(CFLAGS) -c stack.c

qlist.o: qlist.c queue.h
	$(CC) $(CFLAGS) -c qlist.c

graph.o: graph.c stack.h queue.h
	$(CC) $(CFLAGS) -c graph.c

# Executable
graph: graph.o stack.o qlist.o
	$(CC) $(CFLAGS) -o graph graph.o stack.o qlist.o booklib/cslib.a
