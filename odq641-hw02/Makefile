# Makefile for programs for Homework 2
# Lee Reese odq641 
# ***************************************************************

PROGRAMS = \
    hw02

# ***************************************************************
# Parameters to control Makefile operation
# Note that the gccx command script must be defined

CC = gcc
CFLAGS = -Wall -g

# ***************************************************************
# Entry to bring the package up to date

all: $(PROGRAMS)

# ***************************************************************
# Standard entries to remove files from the directories
#    tidy    -- eliminate unwanted files
#    scratch -- delete derived files in preparation for rebuild

tidy:
	rm -f ,* .,* *~ core a.out graphics.ps

scratch: tidy
	rm -f *.o *.a $(PROGRAMS)

# ***************************************************************
# C compilations

hw02.o: hw02.c
	$(CC) $(CFLAGS) -c hw02.c


# ***************************************************************
# Executable programs

hw02: hw02.o
	$(CC) $(CFLAGS) -o hw02 hw02.o
