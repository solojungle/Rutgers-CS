//
//  HuffmanCodebook.c
//  fileCompressor
//
//  Created by Dennis Kager on 3/12/19.
//  Copyright © 2019 Dennis Kager and Ali Awari. All rights reserved.
//

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <dirent.h>
#include <fcntl.h> // For open() and write()
#include <unistd.h> // For read()
#include <ctype.h> // For isdigit() and isalpha()
#include "HuffmanCodebook.h"

_Bool fatalErrorHuffman = 0; // Used for terminating program in the event of an Error
_Bool initCodebookFile = 1; // Used to know if a codebook file needs to be started

strNode* tokenize(const char *path, strNode* list){
    strNode *head = NULL;
    strNode *cursor = NULL;
    char buffer = ' '; // Holds characters from file
    int rd = open(path, O_RDONLY);
    int status = 0;
    char string[500][500]; // Holds strings found in the file
    int i = 0; // Index of tokens
    int j = 0; // Elements of individual tokens
    _Bool wordExists = 0; // Used to tell if a word/token already is an elements in the linked list
    _Bool delimExists = 0; // Used to tell if a delimiter already exists in the linked list
    _Bool skip = 0; // Used to tell if the file starts with a delimiter to initialize the linked list
    _Bool cont = 1; // Used to control when to loop through the list to setup a new node
    _Bool newToken = 0; // Used to tell if a new, non-delimiter, token has been started
    
    if(list == NULL){ // If list is empty, then setup as a new linked list
        head = malloc(sizeof(strNode));
        head -> token = NULL;
    }
    else // If the list already has tokens, then set head to the beginning of the list
        head = list;
    
    if(rd != -1){
        do{
            status = (int)read(rd, &buffer, 1);
            if(status > 0){
                // IF HEAD DOES NOT EXIST YET
                if(head -> token == NULL){
                    if(buffer != ' ' && buffer != '\n' && buffer != '\t'){
                        string[i][j] = buffer;
                        ++j;
                    }
                    else if (buffer == ' ' || buffer == '\n' || buffer == '\t'){
                        string[i][j] = '\0';
                        if(strlen(string[i]) != 0){ // If the string does not start with a delimiter
                            head -> token = (char*)malloc((strlen(&string[i][j])) * sizeof(char));
                            if(head -> token == NULL)
                                goto Error;
                            head -> nextNode = NULL;
                            head -> prevNode = NULL;
                            head -> freq = 1;
                            strcpy(head -> token, string[i]);
                            ++i; // increment token counter
                            j = 0; // Reset character counter
                        }
                        else if(strlen(string[i]) == 0) // If string starts with delimiter, then set skip to true
                            skip = 1;
                        if(buffer == ' ') {
                            if(skip == 0){ // If skip is false, then add new token to the list
                                cursor = head;
                                cursor -> nextNode = malloc(sizeof(strNode));
                                if(cursor -> nextNode == NULL)
                                    goto Error;
                                string[i][j] = '|';
                                ++j;
                                string[i][j] = '\0';
                                addNode(cursor, string[i]);
                                ++i; // increment token counter
                                j = 0; // Reset character counter
                            }
                            else if(skip == 1){ // If skip is true, then initialize linked list
                                string[i][j] = '|';
                                ++j;
                                string[i][j] = '\0';
                                head -> token = (char*)malloc((strlen(&string[i][j])) * sizeof(char));
                                if(head -> token == NULL)
                                    goto Error;
                                head -> nextNode = NULL;
                                head -> prevNode = NULL;
                                head -> freq = 1;
                                strcpy(head -> token, string[i]);
                                ++i; // increment token counter
                                j = 0; // Reset character counter
                            }
                        }
                        else if(buffer == '\n') {
                            if(skip == 0){ // If skip is false, then add new token to the list
                                cursor = head;
                                cursor -> nextNode = malloc(sizeof(strNode));
                                if(cursor -> nextNode == NULL)
                                    goto Error;
                                string[i][j] = '~';
                                ++j;
                                string[i][j] = '\0';
                                addNode(cursor, string[i]);
                                ++i; // increment token counter
                                j = 0; // Reset character counter
                            }
                            else if(skip == 1){ // If skip is true, then initialize linked list
                                string[i][j] = '|';
                                ++j;
                                string[i][j] = '\0';
                                head -> token = (char*)malloc((strlen(&string[i][j])) * sizeof(char));
                                if(head -> token == NULL)
                                    goto Error;
                                head -> nextNode = NULL;
                                head -> prevNode = NULL;
                                head -> freq = 1;
                                strcpy(head -> token, string[i]);
                                ++i; // increment token counter
                                j = 0; // Reset character counter
                            }
                        }
                        else if(buffer == '\t') {
                            if(skip == 0){ // If skip is false, then add new token to the list
                                cursor = head;
                                cursor -> nextNode = malloc(sizeof(strNode));
                                if(cursor -> nextNode == NULL)
                                    goto Error;
                                string[i][j] = '`';
                                ++j;
                                string[i][j] = '\0';
                                addNode(cursor, string[i]);
                                ++i; // increment token counter
                                j = 0; // Reset character counter
                            }
                            else if(skip == 1){ // If skip is true, then initialize linked list
                                string[i][j] = '|';
                                ++j;
                                string[i][j] = '\0';
                                head -> token = (char*)malloc((strlen(&string[i][j])) * sizeof(char));
                                if(head -> token == NULL)
                                    goto Error;
                                head -> nextNode = NULL;
                                head -> prevNode = NULL;
                                head -> freq = 1;
                                strcpy(head -> token, string[i]);
                                ++i; // increment token counter
                                j = 0; // Reset character counter
                            }
                        }
                    }
                }
                
                // IF HEAD EXISTS
                else if(head -> token != NULL){
                    if(cont == 1){ // Only loop once new token(s) have been added to the linked list
                        cursor = head;
                        while(cursor -> nextNode != NULL) // Loop until at the end of the list
                            cursor = cursor -> nextNode;
                        
                        cursor -> nextNode = malloc(sizeof(strNode));
                        if(cursor -> nextNode == NULL)
                            goto Error;
                        cont = 0;
                    }
                    if(buffer != ' ' && buffer != '\n' && buffer != '\t'){
                        string[i][j] = buffer;
                        ++j;
                        newToken = 1; // A new token has been started
                    }
                    else if (buffer == ' ' || buffer == '\n' || buffer == '\t'){
                        printf("\nCALLED\n\n");
                        if(newToken == 1){ // Only execute if a new token has been started
                            string[i][j] = '\0'; // Ends the string with the null terminator
                            wordExists = searchNodes(head, string[i]); // Checks to see if the token already exists
                            ++i; // increment token counter
                            j = 0; // Reset character counter
                            newToken = 0; // Set new token back to false
                        }
                        else if(newToken == 0) // If no new token is found, then assume that it already exists
                            wordExists = 1;
                        if(buffer == ' ') {
                            string[i][j] = '|';
                            ++j;
                            string[i][j] = '\0';
                            delimExists = searchNodes(head, string[i]);
                            
                            if(wordExists == 0){ // If the token does not exist in the list, then add it
                                addNode(cursor, string[i-1]);
                                cont = 1;
                            }
                            if(wordExists == 0 && delimExists == 0){
                                cursor = cursor -> nextNode;
                                cursor -> nextNode = malloc(sizeof(strNode));
                                if(cursor -> nextNode == NULL)
                                    goto Error;
                                addNode(cursor, string[i]);
                                cont = 1;
                            }
                            else if(wordExists == 1 && delimExists == 0){
                                addNode(cursor, string[i]);
                                cont = 1;
                            }
                            
                            ++i; // increment token counter
                            j = 0; // Reset character counter
                        }
                        else if(buffer == '\n') {
                            string[i][j] = '~';
                            ++j;
                            string[i][j] = '\0';
                            delimExists = searchNodes(head, string[i]);
                            
                            if(wordExists == 0){ // If the token does not exist in the list, then add it
                                addNode(cursor, string[i-1]);
                                cont = 1;
                            }
                            if(wordExists == 0 && delimExists == 0){
                                cursor = cursor -> nextNode;
                                cursor -> nextNode = malloc(sizeof(strNode));
                                if(cursor -> nextNode == NULL)
                                    goto Error;
                                addNode(cursor, string[i]);
                                cont = 1;
                            }
                            else if(wordExists == 1 && delimExists == 0){
                                addNode(cursor, string[i]);
                                cont = 1;
                            }
                            
                            ++i; // increment token counter
                            j = 0; // Reset character counter
                        }
                        else if(buffer == '\t') {
                            string[i][j] = '`';
                            ++j;
                            string[i][j] = '\0';
                            delimExists = searchNodes(head, string[i]);
                            
                            if(wordExists == 0){ // If the token does not exist in the list, then add it
                                addNode(cursor, string[i-1]);
                                cont = 1;
                            }
                            if(wordExists == 0 && delimExists == 0){
                                cursor = cursor -> nextNode;
                                cursor -> nextNode = malloc(sizeof(strNode));
                                if(cursor -> nextNode == NULL)
                                    goto Error;
                                addNode(cursor, string[i]);
                                cont = 1;
                            }
                            else if(wordExists == 1 && delimExists ==0){
                                addNode(cursor, string[i]);
                                cont = 1;
                            }
                            
                            ++i; // increment token counter
                            j = 0; // Reset character counter
                        }
                    }
                }
            }
        }while(status > 0);

        // Series of conditional statements to tie-off the end of the linked list
        if(cursor == NULL && strlen(string[i]) > 1){
            string[i][j] = '\0';
            head -> token = (char*)malloc((strlen(&string[i][j])) * sizeof(char));
            if(head -> token == NULL)
                goto Error;
            head -> nextNode = NULL;
            head -> prevNode = NULL;
            head -> freq = 1;
            strcpy(head -> token, string[i]);
        }
        else if(cursor != NULL && newToken == 1){
            string[i][j] = '\0'; // Ends the string with the null terminator
            wordExists = searchNodes(head, string[i]); // Checks to see if the token already exists
            newToken = 0; // Set new token back to false
            
            if(wordExists == 0){ // If the token does not exist in the list, then add it
                addNode(cursor, string[i]);
                cont = 1;
            }
            else if(wordExists == 1){
                cursor -> nextNode = NULL;
            }
        }
        else if(cursor == NULL){
            head = NULL;
            fprintf(stderr, "Error: Cannot build codebook because given file is empty!\n");
            goto DONE;
        }
        else if(cursor -> nextNode -> token == NULL)
            cursor -> nextNode = NULL;
        else if(cursor -> nextNode -> token != NULL)
            cursor -> nextNode -> nextNode = NULL;
        else
            cursor -> nextNode = NULL;
        
    }
    else if(rd == -1){
        fprintf(stderr, "--Error: File could not be opened!--\n"
                "File: %s\n"
                "Line: %d\n", __FILE__, __LINE__);
        return NULL;
    }
    
    goto DONE;
    
Error:
    fatalErrorHuffman = 1;
    close(rd);
    fprintf(stderr, "Error: Malloc() failed\n"
            "File: %s\n"
            "Line: %d\n", __FILE__, __LINE__);
    return NULL;
DONE:
    close(rd);
    return head;
}

