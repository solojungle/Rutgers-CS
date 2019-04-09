# Project Status
Please provide any status updates on the project down below:

Status Update - Dennis Kager - 02/22/2019 @ ~8:30PM EST
-------------------------------------------------------
As it stands, memgrind.c (the file used for testing the munctions) has a few unofficial tests which expose the current bug in the code existing in mymalloc() within mymalloc.c. It is currently being addressed. On memgrind.c and mymalloc.c, there is commented-out code at the bottom of those files. Please leave them there (I was using it as version control prior to getting a GitHub) and I will take care of them soon. Thanks

Status Update - Dennis Kager - 02/22/2019 @ 11:03PM EST
-------------------------------------------------------
* Fixed bug from before in mymalloc() 
* Got rid of extraneous code at the bottom of memgrind.c and mymalloc.c
* Added much needed comments
* Updated some of the unofficial tests to look neater

Status Update - Ali Awari - 02/23/2019 @ 1:19AM EST
-------------------------------------------------------
* Added makefile

Status Update - Dennis Kager - 02/23/2019 @ 5:58PM EST
-------------------------------------------------------
* Tweaked a typo in a test in memgrind.c
* Tweaked the initialization of the first node in mymalloc.c to maximize available memory
* Added an error response to memory saturation in mymalloc.c if a pointer is going to be returned as NULL
* Added a tester in memgrind.c which demonstrates the error message

Status Update - Ali Awari - 02/23/2019 @ 10:04PM EST
-------------------------------------------------------
* Created myfree.c
* Edited makefile to include myfree.c

Status Update - Ali Awari - 02/23/2019 @ 11:54PM EST
-------------------------------------------------------
* Added comments to myfree.c, and simplified if statements

Status Update - Ali Awari - 02/23/2019 @ 12:19AM EST
-------------------------------------------------------
* Added __LINE__, and __FILE__ to myfree.c
* Added tests to memgrind.c
* Fixed compiler warnings for type casting

Status Update - Dennis Kager - 02/25/2019 @ 7:10PM EST
-------------------------------------------------------
* Added myfree() to mymalloc.c
* Eliminated myfree.c from project
* Fixed myfree()
* Partial fix on defragment()
* Added some code at the bottom of myfree() to show the status of nodes after using defragment() 

Status Update - Ali Awari - 02/27/2019 @ 4:07AM EST
-------------------------------------------------------
* Added time to memgrind.c
* Fixed makefile

Status Update - Ali Awari - 03/5/2019 @ 4:12PM EST
-------------------------------------------------------
* Added new tests
* Fixed spelling errors
* Removed prints after malloc
* Added new error case to malloc

Status Update - Ali Awari - 03/6/2019 @ 9:35PM EST
-------------------------------------------------------
* Fixed tests
* Memgrind now runs tests 100 times, and averages the execution time
--
TODO: Need to add comments to functions
TODO: Need to ensure test cases are correct

Status Update - Ali Awari - 03/7/2019 @ 3:54PM EST
-------------------------------------------------------
* Fixed malloc bug in which there was an extra sizeof(metadata) attached to memory array e.i total capacity from 4096 to (4096 - sizeof(metadata))
* Attempted to reduce sizeof(metadata) by changing spaceUsed to a short, didn't change anything on my machine
* Added printNodes() function for debugging purposes
* Added to TestF to ensure defragmentation works correctly.
* Added empty testplan.txt
--
TODO: Need to add comments to functions
TODO: Need to ensure test cases are correct

Status Update - Dennis Kager - 03/7/2019 @ 6:40PM EST
-------------------------------------------------------
* Fixed errors in testing cases: It was just a matter of the arrays being out of sync in Test C/D and in Test D I fixed the the management of the variable remainingMemory so at the end of the test, it will have 4096 remaining
* Comments still have to be added and further testing still needs to be done, but it is a good start
* Fixed warnings for return types from functions in memgrind.c (precision loss from unsigned long to integer)

Status Update - Dennis Kager - 03/8/2019 @ 1:19PM EST
------------------------------------------------------
* Fixed the header file and function prototypes so that when an error is made, it will show the file and line number for memgrind.c
* Fixed test cases C and D so that they work as intended
* Re-wrote Test E to test for an edge case (commented in memgrind.c)
* Modified Test F, which also has edge cases being tested
* Added magic number. It is tacked onto the end of the static array definition in mymalloc.h and is defined in mymalloc.c. It essentially works by setting the first 4 bytes of the array to a number. Every time that mymalloc() is called, it takes the first 4 bytes of the array as an integer pointer and then dereferences it to compares to the magic number. If the numbers match, then the array has not been initialized yet. After initialization, the magic number will be overwritten and each consecutive call to mymalloc() will work as before
* Added much-needed comments throughout

Status Update - Ali Awari - 03/9/2019 @ 5:21PM EST
-------------------------------------------------------
* Formatting (mymalloc.c, memgrind.c, mymalloc.h)
* Filled testplan.txt
--
TODO: Remove test from makefile before submitting

Status Update - Ali Awari - 03/9/2019 @ 6:29PM EST
-------------------------------------------------------
* Fixed -C99 error message "loop initial declarations are only allowed in C99 mode"

Status Update - Dennis Kager - 03/10/2019 @ 4:35PM EST
------------------------------------------------------
* Removed test from makefile
* Removed printNodes() from the program
* Added readme.pdf
