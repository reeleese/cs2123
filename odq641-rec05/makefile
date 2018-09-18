all: client
tidy:
	rm -f *.o *~ a.out

# compiler flags:
# -g add debug info to executable
# -Wall turn on most warning flags
# -o
CC = clang
CFLAGS = -g -Wall

# C Compilations
rec05.o: rec05.c rec05print.h
	$(CC) -c rec05.c

rec05print.o: rec05print.c rec05print.h
	$(CC) -c rec05print.c

# Executables
client: rec05.o rec05print.o
	$(CC) $(CFLAGS) -o rec05 rec05.o rec05print.o