void addNode(strNode *cursor, char *string){
    cursor -> nextNode -> token = (char*)malloc((strlen(string)) * sizeof(char));
    if(cursor -> nextNode -> token == NULL)
        goto Error;
    
    strcpy(cursor -> nextNode -> token, string);
    cursor -> nextNode -> nextNode = NULL;
    cursor -> nextNode -> prevNode = cursor;
    cursor -> nextNode -> freq = 1;
    
    goto DONE;
    
Error:
    fatalErrorHuffman = 1;
    fprintf(stderr, "Error: Malloc() failed\n"
            "File: %s\n"
            "Line: %d\n", __FILE__, __LINE__);
DONE: ;
}

int searchNodes(strNode *head, char *string){
    strNode *cursor = head; // Set cursor to the head of the linked list
    _Bool found = 0;

    if(cursor -> token != NULL){ // If the head has a token
        if(strcmp(cursor -> token, string) == 0){
            found = 1;
            cursor -> freq = (cursor -> freq) + 1;
            return found;
        }
        
        while(cursor -> nextNode -> token != NULL){ // Run if there are more nodes in the linked list
            cursor = cursor -> nextNode; // Traverse list to the next node
            if(strcmp(cursor -> token, string) == 0){
                found = 1;
                cursor -> freq = (cursor -> freq) + 1;
                return found;
            }
        }
    }
    
    return found;
}

