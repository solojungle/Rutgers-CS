//
//  main.c
//  fileCompressor
//
//  Created by Dennis Kager on 3/12/19.
//  Copyright © 2019 Dennis Kager and Ali Awari. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>
#include "HuffmanCodebook.h"
#include <fcntl.h> // For open() and write()
#include <unistd.h> // For read()

// Identification Functions
_Bool isFlag(const char*);
_Bool isPath(const char*);
_Bool isCodebook(const char*);

// Functions for reference
void recursiveFunctions(char*, unsigned int);

_Bool fatalErrorMain = 0; // Used for terminating program in the event of a fatal Error

int main(int argc, const char *argv[]) {
    strNode *list = NULL; // Linked list that holds tokens of the file
    MinHeap *heap = NULL; // Heap that is built off of the tokens in the linked list, known as, *list
    MinNode *bookTokens = NULL; // Holds the codebook
    HuffList *bookCodes = NULL;
    BookTokens *tokenizedBook = NULL;
    
    if(fatalErrorMain != 1){
        // NOTE: argv[0] counts as one (1) in argc. Argv[0] holds the name of the executing file
        if(argc == 3){ // For two user-input arguments
            if(isFlag(argv[1]) == 1 && isPath(argv[2]) == 1){
                if(strcmp(argv[1], "-b") == 0){
                    int rd = open("./HuffmanCodebook.txt", O_RDONLY);
                    if(rd != -1){
                        close(rd);
                        printf("Error: Codebook Already Exists!\n");
                        goto DONE;
                    }
                    list = tokenize(argv[2], list); // Get linked list of tokens and frequencies
                    if(list == NULL || fatalErrorMain == 1) // Checks to see if a null linked list is due to an Error
                        goto DONE;
                    heap = buildHeap(list); // Build heap
                    if(heap == NULL)
                        goto DONE;
                    bookTokens = buildCodebook(heap); // Build codebook
                    if(bookTokens == NULL)
                        goto DONE;
                    bookCodes = generateCodes(bookTokens, 5000);
                    if(bookCodes == NULL)
                        goto DONE;
                    fatalErrorMain = outputCodebook(bookCodes); // Output codebook file
                    if(fatalErrorMain == 1)
                        goto DONE;
                }
                else
                    printf("Error: Invalid flag!\n");
            }
            else{
                printf("Error: Invalid arguments!\n");
            }
        }
        else if(argc == 4){ // For three user-input arguments
            if(isFlag(argv[1]) == 1 && isPath(argv[2]) == 1 && isCodebook(argv[3]) == 1){
                if(strcmp(argv[1], "-c") == 0){
                    int fd = open(argv[3], O_RDONLY); // Open codebook
                    
                    if(fd != -1){ // If the codebook exists
                        close(fd); // Close codebook
                        // COMPRESS GIVEN FILE
                        tokenizedBook = tokenBook("./HuffmanCodebook.txt");
                        if(tokenizedBook == NULL)
                            goto DONE;
                        fatalErrorMain = compress(tokenizedBook, argv[2]);
                        if(fatalErrorMain == 1)
                            goto DONE;
                    }
                    else
                        printf("Error: Codebook does not exist!\n");
                }
                else if(strcmp(argv[1], "-d") == 0){
                    int fd = open(argv[3], O_RDONLY); // Open codebook
                    
                    if(fd != -1){ // If the codebook exists
                        close(fd); // Close codebook
                        // DECOMPRESS GIVEN FILE
                        tokenizedBook = tokenBook("./HuffmanCodebook.txt");
                        if(tokenizedBook == NULL)
                            goto DONE;
                        decompress(tokenizedBook, argv[2]);
                    }
                    else
                        printf("Error: Codebook does not exist!\n");
                }
                else
                    printf("Error: Invalid flags!\n");
            }
            else if(isFlag(argv[1]) == 1 && isFlag(argv[2]) == 1 && isPath(argv[3]) == 1){
                // Build codebook then compress the given file
                if((strcmp(argv[1], "-b") == 0 && strcmp(argv[2], "-c") == 0) || (strcmp(argv[1], "-c") == 0 && strcmp(argv[2], "-b") == 0)){
                    int rd = open("./HuffmanCodebook.txt", O_RDONLY);
                    if(rd != -1){ // If the codebook already exists, then just compress it
                        close(rd);
                        printf("--Message: Codebook Already Exists!\n");
                        tokenizedBook = tokenBook("./HuffmanCodebook.txt");
                        if(tokenizedBook == NULL)
                            goto DONE;
                        // COMPRESS
                        compress(tokenizedBook, argv[3]);
                        
                        goto DONE;
                    }
                    //Run code if the codebook does not yet exist
                    list = tokenize(argv[3], list); // Get linked list of tokens and frequencies
                    if(list == NULL || fatalErrorMain == 1) // Checks to see if a null linked list is due to an Error
                        goto DONE;
                    heap = buildHeap(list); // Build heap
                    if(heap == NULL)
                        goto DONE;
                    bookTokens = buildCodebook(heap); // Build codebook
                    if(bookTokens == NULL)
                        goto DONE;
                    bookCodes = generateCodes(bookTokens, 5000);
                    if(bookCodes == NULL)
                        goto DONE;
                    fatalErrorMain = outputCodebook(bookCodes); // Output codebook file
                    if(fatalErrorMain == 1)
                        goto DONE;
                    tokenizedBook = tokenBook("./HuffmanCodebook.txt");
                    if(tokenizedBook == NULL)
                        goto DONE;
                    // COMPRESS
                    compress(tokenizedBook, argv[3]);
                }
                else
                    printf("Error: Invalid flags!\n");
            }
            else{
                printf("Error: Invalid arguments!\n");
            }
        }
        else if(argc == 5){ // For four user-input arguments
            if(isFlag(argv[1]) == 1 && isFlag(argv[2]) == 1 && isPath(argv[3]) == 1 && isCodebook(argv[4]) == 1){
                if((strcmp(argv[1], "-R") == 0 && strcmp(argv[2], "-b") == 0) || (strcmp(argv[1], "-b") == 0 && strcmp(argv[2], "-R") == 0)){
                    /*// RECURSIVELY BUILD CODEBOOK
                    char *path = (char*)malloc(strlen(argv[3]) * sizeof(char));
                    strcpy(path, argv[3]);
                    recursiveFunctions(path, 1);*/
                    printf("Sorry! This part of the project is not done yet!! :(\n");
                }
                else if((strcmp(argv[1], "-R") == 0 && strcmp(argv[2], "-c") == 0) || (strcmp(argv[1], "-c") == 0 && strcmp(argv[2], "-R") == 0)){
                    /*int fd = open(argv[4], O_RDONLY); // Open codebook
                    
                    if(fd != -1){ // If the codebook exists
                        // RECURSIVLEY COMPRESS FILES
                    }
                    else
                        printf("Error: Codebook does not exist!\n");
                    
                    close(fd); // Close codebook*/
                    printf("Sorry! This part of the project is not done yet!! :(\n");
                }
                else if((strcmp(argv[1], "-R") == 0 && strcmp(argv[2], "-d") == 0) || (strcmp(argv[1], "-d") == 0 && strcmp(argv[2], "-R") == 0)){
                   /* int fd = open(argv[4], O_RDONLY); // Open codebook
                    
                    if(fd != -1){ // If the codebook exists
                        // RECURSIVLEY DECOMPRESS FILES
                    }
                    else
                        printf("Error: Codebook does not exist!\n");
                    
                    close(fd); // Close codebook */
                    printf("Sorry! This part of the project is not done yet!! :(\n");
                }
                else
                    printf("Error: Invalid flag combination!\n");
            }
        }
        else{
            if(argc < 3)
                printf("Error: Too few arguments given!\n");
            else
                printf("Error: Too many arguments given!\n");
        }
    }
    
DONE:
    freeList(list); // Free linked lists
    freeBook(tokenizedBook);
    
    return 0;
}

