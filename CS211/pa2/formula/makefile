CFLAGS = -std=c99 -g -Wall

all: formula clean

formula: formula.c nCr.o
	gcc $(CFLAGS) -o formula formula.c nCr.o

nCr.o: nCr.s nCr.h
	gcc $(CFLAGS) -c nCr.s nCr.h

clean:
	-rm -f *.o
	-rm -f *.h.gch