// For Debugging
void printList(strNode *head){
    strNode *cursor = head; // Set cursor to the head of the linked list
    
    if(cursor -> token != NULL){ // If the head has a token
        printf("Token: %s\n", cursor -> token);
        printf("Frequency: %d\n\n", cursor -> freq);
        while(cursor -> nextNode != NULL){ // Run if there are more nodes in the linked list
            cursor = cursor -> nextNode; // Traverse list to the next node
            printf("Token: %s\n", cursor -> token);
            printf("Frequency: %d\n\n", cursor -> freq);
        }
    }
}

void freeList(strNode *head){
    strNode *cursor = head; // Set cursor to the head
    strNode *delete = malloc(sizeof(strNode)); // Used as a placeholder to free nodes in the linked list
    
    if(delete == NULL) // If malloc() failed, then throw an Error
        goto Error;
    
    if(cursor != NULL){ // If the token at the head of the list is not NULL, then free the list
        while(cursor -> nextNode != NULL){ // Traverse forward through the list until the end is reached
            cursor = cursor -> nextNode;
        }
        while(cursor != NULL){ // Once the last node is found, then traverse the list backwards and free each node
            delete = cursor; // Set delete to the cursor
            cursor = cursor -> prevNode; // Traverse the cursor backwards
            if(delete != NULL)
                free(delete); // Free delete (frees the node that delete points to)
        }
    }
    
    goto DONE; // FreeList() successfully completed, so go to main()
    
Error:
    fatalErrorHuffman = 1;
    fprintf(stderr, "Error: Malloc() failed\n"
            "File: %s\n"
            "Line: %d\n", __FILE__, __LINE__);
DONE: ;
}

MinHeap* buildHeap(strNode *head){
    strNode *cursor = head;
    MinHeap *heap = initializeHeap(5000);
    
    if(head == NULL)
        return NULL;
    
    if(cursor -> token != NULL){ // If the head has a token
        insert(heap, initializeMinNode(cursor -> freq, cursor -> token));
        
        while(cursor -> nextNode != NULL){ // Run if there are more nodes in the linked list
            cursor = cursor -> nextNode; // Traverse list to the next node
            insert(heap, initializeMinNode(cursor -> freq, cursor -> token));
        }
    }
    return heap;
}

