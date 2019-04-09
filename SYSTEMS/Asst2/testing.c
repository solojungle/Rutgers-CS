#include <stdio.h>
#include <stdlib.h>
#include "HuffmanCodebook.h"
#include "decompress.c"
int main(int argc, const char *argv[])
{

    MinHeap *heap = malloc(sizeof(MinHeap));
    heap = initializeHeap(3);

    insert(heap, initializeMinNode(1, "i"));
    insert(heap, initializeMinNode(2, "love"));
    insert(heap, initializeMinNode(3, "you"));
    insert(heap, initializeMinNode(4, "so"));
    insert(heap, initializeMinNode(5, "much"));
    insert(heap, initializeMinNode(6, "khamis"));
    insert(heap, initializeMinNode(7, "~"));
    insert(heap, initializeMinNode(8, "|"));


    HuffList *codes = malloc(sizeof(HuffList));
    codes = generateCodes(buildCodebook(heap), heap->size);

    // printCodes(codes);


// 11010 01 11011 01 1100 01 100 01 101 01 111 00

    char * example = "1101001110110111000110001101011110011011";

    printf("%s\n", decompress(codes, example));

    return 0;
}