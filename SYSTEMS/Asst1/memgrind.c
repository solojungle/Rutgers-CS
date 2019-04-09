//
//  main.c
//  memgrind
//
//  Created by Dennis Kager and Ali Awari on 2/18/19.
//  Copyright © 2019 Dennis Kager and Ali Awari. All rights reserved.
//

#include <stdio.h>
#include <string.h>
#include <time.h>
#include <sys/time.h>
#include "mymalloc.h"

/* A: malloc() 1 byte and immediately free it - do this 150 times */
int testA()
{
    struct timeval start, end;
    gettimeofday(&start, NULL);
    
    int i = 0;
    while (i < 150)
    {
        char *a = malloc(1); // Malloc() 1 byte then immediately free()
        free(a);
        i++;
    }
    
    gettimeofday(&end, NULL);
    
    return (int)((end.tv_sec - start.tv_sec) / 10000000 + (end.tv_usec - start.tv_usec));
}

/*
 *   B: malloc() 1 byte, store the pointer in an array - do this 150 times.
 * Once you've malloc()ed 50 byte chunks, then free() the 50 1 byte pointers one by one.
 */
int testB()
{
    struct timeval start, end;
    gettimeofday(&start, NULL);
    
    char *array[50];
    int i = 0;
    int j = 0;
    int k = 0;
    
    while (i < 3) // Each i = 50 operations completed
    {
        // Malloc
        while (j < 50) // Malloc 50 bytes
        {
            array[j] = malloc(1);
            j += 1;
        }
        j = 0;
        
        // Free
        while (k < 50) // Free 50 bytes
        {
            free(array[k]);
            k += 1;
        }
        k = 0;
        
        i += 1;
    }
    
    gettimeofday(&end, NULL);
    return (int)((end.tv_sec - start.tv_sec) / 10000000 + (end.tv_usec - start.tv_usec));
}

/*
 *   C: Randomly choose between a 1 byte malloc() or free()ing a 1 byte pointer.
 * Keep track of each operation so that you eventually malloc() 50 bytes, in total.
 * Keep track of each operation so that you eventually free() all pointers.
 **/
int testC()
{
    struct timeval start, end;
    gettimeofday(&start, NULL);
    
    int boolean;            // Random number.
    int operationCount = 0; // Total amount of malloc() pointers.
    int totalPointers = 0;  // Amount of pointers in array.
    int *slots[50];         // Pointer storage.
    
    unsigned long int randomNumber = time(NULL); // Seed for random number.
    
    while (operationCount < 50) // do this until you have allocated 50 times
    {
        randomNumber = (unsigned int)(((randomNumber * 1103515245 + 12345) / 65536) % 32768);
        boolean = randomNumber % 2;
        if (boolean) // If malloc()ing
        {
            operationCount += 1;              // Increment operation count
            slots[totalPointers] = malloc(1); // Malloc 1 byte to array at index
            totalPointers += 1;               // Increment pointer count
        }
        else // If free()ing
        {
            if (totalPointers > 0) // Only free if there is at least one pointer
            {
                free(slots[totalPointers - 1]); // Free pointer at index
                totalPointers -= 1;             // Update pointer count
            }
        }
    }
    
    // Loop frees any remaining pointers
    while (totalPointers > 0)
    {
        free(slots[totalPointers - 1]); // Must subtract 1 from totalPointers to account for the increment after adding a pointer
        totalPointers -= 1;             // Update pointer count
    }
    
    gettimeofday(&end, NULL);
    return (int)((end.tv_sec - start.tv_sec) / 10000000 + (end.tv_usec - start.tv_usec));
}

/*
 *   D: Randomly choose between a randomly-sized malloc() or free()ing a pointer – do this many times
 * Keep track of each malloc so that all mallocs do not exceed your total memory capacity
 * Keep track of each operation so that you eventually malloc() 50 times
 * Keep track of each operation so that you eventually free() all pointers
 * Choose a random allocation size between 1 and 64 bytes
 **/
