all: calc.c format.c
	gcc -std=c99 calc.c -o calc
	gcc -std=c99 format.c -o format

calc: calc.c
	gcc -std=c99 -o calc calc.c

format: format.c
	gcc -std=c99 -o format format.c

clean:
	rm -f *.o calc
	rm -f *.o format