_Bool isFlag(const char *arg){ // Checks to see if an argument is a flag
    if(strcmp(arg, "-b") == 0)
        return 1;
    else if(strcmp(arg, "-c") == 0)
        return 1;
    else if(strcmp(arg, "-d") == 0)
        return 1;
    else if(strcmp(arg, "-R") == 0)
        return 1;
    
    return 0;
}

_Bool isPath(const char *arg){ // Checks to see if an argument is a directory
    if(strlen(arg) > 2 && isCodebook(arg) == 0)
        return 1;
    
    return 0;
}

_Bool isCodebook(const char *arg){ // Checks to see if the argument is the path to the Huffman Codebook
    if(strcmp(arg, "./HuffmanCodebook.txt") == 0)
        return 1;
    
    return 0;
}

// SUPPOSED TO HANDLE RECURSIVE CALLS -- NOT WORKING CURRENTLY
void recursiveFunctions(char* input, unsigned int mode){
    char *path = (char*)malloc(strlen(input)*sizeof(char));
    DIR *dd = opendir(input); // Opens a directory and returns a dirctory pointer
    struct dirent *status = NULL; // Status pointer of type struct dirent
    strNode *list = NULL; // Linked list that holds tokens of the file
    MinHeap *heap = NULL; // Heap that is built off of the tokens in the linked list, known as, *list
    MinNode *bookTokens = NULL; // Holds the codebook
    HuffList *bookCodes = NULL;
    
    if(dd != NULL){
        
        status = readdir(dd); // readdir() retuns pointer to next directory entry
        
        while(status != NULL){ // If directory can be accessed, then keep looping
            status = readdir(dd); // readdir() retuns pointer to next directory entry
            
            if(status == NULL) // If the direcory cannot be accessed, then exit
                break;
            
            // DO SOMETHING HERE WITH FILES FOUND
            if(status -> d_type == DT_REG && strcmp(".DS_Store", status -> d_name) != 0){
                printf("%s\n", status -> d_name);
                
                if(mode == 1){ // Recursively build
                    char *filePath = (char*)malloc(20 * sizeof(char));
                    strcpy(filePath, "./");
                    filePath = (char*)realloc(filePath, (strlen(status -> d_name) + 2) * sizeof(char));
                    strcat(filePath, status -> d_name);
                    list = tokenize(filePath, list); // Get linked list of tokens and frequencies
                    if(list == NULL || fatalErrorMain == 1) // Checks to see if a null linked list is due to an Error
                        goto DONE;
                    printList(list);
                }
                else if(mode == 2){ // Recursively compress
                    
                }
                else if(mode == 3){ // Recursively decompress
                    
                }
            }
            
            // If the file type is another directory, then output '\' at the end
            if(status -> d_type == DT_DIR)
            {
                if((strcmp(status -> d_name, ".") != 0) && (strcmp(status -> d_name, "..") != 0)){
                //    printf("%s", status -> d_name); // Prints only directories
                //    printf("/");
                    path = NULL;
                    path = realloc(path, strlen(input) + strlen(status -> d_name ) + 1);
                    strcat(path, input);
                    strcat(path, "/");
                    strcat(path, status -> d_name);
                  //  printf("\n");
                 //   printf("Directory Path: %s/\n\n", path);
                    recursiveFunctions(path, mode);
                }
            }
        }
        if(mode == 1 && list != NULL){
            heap = buildHeap(list); // Build heap
            bookTokens = buildCodebook(heap); // Build codebook
            bookCodes = generateCodes(bookTokens, 5000);
            outputCodebook(bookCodes); // Output codebook file
        }
        closedir(dd); // Close the directory
    }
    
    else
        printf("\n--Error: Directory could not be opened!--\n");
    
DONE: ;
}
