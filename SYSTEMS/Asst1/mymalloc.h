//
//  mymalloc.h
//  memgrind
//
//  Created by Dennis Kager and Ali Awari on 2/18/19.
//  Copyright © 2019 Dennis Kager and Ali Awari. All rights reserved.
//

#ifndef _MYMALLOC_h
#define _MYMALLOC_h

#include <stdio.h>

#define malloc(x) mymalloc(x, __FILE__, __LINE__) // Replace malloc() calls with mymalloc()
#define free(x) myfree(x, __FILE__, __LINE__)     // Replace free() calls with myfree()

typedef struct node
{                          // Define metadata struct
    struct node *nextNode; // Holds the address to the next node
    short spaceUsed;       // Holds how much memory the user is given for a given block
    _Bool inUse;           // Holds a value telling whether or not a block of memory is in use
} metadata;

void *mymalloc(int, const char *file, int line);  // Orchestrates when to create a new node, when to initialize, and error handling
void addNode(metadata *, int);                    // Will create a new metadata node
void defragment(void);                            // After freeing a node, will re-link the linked list properly
void *myfree(void *, const char *file, int line); // Frees memory from myblock

static char myblock[4096] = {15}; // Simulates a heap to manage and sets a 4 byte magic number

#endif /* _MYMALLOC_h */
