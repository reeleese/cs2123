all: driver

# Compiler Flags
CC = clang -I booklib
CFLAGS = -g -Wall

# Cleanup
tidy:
	rm -f ,* .,* *~ core a.out graphics.ps

scratch: tidy
	rm -f *.o *.a driver

# C compilations
stack.o: stack.c stack.h
	$(CC) $(CFLAGS) -c stack.c

driver.o: driver.c stack.h
	$(CC) $(CFLAGS) -c driver.c

# Executable
driver: stack.o driver.o
	$(CC) $(CFLAGS) -o driver driver.o stack.o booklib/cslib.a
