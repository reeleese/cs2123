all: rec06

tidy:
	rm -f *.o *~ a.out
	rm -rf *.dSYM

# Compiler Flags:
# -g add debug info to executable
# -Wall turn on most warning flags
CC = gcc
CFLAGS = -Wall

# C Compilations
rec05.o: rec06.c random.h
	$(CC) -c rec06.c

random.o: random.c random.h
	$(CC) -c random.c

# Executables
rec06: rec06.o random.o
	$(CC) $(CFLAGS) -o rec06 rec06.o random.o