_Bool outputCodebook(HuffList *codebook){
    int wd = open("./HuffmanCodebook.txt", O_CREAT | O_WRONLY, S_IRWXU);
    char *strBuffer = NULL;
    int stringSize = 0;
    char *codeBuffer = NULL; // To be used to get the ASCII bytestring from the codebook
    int codeSize = 0; // Will hold the length of the ASCII bytestring
    
    if(wd != -1){
        printf("--File Opened: Creating HuffmanCodebook.txt ...\n");
        if (codebook == NULL)
            return 1;
        
        int i = 0;
        while (i < codebook->size)
        {
            //   printf("%s : %s\n", codebook->array[i]->string, codebook->array[i]->code);
            strBuffer = (char*)realloc(strBuffer, strlen(codebook->array[i]->string) * sizeof(char));
            if(strBuffer == NULL)
                goto Error;
            strcpy(strBuffer,codebook->array[i]->string);
            stringSize = (int)strlen(strBuffer);
            
            codeBuffer = (char*)realloc(codeBuffer, strlen(codebook->array[i]->code) * sizeof(char));
            if(codeBuffer == NULL)
                goto Error;
            strcpy(codeBuffer,codebook->array[i]->code);
            codeSize = (int)strlen(codeBuffer);
            
            write(wd, codeBuffer, codeSize);
            write(wd, "\t", 1);
            write(wd, strBuffer, stringSize);
            write(wd, "\n", 1);
            
            i += 1;
        }
        printf("--DONE: Created HuffmanCodebook.txt\n");
    }
    else if(wd == -1){
        fprintf(stderr, "--Error: File could not be opened!--\n"
                "File: %s\n"
                "Line: %d\n", __FILE__, __LINE__);
        return 1;
    }
    
    goto DONE;
    
Error:
    printf("Error: Dynamic allocation of memory failed!\n");
DONE:
    close(wd);
    return 0;
}

MinHeap *initializeHeap(unsigned capacity)
{
    if (capacity <= 0)
    {
        fprintf(stderr, "Error: min-heap capacity must be a non-zero positive number.\n");
        return NULL;
    }
    
    MinHeap *temporary = malloc(sizeof(MinHeap));
    if (temporary == NULL)
    {
        fprintf(stderr, "Error: malloc failed to allocate enough memory for heap.\n");
        return NULL;
    }
    
    temporary->capacity = capacity;
    temporary->size = 0;
    temporary->array = malloc(sizeof(MinNode) * capacity);
    if (temporary->array == NULL)
    {
        fprintf(stderr, "Error: malloc failed to allocate enough memory for heap.\n");
        return NULL;
    }
    
    return temporary;
}

MinNode *initializeMinNode(int frequency, char *string)
{
    if (frequency <= 0)
    {
        fprintf(stderr, "Error: MinNode frequency must be a non-zero positive number.\n");
        return NULL;
    }
    
    MinNode *temporary = malloc(sizeof(MinNode));
    if (temporary == NULL)
    {
        fprintf(stderr, "Error: malloc failed to allocate enough memory for node.\n");
        return NULL;
    }
    
    temporary->frequency = frequency;
    temporary->string = string;
    temporary->left = NULL;
    temporary->right = NULL;
    
    return temporary;
}

void insert(MinHeap *heap, MinNode *node)
{
    if (heap == NULL)
    {
        fprintf(stderr, "Error: input MinHeap is NULL.\n");
        return;
    }
    
    if (node == NULL)
    {
        fprintf(stderr, "Error: input MinNode is NULL.\n");
        return;
    }
    
    if (heap->size == heap->capacity) // If heap is currently full.
    {
        heap->array = realloc(heap->array, sizeof(MinNode) * (heap->capacity * 2)); // Realloc twice size of current.
        heap->capacity *= 2;
    }
    
    heap->size += 1;                    // Increment number of nodes in heap
    heap->array[heap->size - 1] = node; // Quantity - 1, will never be 0.
    percolateUp(heap);                  // Retain heap property.
    
    return;
}

void percolateUp(MinHeap *heap)
{
    if (heap == NULL)
    {
        fprintf(stderr, "Error: input MinHeap is NULL.\n");
        return;
    }
    
    if (heap->size == 1)
    {
        return; // Only root node is in heap.
    }
    
    int index = heap->size - 1;
    while (heap->array[index]->frequency < heap->array[(index - 1) / 2]->frequency) // While percolated node is less than it's parent.
    {
        if (index == 0)
        {
            break; // If percolated node is now root node.
        }
        
        swap(&heap->array[index], &heap->array[(index - 1) / 2]);
        index = (index - 1) / 2; // Percolated node is now parent.
    }
}

void swap(MinNode **first, MinNode **second)
{
    MinNode *temporary = malloc(sizeof(MinNode)); // You must malloc here to avoid SegFault.
    if (temporary == NULL)
    {
        fprintf(stderr, "Error: malloc failed to allocate enough memory for node.\n");
        return;
    }
    
    *temporary = **first;
    **first = **second;
    **second = *temporary;
    
    free(temporary);
    return;
}

MinNode *pop(MinHeap *heap)
{
    if (heap == NULL)
    {
        fprintf(stderr, "Error: input MinHeap is NULL.\n");
        return NULL;
    }
    
    if (heap->size == 0)
    {
        fprintf(stderr, "Error: MinHeap is empty.\n\n");
        return NULL;
    }
    
    MinNode *temporary = malloc(sizeof(MinNode)); // Create temp node.
    if (temporary == NULL)
    {
        fprintf(stderr, "Error: malloc failed to allocate memory for a node.\n");
        return NULL;
    }
    
    *temporary = *heap->array[0];
    swap(&heap->array[0], &heap->array[heap->size - 1]);
    free(heap->array[heap->size - 1]);
    heap->size -= 1;
    percolateDown(heap, 0);
    
    return temporary;
}

