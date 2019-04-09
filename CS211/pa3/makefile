CFLAGS = -std=c99 -g -Wall

all: y86emul

y86emul: y86emul.c
	gcc $(CFLAGS) -o y86emul y86emul.c

clean:
	-rm -f *.o
	-rm -f *.h.gch
