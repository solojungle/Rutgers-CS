CFLAGS= -g

all: memgrind clean

memgrind: memgrind.c mymalloc.o
	gcc $(CFLAGS) -o memgrind memgrind.c mymalloc.o

mymalloc.o: mymalloc.c mymalloc.h
	gcc $(CFLAGS) -c mymalloc.c

clean:
	-rm -f *.o
	-rm -f *.h.gch

# test:
# 	./memgrind

# tar:
# 	tar --exclude='.git/*' --exclude='memgrind.dSYM/*' --exclude='.*' --exclude='*.md' --exclude='shiftLeft (unused).c' --exclude='memgrind' -czvf ../Asst1.tar.gz ../Asst1