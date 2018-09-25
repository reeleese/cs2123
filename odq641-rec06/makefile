all: rec06

tidy:
	rm -f *.o *~ a.out
	rm -rf *.dSYM

# Compiler Flags:
# -g add debug info to executable
# -Wall turn on most warning flags
CC = clang
CFLAGS = -Wall -g

# C Compilations
rec05.o: rec06.c random.h
	$(CC) -c rec06.c

random.o: random.c random.h
	$(CC) -c random.c

# Executables
rec06: rec05.o rec05print.o
	$(CC) $(CFLAGS) -o rec05 rec05.o rec05print.o
