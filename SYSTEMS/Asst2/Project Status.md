Project Status 
==============

Status Update - Dennis Kager - 3/14/19 @ 6:22PM
-----------------------------------------------
* Initial file upload
* Huffman Codebook header file and C file are there but currently do not serve a purpose
* The header file contains a struct for a tree. I am not sure if the tree is setup right or not, but its a start
* In fileCompressor.c you will find various functions that demonstrate navigating the file system. There are not too many comments in there that really explain what is going on, but I will add some later. In the functions where you see a hardcoded path, you will need to change the path to something on your computer. This is only temporary since we will be retreiving the path from the command line when the program is run. For now it just makes it easier to work with. 
* outputToFile() takes a path and will create (O_CREAT) a document called test.txt or open a pre-existing file called test.txt for writing (O_WRONLY). All files in the given directory will be opened and have their contents dumped into the test file. The location of the test.txt file can be changed to anywhere of your choosing by modifying the wd variable. One thing worth noting is that I have this function set to open test.txt in append-mode (O_APPEND) so that the file isn't overwritten with each call to add contents
* dumpFile() will dump all of the contents of the file it gets to STDOUT
* printAllDir() takes a base directory and prints all sub-directories. You can test this by creating a folder and inside having more folders nested as deep as you want
* printAllFile() finds all files in a given directory and call dumpFile() to output to STDOUT and then call outputToFile() to save the contents to test.txt
* I soon plan on changing up the program to work more closely to how it is supposed to be ran, but its a start
* fileCompressor.c can currently be run independently from HuffmanCodebook.c and HuffmanCodebook.c but you may have to comment out this line to get it to work without warnings if you plan on only using that file for now: #include "HuffmanCodebook.h"

Status Update - Ali Awari - 3/14/19 @ 7:21PM
---------------------------------------------
* Added makefile
* Changed "HuffmanCodebook.\*" to "huffmanCodebook.\*"
* Created tests dir, for relative-path testing

Status Update - Dennis Kager - 3/22/19 @ 10:54PM
-----------------------------------------------
* Added a few functions to tokenize a given file 
* Tokenizing should work for at least basic files but I am not 100% sure of the behavior on more complex files. I have not gotten that far on the testing
* Changed names back to HuffmanCodebook.h and HuffmanCodebook.c for consistency with the project outline

Status Update - Dennis Kager - 3/27/19 @ 10:35PM
------------------------------------------------
* Attempted to fix bug in the tokenizer. It works much better than it did before and should be at least 99.9% bug free. I have not yet tested it on iLab machines but it should work. It can't take huge files since the array holding the tokens is only 2,000 by 2,000. For now this should work for basic text files

Status Update - Ali Awari - 3/29/19 @ 2:49PM
--------------------------------------------
* Finished min-heap and added comments to files.

Status Update - Dennis Kager - 3/29/19 @ 3:02PM
-----------------------------------------------
* Fixed tokenizer() and made it much more robust and added error handling
* Added function to free dynamically allocated memory in the linked list

Status Update - Ali Awari - 3/29/19 @ 4:33PM
--------------------------------------------
* Fixed min-heap bug (improperly placed child/subset condition ontop of parent/superset)
    - (LEFT || RIGHT) before (LEFT && RIGHT)

Status Update - Dennis Kager - 3/29/19 @ 10:41PM
------------------------------------------------
* Added ability to tokenize multiple files and append/modify frequencies of tokens in the linked list
* Added handling for input
* Added various functions for detecting flags, paths, and the path to the HuffmanCodebook on user input
* Changed arrangement of main.c so that the original functions I wrote for handling files/directories are out of the way and can be used for reference later on
* Updated Copyright headers on files
* Edited min-heap.h so that it can detect if the header file already exists

Status Update - Ali Awari - 3/30/19 @ 8:45PM
--------------------------------------------
* Merged minheap nodes and Huffman nodes
* Improved minheap
* Changed typedef naming scheme

Status Update - Ali Awari - 3/31/19 @ 12:15AM
--------------------------------------------
* Fixed realloc bug in min-heap
* Fixed printHeap bug
* Uncommented important structs in HuffmanCodebook.h

Status Update - Ali Awari - 3/31/19 @ 9:48PM
--------------------------------------------
* Added buildCodebook()
* Added printBook() for debugging

Status Update - Dennis Kager - 3/31/19 @ 10:20PM
------------------------------------------------
* Added buildHeap() in main.c for building a minheap from a linked list of tokens
* Implemented buildCodebook() in main.c
* Fixed copyright headers in HuffmanCodebook.c and HuffmanCodebook.h
* Added #include <math.h> in HuffmanCodebook.c to get rid of warning for using pow()

Status Update - Ali Awari - 4/1/19 @ 4:50AM
--------------------------------------------
* Almost finished generating HuffmanCodes
* Small bug in traverse(), will only display last generated code, must likely pointer error

Status Update - Ali Awari - 4/1/19 @ 1:45PM
--------------------------------------------
* Generate codes but incorrectly

Status Update - Ali Awari - 4/1/19 @ 2:30PM
--------------------------------------------
* Fixed traverse(), when returning back to root node, Internal Nodes wouldn't reflect being finished by removing their path.
* Internal Nodes now reflect correct pathing when exhausted.

Status Update - Dennis Kager - 4/1/19 @ 6:42PM
-----------------------------------------------
* Fixed the HuffmanCodebook.txt output
* Added compress() and getCodes() for compressing files in HuffmanCodebook.c

Status Update - Ali Awari - 4/1/19 @ 8:04PM
--------------------------------------------
* Added decompress()

Status Update - Ali Awari - 4/1/19 @ 9:43PM
--------------------------------------------
* Added control chars to decompress()

Status Update - Dennis Kager - 4/3/19 @ 12:42PM
-----------------------------------------------
* Implemented new algorithm for tokenizing the Huffman Codebook in the event that we are told to compress or decompress a file with only being given a codebook
* Worked on decompress() to add reading and writing file descriptors
* Modified compress() and decompress() to work with my codebook-tokenizing function

Status Update - Dennis Kager - 4/3/19 @ 1:18PM
-----------------------------------------------
* Fixed a few lines in main.c that would cause program to segfault
* Fixed some input functionality in main.c

Status Update - Dennis Kager - 4/3/19 @ 9:39PM
-----------------------------------------------
* Added LOTS of error checking
* Fixed bug in tokenizing and compressing
* Added guards to prevent creating or overwriting codebook files

Status Update - Dennis Kager - 4/3/19 @ 10:13PM
-----------------------------------------------
* Added guards so that compress() will only compress .txt files
* Added guards so that decompress() will only decompress .hcz files
