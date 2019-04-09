//
//  mymalloc.c
//  memgrind
//
//  Created by Dennis Kager and Ali Awari on 2/18/19.
//  Copyright © 2019 Dennis Kager and Ali Awari. All rights reserved.
//

#include "mymalloc.h"
#define magicNum 15 // Magic number

/*
 *   printNodes()
 *   @params: void
 *   @returns: void
 *   @comments: prints all current nodes in heap, used for debugging.
 **/
void printNodes()
{
    printf("\n");
    int i = 0;
    metadata *current = (void *)myblock;
    while (current != NULL)
    {
        i += 1;
        printf("%s%p : %i : %i%s\n", "\x1B[34m", current, current->spaceUsed, current->inUse, "\033[0m");
        current = current->nextNode;
    }
    printf("Total nodes: %i\n", i);
    printf("\n");
}

/*
 *   mymalloc()
 *   @params:
 *       int bytesRequested: The amount of memory the user requested
 *       const char* file: Holds the file name of the parent
 *       int line: Holds the line number of the parent
 *   @returns: void *usermemory
 *   @comments: Returns a pointer to a user that contains an address to a block of memory in myblock[]
 **/
void *mymalloc(int bytesRequested, const char *file, int line)
{
    metadata *cursor = (void *)myblock; // Points to the first node in myblock[]
    metadata *currentNode = NULL;       // currentNode is used to traverse through the list
    void *userMemory = NULL;            // Memory that will be used to
    int *testInit = (int *)myblock;     // Converts the first 4 bytes of the array to get an integer number

    // If user asks for improper memory, throw error.
    if (bytesRequested <= 0)
    {
        fprintf(stderr, "\nERROR: Please request a valid size of memory.\n"
                        "File: %s\n"
                        "Line: %d\n",
                file, line);
        return NULL;
    }

    // If user calls mymalloc() for the first time, then initialize first node
    if (*testInit == magicNum)
    {
        cursor->inUse = 0;
        cursor->spaceUsed = 4096 - sizeof(metadata);
        cursor->nextNode = NULL;
    }

    currentNode = cursor; // Set the currentNode to the cursor

    // Traverse through linked list until either suitable space is found or the end is reached
    while ((currentNode->inUse == 1 || currentNode->spaceUsed < bytesRequested) && currentNode->nextNode != NULL)
    {
        currentNode = currentNode->nextNode;
    }

    // If the space requested + sizeof(metadata) is exactly equal to an available node
    if (currentNode->spaceUsed == bytesRequested)
    {
        currentNode->inUse = 1;               // Set the current node's status to "in-use"
        userMemory = (void *)(++currentNode); // Point userMemory to the space to return

        return userMemory; // Return space to the user
    }

    // If the current node's space is larger than what the user requested, then divide the node to get exact space
    else if (currentNode->spaceUsed > (bytesRequested + sizeof(metadata)))
    {
        addNode(currentNode, bytesRequested); // Add a node to the linked list
        userMemory = (void *)(++currentNode); // Point userMemory to the space to return

        return userMemory; // Return space to the user
    }

    // If the space is large enough for what the user wants but not enough for metadata
    else if ((currentNode->spaceUsed > (bytesRequested)) && (currentNode->spaceUsed < (bytesRequested + sizeof(metadata))))
    {
        currentNode->inUse = 1;               // Set the current node's status to "in-use"
        userMemory = (void *)(++currentNode); // Point userMemory to the space to return

        return userMemory; // Return space to the user -- This space may be slightly more than what the user requested
    }

    // No memory could be sent back to the user -- Return NULL
    else
    {
        userMemory = NULL;
        fprintf(stderr, "\nERROR: Unable to allocate %d byte(s) of memory.\n"
                        "File: %s\n"
                        "Line: %d\n",
                bytesRequested, file, line);
        return userMemory; // Return NULL to the user
    }
}

/*
 *   addNode()
 *   @params:
 *           metadata *oldNode: The old node to split
 *           int bytesRequested: The amount of memory the user requested
 *   @returns: void
 *   @comments: Takes node space larger than what user requested and splits it to give the user the exact amount and store the remaining
 *              space in a new node
 **/