void percolateDown(MinHeap *heap, int currentSmallest)
{
    if (heap == NULL)
    {
        fprintf(stderr, "Error: input MinHeap is NULL.\n");
        return;
    }
    
    if (heap->size <= 1)
    {
        return; // Heap is empty, or only has a root.
    }
    
    int parent = currentSmallest;
    int leftChild = 2 * parent + 1;
    int rightChild = 2 * parent + 2;
    
    // If leftChild exists within bounds, and it is larger than original set flag.
    if (leftChild < heap->size && heap->array[leftChild]->frequency < heap->array[parent]->frequency)
    {
        parent = leftChild;
    }
    
    // If rightChild exists within bounds, and it is larger than original set flag.
    if (rightChild < heap->size && heap->array[rightChild]->frequency < heap->array[parent]->frequency)
    {
        parent = rightChild;
    }
    
    // If currentSmallest doesn't equal original, recursively call itself.
    if (parent != currentSmallest)
    {
        swap(&heap->array[parent], &heap->array[currentSmallest]);
        percolateDown(heap, parent);
    }
}

MinNode *buildCodebook(MinHeap *heap)
{
    if (heap == NULL)
    {
        fprintf(stderr, "Error: input MinHeap is NULL.\n");
        return NULL;
    }
    
    if (heap->size == 0)
    {
        fprintf(stderr, "Error: heap is empty.\n");
        return NULL;
    }

    while (heap->size > 1)
    {
        MinNode *first = malloc(sizeof(MinNode));
        MinNode *second = malloc(sizeof(MinNode));
        MinNode *temporary = malloc(sizeof(MinNode));
        if (first == NULL || second == NULL || temporary == NULL)
        {
            fprintf(stderr, "Error: malloc failed to allocate enough memory for node.\n");
            return NULL;
        }
    
        first = pop(heap);
        second = pop(heap);
        temporary = initializeMinNode(first->frequency + second->frequency, NULL);
        temporary->left = first;
        temporary->right = second;
        insert(heap, temporary);
    }

    return heap->array[0];
}

HuffNode *initializeHuffNode(char *code, char *string)
{
    if (code == NULL)
    {
        fprintf(stderr, "Error: input code is NULL.\n");
        return NULL;
    }
    
    if (string == NULL)
    {
        fprintf(stderr, "Error: input string is NULL.\n");
        return NULL;
    }
    
    HuffNode *temporary = malloc(sizeof(HuffNode));
    if (temporary == NULL)
    {
        fprintf(stderr, "Error: malloc failed to allocate enough memory for node.\n");
        return NULL;
    }
    
    temporary->string = string;
    temporary->code = code;
    
    return temporary;
}

HuffList *initializeHuffList(int capacity)
{
    if (capacity < 0)
    {
        fprintf(stderr, "Error: length must be a non-zero positive number.\n");
        return NULL;
    }
    
    HuffList *temporary = malloc(sizeof(HuffList));
    if (temporary == NULL)
    {
        fprintf(stderr, "Error: malloc failed to allocate.\n");
        return NULL;
    }
    
    temporary->capacity = capacity;
    temporary->size = 0;
    temporary->array = malloc(sizeof(HuffList) * capacity);
    if (temporary->array == NULL)
    {
        fprintf(stderr, "Error: malloc failed to allocate.\n");
        return NULL;
    }
    return temporary;
}

void insertHuffNode(char *string, char *path, HuffList *list)
{
    if (string == NULL || path == NULL)
    {
        fprintf(stderr, "Error: input is invalid.\n");
        return;
    }
    
    if (list->size == list->capacity)
    {
        list->array = realloc(list->array, sizeof(HuffNode) * (list->capacity * 2));
        list->capacity *= 2;
    }
    
    if (list->size < 1)
    {
        list->array[0] = initializeHuffNode(path, string);
        // printf("TEST:%s %s\n", list->array[0]->string, list->array[0]->code);
    }
    else
    {
        list->array[list->size] = initializeHuffNode(path, string);
        // printf("TEST:%s %s\n", list->array[list->size]->string, list->array[list->size]->code);
    }
    
    list->size += 1;
    
    return;
}

void traverse(MinNode *branch, char *path, HuffList *list)
{
    if (branch == NULL)
    {
        return;
    }
    if (branch->left == NULL && branch->right == NULL) // Leaf Node
    {
        char *code = malloc(sizeof(char) * strlen(path + 1));
        if (code == NULL)
        {
            fprintf(stderr, "Error: malloc failed to allocate.\n");
            return;
        }
        
        strcpy(code, path);
        insertHuffNode(branch->string, code, list);
        path[strlen(path) - 1] = '\0';
    }
    else // Interal Node
    {
        traverse(branch->left, strcat(path, "0"), list);
        traverse(branch->right, strcat(path, "1"), list);
        path[strlen(path) - 1] = '\0';
    }
    return;
}

void printCodes(HuffList *list)
{
    int i = 0;
    while (i < list->size)
    {
        printf("%s : %s\n", list->array[i]->string, list->array[i]->code);
        i += 1;
    }
    return;
}

HuffList *generateCodes(MinNode *root, int capacity)
{
    if(root == NULL)
        return NULL;
    HuffList *codes = malloc(sizeof(HuffList));
    codes = initializeHuffList(capacity);
    if (root->left == NULL && root->right == NULL)
    {
        printf("Warning: only one token is present.\n");
        insertHuffNode(root->string, "0", codes);
        printCodes(codes);
        return codes;
    }
    char *original = malloc(50);
    original[0] = '\0';
    traverse(root, original, codes);
    return codes;
}