int testD()
{
    struct timeval start, end;
    gettimeofday(&start, NULL);
    
    int boolean = 0;                             // Random number.
    int memoryAmount = 0;                        // Randomly chosen amount of memory (between 1-64).
    int *randomMemoryArray[200];                 // Holds pointers.
    int sizeOfMemory[200];                       // Holds size of pointers.
    int operationCount = 0;                      // Number of operations.
    int remainingMemory = 4096;                  // Amount of remaining memory from malloc.
    int totalPointers = 0;                       // Total number of pointers.
    unsigned long int randomNumber = time(NULL); // Seed for random number.
    
    while (operationCount < 50) // Keep track of each operation so that you eventually malloc() 50 times.
    {
        randomNumber = (unsigned int)(((randomNumber * 1103515245 + 12345) / 65536) % 32768);
        boolean = randomNumber % 2;
        
        if (boolean) // Randomly choose between a randomly-sized malloc() or free()ing a pointer – do this many times.
        {
            memoryAmount = (randomNumber % 64) + 1; // Choose a random allocation size between 1 and 64 bytes.
            
            if ((memoryAmount + sizeof(metadata)) <= remainingMemory) // Keep track of each malloc so that all mallocs do not exceed your total memory capacity.
            {
                remainingMemory -= memoryAmount + sizeof(metadata);            // Update remaining memory to use
                randomMemoryArray[totalPointers] = malloc(memoryAmount);       // Allocates memory to address in array
                sizeOfMemory[totalPointers] = memoryAmount + sizeof(metadata); // Respective array to randomMemoryArray that keeps track of what size each pointer is
                totalPointers += 1;                                            // Increment pointer count
                operationCount += 1;                                           // Increment operation count
            }
        }
        else // Execute if freeing a pointer was randomly chosen
        {
            if (totalPointers > 0) // Only free if there are available pointers to free
            {
                remainingMemory += sizeOfMemory[totalPointers - 1]; // Update remaining memory to use
                free(randomMemoryArray[totalPointers - 1]);         // Free memory at the array index
                
                totalPointers -= 1; // Update pointer count
            }
        }
    }
    
    while (totalPointers > 0) // If at the end, there are still pointers, then free any remaining pointers
    {
        remainingMemory += sizeOfMemory[totalPointers - 1]; // Update remaining memory
        free(randomMemoryArray[totalPointers - 1]);         // Free pointer at array index
        totalPointers -= 1;                                 // Update pointer count
    }
    
    gettimeofday(&end, NULL);
    return (int)((end.tv_sec - start.tv_sec) / 10000000 + (end.tv_usec - start.tv_usec));
}

/* E: Checking edge case where a user requests memory and we have enough memory in a block for the user,
 but not enough memory to make a new metadata block -- Test runs 150 times*/
int testE()
{
    struct timeval start, end;
    gettimeofday(&start, NULL);
    
    int i;
    for (i = 0; i < 150; ++i)
    {
        int *var1 = (int *)malloc(4029 * sizeof(char)); // After Malloc, 35 bytes remain
        int *var2 = (int *)malloc(30 * sizeof(char));   // We have 35 bytes but that will leave only 5 bytes for metadata -- not enough so all bytes are returned
        free(var1);
        free(var2);
    }
    
    gettimeofday(&end, NULL);
    return (int)((end.tv_sec - start.tv_sec) / 10000000 + (end.tv_usec - start.tv_usec));
}

/* F: Filling all of memory up and testing the effectiveness of defragment() after freeing 150 times*/
int testF()
{
    int metadataSize = sizeof(metadata);
    struct timeval start, end;
    gettimeofday(&start, NULL);
    
    int i;
    for (i = 0; i < 150; ++i)
    {
        // Use all available memory.
        int *a = malloc(4096 - metadataSize);
        free(a);
        
        // See if above free was successful.
        int *b = malloc(500);
        free(b);
        // [1, 0, 0, 1] -> [1, 0, 1]
        // Check to see if defragment is working.
        char *e = malloc(1024 - metadataSize);
        char *f = malloc(1024 - metadataSize);
        char *g = malloc(1024 - metadataSize);
        char *h = malloc(1024 - metadataSize); // All memory is used up
        free(f);                               //Free f and g to frees two middle nodes and condenses it to one node
        free(g);
        f = malloc(2048 - metadataSize); // Malloc entire space of the one free node in the middle
        free(h);                         // Free the rest of the nodes
        free(f);
        free(e);
        e = malloc(4096 - sizeof(metadata)); // Use up all space in the array again
        free(e);                             // Free up all space
    }
    
    gettimeofday(&end, NULL);
    return (int)((end.tv_sec - start.tv_sec) / 10000000 + (end.tv_usec - start.tv_usec));
}

int main(int argc, const char *argv[])
{
    float totalForTestA = 0.0; // Holds the sum of all the test times
    float totalForTestB = 0.0;
    float totalForTestC = 0.0;
    float totalForTestD = 0.0;
    float totalForTestE = 0.0;
    float totalForTestF = 0.0;
    
    int i;
    for (i = 0; i < 100; ++i)
    {
        totalForTestA += testA();
        totalForTestB += testB();
        totalForTestC += testC();
        totalForTestD += testD();
        totalForTestE += testE();
        totalForTestF += testF();
    }
    
    printf("%sAFTER 100 TRIALS:%s\n", "\x1B[32m", "\033[0m"); // Outputs averaged test times
    printf("%sTEST A AVERAGE: %.2f microseconds%s\n", "\x1B[32m", totalForTestA / 100, "\033[0m");
    printf("%sTEST B AVERAGE: %.2f microseconds%s\n", "\x1B[32m", totalForTestB / 100, "\033[0m");
    printf("%sTEST C AVERAGE: %.2f microseconds%s\n", "\x1B[32m", totalForTestC / 100, "\033[0m");
    printf("%sTEST D AVERAGE: %.2f microseconds%s\n", "\x1B[32m", totalForTestD / 100, "\033[0m");
    printf("%sTEST E AVERAGE: %.2f microseconds%s\n", "\x1B[32m", totalForTestE / 100, "\033[0m");
    printf("%sTEST F AVERAGE: %.2f microseconds%s\n", "\x1B[32m", totalForTestF / 100, "\033[0m");
    
    return 0;
}