void addNode(metadata *oldNode, int bytesRequested)
{
    // Allocate some space for the new node
    metadata *newNode = (void *)((void *)oldNode + bytesRequested + sizeof(metadata));
    newNode->inUse = 0; // Set the new node so it is not in-use
    // Set the space used in the new node to to the free space - bytesRequested - the size of a metadata node
    newNode->spaceUsed = oldNode->spaceUsed - bytesRequested - sizeof(metadata);
    newNode->nextNode = NULL; // Set new node's pointer to what the old node pointed to

    oldNode->inUse = 1;                  // Set the old node to in-use
    oldNode->spaceUsed = bytesRequested; // Set the space in the old node to exactly what the user asked for
    oldNode->nextNode = newNode;         // Point the old node to the new node
}

/*
 *   defragment()
 *   @params: void
 *   @returns: void
 *   @comments: Combines consecutive free nodes
 **/

void defragment()
{
    metadata *head = (void *)myblock; // Points to the first node in myblock[]
    metadata *current = head;         // Sets the current node to the cursor

    // While neither the current nor next node's are NULL
    while ((current != NULL) && (current->nextNode != NULL))
    {
        // If the current node and next node are not in use
        if ((current->inUse == 0) && (current->nextNode->inUse == 0))
        {
            current->spaceUsed += current->nextNode->spaceUsed + sizeof(metadata); // Combine space
            // Set's current's next node to two (2) nodes ahead of it to re-link
            current->nextNode = current->nextNode->nextNode;
            defragment();
        }
        current = current->nextNode; // Traverse to next node
    }
}

/*
 *   myfree()
 *   @params:
 *       void * memory: pointer which is requested to be deleted.
 *       const char* file: Holds the file name of the parent
 *       int line: Holds the line number of the parent
 *   @returns: void
 *   @comments: Changes metadata of node to allow overwritting, then defragments data array,
 *   undefined behavior may occur on big endian machines.
 **/
void *myfree(void *memory, const char *file, int line)
{
    _Bool foundFlag = 0; // Flag used in the testing of whether or not a match has been found between nodes and the pointer passed-in

    /* If user supplies a pointer with the value of NULL */
    if (memory == NULL)
    {
        fprintf(stderr, "\nERROR: Given pointer is NULL.\n"
                        "File: %s\n"
                        "Line: %d\n",
                file, line);
        return NULL;
    }

    /*
     *   Checks to see if pointer has memory address residing in the heap,
     *   if it does, then one little endian machines it will not have been
     *   malloced by mymalloc.
     *
     *   A: Free()ing addresses that are not pointers.
     *   B: Free()ing pointers that were not allocated by malloc().
     **/

    metadata *cursor = (void *)myblock;

    while (cursor != NULL)
    {
        if (memory - sizeof(metadata) == cursor)
        {
            foundFlag = 1; // If the (address - metadata) matches the address of a node, then a match has been found
            break;
        }
        else
            cursor = cursor->nextNode;
    }

    if (foundFlag == 0) // If match has not been found, then throw error
    {
        fprintf(stderr, "\nERROR: Pointer is not associated with malloc().\n"
                        "File: %s\n"
                        "Line: %d\n",
                file, line);
        return NULL;
    }

    metadata *currentNode = memory - (sizeof(metadata)); // Points sizeof(metadata) bytes in front of actual metadata.

    /* C: Redundant free()ing of the same pointer. */
    if (currentNode->inUse == 0) // If memory address matches, but the node is not in use, then it is redundant free()ing
    {
        fprintf(stderr, "\nERROR: Redundant free()ing of the same pointer.\n"
                        "File: %s\n"
                        "Line: %d\n",
                file, line);
        return NULL;
    }

    currentNode->inUse = 0; // If none of the above error conditions are met, then set the current->inUse to zero and free pointer

    defragment(); // Call to ensure we get maximum space by combining consecutive free memory blocks together

    return NULL;
}