BookTokens* tokenBook(char* path){
    int rd = open(path, O_RDONLY);
    int status = 0;
    char buffer;
    BookTokens *head = NULL;
    BookTokens *cursor = NULL;
    char string[2000][2000];
    int i = 0;
    int j = 0;
    int cont = 1;
    
    if(rd != -1){
        
        do{
            status = (int)read(rd, &buffer, 1); // Get character
            if(status > 0){
                // IF HEAD DOES NOT EXIST YET
                if(head == NULL){
                    while(buffer != '\n' && status > 0){
                        if(isdigit(buffer)){
                            string[i][j] = buffer;
                            ++j;
                        }
                        else if(buffer == '\t'){
                            string[i][j] = '\0';
                            head = malloc(sizeof(BookTokens));
                            head -> code = (char*)malloc(strlen(string[i]) * sizeof(char));
                            strcpy(head -> code, string[i]);
                            ++i;
                            j = 0;
                        }
                        else if(isalpha(buffer) || buffer == '|' || buffer == '~' || buffer == '`'){
                            string[i][j] = buffer;
                            ++j;
                        }
                        status = (int)read(rd, &buffer, 1); // Get Character
                    }
                    if(buffer == '\n'){
                        string[i][j] = '\0';
                        head -> token = (char*)malloc(strlen(string[i]) * sizeof(char));
                        strcpy(head -> token, string[i]);
                        ++i;
                        j = 0;
                    }
                    head -> nextNode = NULL;
                    head -> prevNode = NULL;
                }
                // IF HEAD EXISTS
                else if(head != NULL){
                    if(cont == 1){ // Only loop once new token(s) have been added to the linked list
                        cursor = head;
                        while(cursor -> nextNode != NULL) // Loop until at the end of the list
                            cursor = cursor -> nextNode;
                        
                        cursor -> nextNode = malloc(sizeof(strNode));
                        cont = 0;
                    }
                    while(buffer != '\n' && status > 0){
                        if(isdigit(buffer)){
                            string[i][j] = buffer;
                            ++j;
                        }
                        else if(buffer == '\t'){
                            string[i][j] = '\0';
                            cursor -> nextNode -> code = (char*)malloc(strlen(string[i]) * sizeof(char));
                            if(cursor -> nextNode -> code == NULL)
                                goto Error;
                            strcpy(cursor -> nextNode -> code, string[i]);
                            ++i;
                            j = 0;
                        }
                        else if(isalpha(buffer) || buffer == '|' || buffer == '~' || buffer == '`'){
                            string[i][j] = buffer;
                            ++j;
                        }
                        status = (int)read(rd, &buffer, 1); // Get Character
                    }
                    if(buffer == '\n'){
                        string[i][j] = '\0';
                        cursor -> nextNode -> token = (char*)malloc(strlen(string[i]) * sizeof(char));
                        if(cursor -> nextNode -> token == NULL)
                            goto Error;
                        strcpy(cursor -> nextNode -> token, string[i]);
                        ++i;
                        j = 0;
                    }
                    cursor -> nextNode -> nextNode = NULL;
                    cursor -> nextNode -> prevNode = cursor;
                    cont = 1;
                }
            }
        }while(status > 0);
    }
    
    goto DONE;
    
Error:
    fatalErrorHuffman = 1;
    close(rd);
    fprintf(stderr, "Error: Malloc() failed\n"
            "File: %s\n"
            "Line: %d\n", __FILE__, __LINE__);
    return NULL;
DONE:
    close(rd);
    return head;
}

// FOR DEBUGGING
void printBookTokens(BookTokens *head){
    BookTokens *cursor = head; // Set cursor to the head of the linked list
    
    if(cursor -> code != NULL && cursor -> token != NULL){ // If the head has a token
        printf("Token: %s\n", cursor -> token);
        printf("Code: %s\n\n", cursor -> code);
        while(cursor -> nextNode != NULL){ // Run if there are more nodes in the linked list
            cursor = cursor -> nextNode; // Traverse list to the next node
            printf("Token: %s\n", cursor -> token);
            printf("Code: %s\n\n", cursor -> code);
        }
    }
}

// Free the tokenized linked list from the codebook
void freeBook(BookTokens *head){
    BookTokens *cursor = head; // Set cursor to the head
    BookTokens *delete = malloc(sizeof(strNode)); // Used as a placeholder to free nodes in the linked list
    
    if(delete == NULL) // If malloc() failed, then throw an Error
        goto Error;
    
    if(cursor != NULL){ // If the token at the head of the list is not NULL, then free the list
        while(cursor -> nextNode != NULL){ // Traverse forward through the list until the end is reached
            cursor = cursor -> nextNode;
        }
        while(cursor != NULL){ // Once the last node is found, then traverse the list backwards and free each node
            delete = cursor; // Set delete to the cursor
            cursor = cursor -> prevNode; // Traverse the cursor backwards
            if(delete != NULL)
                free(delete); // Free delete (frees the node that delete points to)
        }
    }
    
    goto DONE; // FreeList() successfully completed, so go to main()
    
Error:
    fatalErrorHuffman = 1;
    fprintf(stderr, "Error: Malloc() failed\n"
            "File: %s\n"
            "Line: %d\n", __FILE__, __LINE__);
DONE: ;
}

