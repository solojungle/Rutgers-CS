//
//  HuffmanCodebook.h
//  fileCompressor
//
//  Created by Dennis Kager on 3/12/19.
//  Copyright © 2019 Dennis Kager and Ali Awawri. All rights reserved.
//

#ifndef __HUFFMANCODEBOOK__
#define __HUFFMANCODEBOOK__

#include <stdio.h>

typedef struct branch
{
    char *leaf;
    struct branch *left;
    struct branch *right;
} Tree;

typedef struct node
{
    char *token;           // Holds a token from a string
    int freq;              // Holds the frequency in which a token occurs
    struct node *nextNode; // Holds the address to the next node
    struct node *prevNode; // Holds the address to the previous node
} strNode;

// ========================================================================================

typedef struct node_type
{
    int frequency;
    char *string;
    struct node_type *left;
    struct node_type *right;
} MinNode;

typedef struct minheap_type
{
    int capacity;
    int size;
    MinNode **array;
} MinHeap;

typedef struct huffmancode_type
{
    char *string;
    char *code;
} HuffNode;

typedef struct huffmanlist_type
{
    int size;
    int capacity;
    HuffNode **array;
} HuffList;

typedef struct book_node
{
    char *code;
    char *token;
    struct book_node *nextNode;
    struct book_node *prevNode;
}BookTokens;

/**
 *  Forward Declarations
 **/
// Functions for tokenizing and managing the linked list
strNode* tokenize(const char*, strNode*); // Returns linked list of file tokens and frequencies
void addNode (strNode*, char*); // Adds nodes to linked list in through tokenize()
int searchNodes (strNode*, char*); // Searches for duplicate nodes in tokenize()
void printList(strNode*); // For debugging: Prints the linked list of tokens and their frequencies
void freeList(strNode*); // Frees the dynamic memory from the linked list
// Functions for creating and/or handling a codebook
MinHeap* buildHeap(strNode*);
_Bool outputCodebook(HuffList*);
BookTokens* tokenBook(char*); // Get tokenized codebook
void printBookTokens(BookTokens*);
void freeBook(BookTokens*);

MinHeap *initializeHeap(unsigned);
MinNode *initializeMinNode(int, char *);
MinNode *pop(MinHeap *);
MinNode *buildCodebook(MinHeap *);
void insert(MinHeap *, MinNode *);
void swap(MinNode **, MinNode **);
void percolateUp(MinHeap *);
void percolateDown(MinHeap *, int);
HuffList* generateCodes(MinNode *, int);
_Bool compress(BookTokens*, const char*);
char* getCodes(BookTokens*, char*);
char *findString(BookTokens*, char *);
_Bool decompress(BookTokens*, const char *);
// DEBUG
void printHeap(MinHeap *);
void printBook(MinNode *);

#endif /* __HUFFMANCODEBOOK__ */
