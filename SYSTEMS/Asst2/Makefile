CFLAGS= -g

all: fileCompressor clean test reset

fileCompressor: main.c HuffmanCodebook.o
	gcc $(CFLAGS) -o main main.c HuffmanCodebook.o

HuffmanCodebook.o: HuffmanCodebook.c HuffmanCodebook.h
	gcc $(CFLAGS) -c HuffmanCodebook.c

clean:
	-rm -f *.o
	-rm -f *.h.gch

test:
	./main -b tests/TestDirectory1/Dir1/test.txt

reset:
	-rm HuffmanCodebook.txt

# tar:
# 	tar --exclude='.git/*' --exclude='fileCompressor.dSYM/*' --exclude='.*' --exclude='*.md' --exclude='fileCompressor' -czvf ../Asst2.tar.gz ../Asst2