_Bool compress(BookTokens *codebook, const char *file){
    int rd = 0; // Initialize the read descriptor
    int wd = 0; // Initialize the write descriptor
    int fileLength = (int)strlen(file);
    const char *last_four = &file[fileLength-4]; // Pointer to the file extension
    
    if(fileLength < 5)
        goto COMPERR;
    else if (strcmp(last_four, ".txt") != 0)
        goto COMPERR;
    
    char *comFile = (char*)malloc(strlen(file) * sizeof(char)); // Compressed file declaration
    if(comFile == NULL){ // Check to see if malloc() worked
        goto MEMERROR; // Throw Error if malloc() failed
    }
    strcpy(comFile, file);
    comFile = (char*)realloc(comFile, (strlen(file) + 4) * sizeof(char));
    if(comFile == NULL){ // Check to see if realloc() worked
        goto MEMERROR; // Throw Error if realloc() failed
    }
    strcat(comFile, ".hcz");
    
    char string[2000][2000]; // Holds strings found in the file
    int i = 0; // Token Counter
    int j = 0; // Character Counter
    char* code = NULL;
    _Bool newToken = 0;
    rd = open(file, O_RDONLY);
    wd = open(comFile, O_CREAT | O_WRONLY, S_IRWXU);
    
    if(rd != -1 && wd != -1){
        printf("--File Opened: Compressing File...\n");
        int status = 0;
        char buffer;
        
        do{
            status = (int)read(rd, &buffer, 1);
            if(status > 0){
                if(buffer != ' ' && buffer != '\n' && buffer != '\t'){
                    string[i][j] = buffer;
                    ++j;
                    newToken = 1;
                }
                else if (buffer == ' ' || buffer == '\n' || buffer == '\t'){
                    if(newToken == 1){
                        string[i][j] = '\0';
                        code = getCodes(codebook, string[i]);
                
                        if(code == NULL){
                            goto SYMERROR;
                        }
                        
                        write(wd, code, strlen(code));
                        
                        ++i; // increment token counter
                        j = 0; // Reset character counter
                        newToken = 0;
                    }
                    
                    if(buffer == ' '){
                        string[i][j] = '|';
                        ++j;
                        string[i][j] = '\0';
                        
                        code = getCodes(codebook, string[i]);
                        
                        if(code == NULL){
                            goto SYMERROR;
                        }
                        
                        write(wd, code, strlen(code));
                        
                        ++i; // increment token counter
                        j = 0; // Reset character counter
                    }
                    else if(buffer == '\n'){
                        string[i][j] = '~';
                        ++j;
                        string[i][j] = '\0';
                        
                        code = getCodes(codebook, string[i]);
                        
                        if(code == NULL){
                            goto SYMERROR;
                        }
                        
                        write(wd, code, strlen(code));
                        
                        ++i; // increment token counter
                        j = 0; // Reset character counter
                    }
                    else if(buffer == '\t'){
                        string[i][j] = '`';
                        ++j;
                        string[i][j] = '\0';
                        
                        code = getCodes(codebook, string[i]);
                        
                        if(code == NULL){
                            goto SYMERROR;
                        }
                        
                        write(wd, code, strlen(code));
                        
                        ++i; // increment token counter
                        j = 0; // Reset character counter
                    }
                }
            }
        }while(status > 0);
        
        if(newToken == 1){ // If end was reached without finding delimiter, then makse sure the last token is added
            
            string[i][j] = '\0';
            code = getCodes(codebook, string[i]);
                
            if(code == NULL){
                goto SYMERROR;
            }
            write(wd, code, strlen(code));
        }
    }
    else if(rd == -1 || wd == -1){
        fprintf(stderr, "--Error: File could not be opened!--\n"
                "File: %s\n"
                "Line: %d\n", __FILE__, __LINE__);
        return 1;
    }
    
    goto DONE;
COMPERR:
    printf("Error: This file is not able to be compressed! Please compress .txt files!\n");
    fatalErrorHuffman = 1;
    close(rd);
    close(wd);
    printf("--DONE: File Closed\n");
    return 1;
SYMERROR:
    printf("Error: Unexpected symbol found during compression! Aborting compression...\n");
    fatalErrorHuffman = 1;
    close(rd);
    close(wd);
    printf("--DONE: File Closed\n");
    return 1;
MEMERROR:
    printf("Error: Dynamic memory allocation failed! Aborting compression...\n");
    fatalErrorHuffman = 1;
    close(rd);
    close(wd);
    printf("--DONE: File Closed\n");
    return 1;
DONE:
    close(rd);
    close(wd);
    printf("--DONE: File Closed\n");
    return 0;
}

char* getCodes(BookTokens *head, char *token){
    char *code = NULL;
    BookTokens *cursor = head; // Set cursor to the head of the linked list
    
    if(cursor -> code != NULL && cursor -> token != NULL){ // If the head has a token
        if(strcmp(token, cursor -> token) == 0){
            code = (char*)malloc(strlen(cursor -> code) * sizeof(char));
            strcpy(code, cursor -> code);
            return code;
        }
        while(cursor -> nextNode != NULL){ // Run if there are more nodes in the linked list
            cursor = cursor -> nextNode; // Traverse list to the next node
            if(strcmp(token, cursor -> token) == 0){
                code = (char*)malloc(strlen(cursor -> code) * sizeof(char));
                strcpy(code, cursor -> code);
                return code;
            }
        }
    }
   
    return NULL;
}

char *findString(BookTokens *head, char *code) {
    char *string = NULL;
    BookTokens *cursor = head; // Set cursor to the head of the linked list
    
    if(cursor -> code != NULL && cursor -> token != NULL){ // If the head has a token
        if(strcmp(code, cursor -> code) == 0){
            string = (char*)malloc(strlen(cursor -> token) * sizeof(char));
            strcpy(string, cursor -> token);
            return string;
        }
        while(cursor -> nextNode != NULL){ // Run if there are more nodes in the linked list
            cursor = cursor -> nextNode; // Traverse list to the next node
            if(strcmp(code, cursor -> code) == 0){
                string = (char*)malloc(strlen(cursor -> code) * sizeof(char));
                strcpy(string, cursor -> token);
                return string;
            }
        }
    }
    
    return NULL;
}

_Bool decompress(BookTokens *codebook, const char *file) {
    int wd = 0; // Initialize writing file descriptor
    int rd = 0; // Initialize reading file descriptor
    int fileLength = (int)strlen(file);
    const char *last_four = &file[fileLength-4]; // Pointer to the file extension
    
    if(fileLength < 5)
        goto COMPERR;
    else if (strcmp(last_four, ".hcz") != 0)
        goto COMPERR;
    
    // Create name of the decompressed file
    int baseFileLength = (int)strlen(file) - 4;
    char* baseFile = (char*)malloc((strlen(file) - 3) * sizeof(char));
    if(baseFile == NULL)
        goto MEMERROR;
    memcpy(baseFile, file, baseFileLength);
    strcat(baseFile, "\0");
    
    char string[5000]; // String to hold characters from the compressed file
    int i = 0;
    rd = open(file, O_RDONLY); // Open compressed file
    
    if(rd != -1){
        printf("--File Opened: Decompressing File...\n");
        int status = 0;
        char buffer;
        
        do{ // Copy the compressed file into the character array
            status = (int)read(rd, &buffer, 1);
            if(status > 0){
                string[i] = buffer;
                ++i;
            }
        }while(status > 0);
        string[i] = '\0';
    }else
        printf("Error: File could not be opened!\n");
    
    int c = 0;
    char *accumulator = malloc(200);
    if(accumulator == NULL)
        goto MEMERROR;
    char *temp = malloc(200);
    if(temp == NULL)
        goto MEMERROR;
    char *decoded = malloc(5000);
    if(decoded == NULL)
        goto MEMERROR;
    accumulator[0] = '\0';
    
    while(string[c] != '\0') {
        temp = findString(codebook, accumulator);
        if (temp == NULL) {
            accumulator[strlen(accumulator)] = string[c];
            accumulator[strlen(accumulator) + 1] = '\0';
            c += 1;
        }
        else {
            if (strcmp(temp, "`") == 0) {
                char *new = malloc(strlen(decoded) + 2);
                strcpy(new, decoded);
                strcat(decoded, "\t");
                free(new);
            }
            else if (strcmp(temp, "~") == 0) {
                char *new = malloc(strlen(decoded) + 2);
                strcpy(new, decoded);
                strcat(decoded, "\n");
                free(new);
            }
            else if (strcmp(temp, "|") == 0) {
                char *new = malloc(strlen(decoded) + 2);
                strcpy(new, decoded);
                strcat(decoded, " ");
                free(new);
            }
            else {
                strcpy(decoded+strlen(decoded), temp);
            }
            memset(accumulator, '\0', sizeof(char)*strlen(accumulator));
        }
    }
    
    // Leftover string.
    temp = findString(codebook, accumulator);
    
    if (strcmp(temp, "~") == 0) {
        char *new = malloc(strlen(decoded) + 2);
        strcpy(new, decoded);
        strcat(decoded, "\n");
        free(new);
    }
    else if (strcmp(temp, "|") == 0) {
        char *new = malloc(strlen(decoded) + 2);
        strcpy(new, decoded);
        strcat(decoded, " ");
        free(new);
    } else if (strcmp(temp, "`") == 0) {
        char *new = malloc(strlen(decoded) + 2);
        strcpy(new, decoded);
        strcat(decoded, "\t");
        free(new);
    }
    else
        strcpy(decoded+strlen(decoded), temp);
    
    wd = open(baseFile, O_CREAT | O_WRONLY, S_IRWXU); // Open/create file to decompress to
    if(wd != -1){
        write(wd, decoded, strlen(decoded)); // Write decompressed contents ot file
    }
    else if(wd == -1){
        fprintf(stderr, "--Error: File could not be opened!--\n"
                "File: %s\n"
                "Line: %d\n", __FILE__, __LINE__);
        return 1; // Return with error
    }
    
    goto DONE;
COMPERR:
    printf("Error: This file is not able to be compressed! Please decompress .hcz files!\n");
    fatalErrorHuffman = 1;
    close(rd);
    close(wd);
    printf("--DONE: File Closed\n");
    return 1;
MEMERROR:
    printf("Error: Dynamic memory allocation failed! Aborting compression...\n");
    fatalErrorHuffman = 1;
    close(rd); // Close the compressed file
    close(wd); // Close file
    return 1; // Return with error
DONE:
    close(rd); // Close the compressed file
    close(wd); // Close file
    printf("--DONE: File Decompressed!\n");
    return 0;
}
