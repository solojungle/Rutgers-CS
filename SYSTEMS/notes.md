# January 22, 2019

## _UNDEFINED BEHAVIOR_

Basic C overview

# January 24, 2019

Review of last class

C-convention:

```C
struct _point {
int x;
int y;
};

typedef struct _point point;

point corner = {1, 2};
```

# January 29, 2019

Fetch, Decode, Execute

- Fetch instruction
- Pull info from memory addresses
- Execute code, increment program counter

#

- Create
- Run
- Edit/Debug/Test

#

### Struct

- Structs are data structures which contain only state
- Accessed by dot-notation
- At least the sum of the size of its attributes

### Union

- At least size of largest attribute
- Definition and access is same as structs, but all members share same memory block

#

### SizeOf

### Pointers

- \* dereference
- \& address of

### Arrays

An array type describes a contiguously allocated nonempty set of objects with a particular member object type, called the element type.

### Arrow Operator (Notation)

(\*ptr1).a is the same as ptr1 -> a

# January 31, 2019

- F
  (- pipeline)
- D
- (latch) < latch speed
- E

Clock rate and latch speed are not synchronous, you can raise clock rate and slow down CPU

- Fetch: go to location in main memory dictated by the program counter and load as next instr
- Decode: inspect and prepare to be used (anything that needs to be done to make it exec-able)
- Execute: run instruction and increment program counter

### Pointers

- a type of variable that stores the memory location of another ... thing
- &: address of
- \*: dereference
- ->: (\*var0).var1 <=> var0 -> var1
- []: thing[value] <=> \*(thing+value)

#

- int array[] = {1, 2, 3, 4};
- int \*ptr = array;
- double array0[] = {5, 6, 7, 8};
- double \*ptr0 = array0;
- \*(++ptr); // Incremented by 4 bytes
- \*(++ptr0); // Incremented more than the int array (by 8 bytes)

### Malloc

- Ask operating system for memory on the heap
- Malloc is allowed to fail
- Guaranteed that amount of memory requested, it might be more.
- Must free() malloc

#

Why would Malloc fail?

- If you ask for too much memory (malloc(10 million GB))
- If malloc cannot retrieve enough data using sbrk() or mmap()
- If you asked for 0 bytes ( malloc(0) )

#

In order to ensure that you get correct amount of memory (due to machine dependency)

- char \* array = (char\*)malloc(8\*sizeof(char));
- prevents default behavior
- "I hate default behavior, the machine does what I do" - Francisco

### Free

- Dont free arrays, primative types, static types
- Only free dynamic types
- calloc must be contiguous in memory (restrictive), malloc may pull memory from anywhere but it might not be next to eachother
- free might return before it's acutally done

### Realloc

Can't make itself bigger

<!-- http://www.iso-9899.info/wiki/Why_not_realloc -->

- There is a timing issue
- You try to access a pointer that has been free'd
- You're better off doing the three steps manually
- malloc a larger dataset
- memcpy the old malloc
- free the old malloc

```C
char * newspace = (char)malloc(10*sizeof(char));
memcpy(newspace, array, 6);
free(array);
```

# February 5, 2019

- Z
- A
- z
- a

#

- Apple
- zebra

#

- cat
- bat

#

- caT
- catamaran

#

- catamaran
- cat

#

- cat
- bAt

#

If you need things allocated to 0, don't use calloc, use bzero

- you can also use memset more generally (set all memory to 'a's for example)

#

- malloc() - dynamic allocation (initialize with bzero or memset if you care)
- calloc() - dynamic allocation that is physically contiguous and initialized to 0
- realloc():
  - malloc()
  - memcpy()
  - free()
- free() - dynamic deallocation of dynamically-allocated memory

#

- char ** alltokens = (char**)malloc(sizeof(char*)*20)
- alltokens[5] = (char*)malloc(sizeof(char)*7)

#

- Fatal Error: During Runtime (Tried to malloc got a NULL)
- Error: During Compile (Out of spec, can't continue)
- Warning: Something odd

#

Print filename and line number

- \_\_FILE\_\_
- \_\_LINE\_\_
- \$FILE\_\_

#

- const to a primative will not allow you to change the value, even at the memory address.
  - you can change the value of the const with a pointer
- const on a pointer will allow you to change value
- two flavors of const for pointers
  - const pointer = &a
  - const pointer = a

#

const on inside v.s. outside

- const int \* ptr0 = &a;
- int \* const ptr1 = &a;

double const

- const \* int const ptr2 = &a;
- int const \* const ptr2 (is also legal syntax)

#

If you want an easier const use define.

- #define UNCHANGED 10
- Will do text replacement

#

gcc:

- c goes into preprocessor
- converted to .i, sent to compiler
- converted to .s, sent to linker
  - static linking (rarely used)
  - dynamic linking
    - dynamic runtime linking
- converted to .o, sent to assembler
- emits an executable, ./a.out

### Headers

- \#ifndef \_NAME_H
- \#define \_NAME_H

# February 7, 2019

- Cat
- Apple
- zebra
- cat

#

Headers files:

- Hold #defines, typedefs, structs, unions ... stuff you want to use in your code, but don't want to clutter your code up defining
- Can include other headers and libraries in a header file

#

- \#define \<name> \<value>
- by convention, things you define are all caps
- (and your var/func names are never all caps)

#

- ifndef \_NAME_H
- define \_NAME_H

#

Macro: definition with parameters

- ls -laF
- cat file.extension will print contents of file
- less for reading files (less is more; has more functionality than 'more' command)
- grep is powerful: grep thing test.c
- Piping
  - cat testclient.c | grep portno
  - cat testclient.c | grep a | more

#

If you dereference a function you:

- int \* fn(int) = &plusone;
- int (\* fn) (int) = &plusone;
- printf("%d\n", plusone(1));
- printf("%d\n", fn(1));
- pointer points to a memory address that has executable code

#

- You want to write a sort or bst
- You might need to compare strings vs integers
- You want general types

#

```C
int genericCompare(void * arg0, void * arg1, (*comparator)(void*, void*)) {

comparator(arg0, arg1);
// +1 1 -1
}
```

# February 12, 2019

## Recitation

## Lecture

Function Pointers, Macros, Header files

### Macros

Parameterized definition

- \#define something(x) x\*x
- \#define something(x) (x)\*(x) - if you expect them to always be numbers

### Function Pointers

int somefunction(char a, double b)

1. int(\*fn)(char a, double b)
2. int(\*fn)(char, double)
3. int(\*fn)(char, double) = somefunc;

#

Equivalent Function Pointers

- int(\*fn)(char, double) = somefunc;
- int(\*fn)(char, double) = &somefunc;

#

Called like: fn('a', 12);

#

Void stars can't be derefenced because, in order to dereference you must have a memory address, and the length of the memory (type).

#

    Pointer is an abstraction/reference

    Pointers are usually the same size (they are just a memory address)

#

File descriptor - atomic definition to describe a way to talk to things outside of your code, its an int

Three basic files descriptors:

- STDIN (0)
- STDOUT (1)
- STDERR (2)

"print to a file descriptor thats why its fprint"

```c
char message = "hello";
write(1, message, 5);
```

#

I/O Types:

- Blocking - what you'd expect from a function call - halts, runs I/O does not return until finished (gets suspended).
- Non-blocking - may return partway through - returns to you when you are next scheduled to run, and tells you how much was finished, will have to make another write call to finish the rest. I/O to network sockets as an example
- Asynchronous - have to talk to the CPU/Memory, its own operation with its own runtime.

# February 14, 2019

## Exam

February 26th

Exam topics

- Intro to C
  - typedef
  - enum
  - pointer
  - free/malloc
- shell commands
- headers
- macros

#

Short code, non-running code, code blocks

- Knowledge (What is the term ex. less)
- Function (How is struct/diff from union)
- Operation in practice (Will this segfault, execute this line what will happen?)

#

Top of lecture 8 at most

#

- File descriptors is an abstraction of I/O to an operating system
- allow you to read/write to things outside your code (memory space)

#

- read(), write(), open(), close()

fopen,fread is a wrapper around the above commands

#

- blocking
  - as soon as call is made, interrupts your operation and will not allow you to run until process it done
- non-blocking
  - as soon as call is made, interrupts your operation and will return the next time you are scheduled to run, bo matter how much is done (will return how much was done)
- async
  - set up call, once call is in motion it does not interact with you (except to possibly indicate when it is done)

#

```C
char buffer[] = "hello out there in TV land";
int length = 27;
int written = 0;
int offset = 0;

... have a file descriptor named fd

int status = 0;

do
{
    written += status;
    length -= status;
    status = write(fd, buffer+written, length-remaining);

} while(status > 0 && status < length && length > 0)
```

#

Nonblocking is useful for streaming, if you miss frames you can send the new ones

Files are nonblocking, sockets are blocking

#

Directories are essentially just larger names

#

Absolute vs Relative pathnames

#

- The hardrive does not know what a file is
- A massive circular array of things typed disk-block
- Create a linked-list if the file is larger than the disk-block chunk
- Need some metadata, address of disk blocks, names, size, who made it, day it was made, protections
- Store metadata on disk drive
- Metadata about metadata

#

```
bootblock | superblock | info-node (i-node) | user
```

#

- Split hard-drive into user and system

# February 19, 2019

If your data is bigger than one disk-block, use multiple "consecutive" disk-blocks

- user data: disk-blocks that hold user data
- inode: disk-blocks that hold inodes (file metdata)
- super: disk-blocks that hold information about inodes (metametadata)
- boot: disk-blocks that hold basic drive, OS, and superblock info (metametametadata)

#

- cat: dumps to standard out
- more: lets you scroll file
- less: at least what 'more' does, backslash and search
- grep: regular expression matcher, can be run on file
- '|': pipe composes commands
- '>': redirect output, can log command output, so it doesn't scroll past you, will replace file if ran again
- '>>': will append to the end of the file

#

### Indexed Allocation: UNIX FILE

    direct mapped ptr
    single indirect ptr
    i-node
    p-node

- direct mapped pointers used when the file is too larged

# Feb 28, 2019

blocking IO:

- write(fd, buffer, 100);

non-blocking

```C
int status = -1;
int written = 0;
int n = ... however much you need to write.;

do {
    status = write(fd, buffer + written, n-);
} while(status != -1 && written < n);


```

#

### i-nodes

- i-nodes are why files exist.
- provides the file abstraction
- metadata about your 'file'
  - owner
  - protections
  - dates (modified, created ..etc.)
- list of pointers (addresses) of disk blocks that make up the file
- i-node number, stores the index to the name (not actually the name)

`ls -i For each file, print the file's file serial number (inode number).`

### p-nodes

#

same size as an i-node, but all space is used to hold pointers (either direct, or some amount of indirect) of a given type

`ls /dev` is where all your i-nodes exist

`ls /proc/` - a special filesystem in Unix-like operating systems that presents information about processes and other system information in a hierarchical file-like structure

`cat "proccess inside /proc"` will give you information about a process

This is not memory it is a parsing of operating system tables

#

You can't put executable code in a headerfile, when you start importing code through a headerfile, it becomes a library

.h files (header files) don't get compiled.

- libraries
- Makefiles

#

```C
int plusone(int); // You're telling compiler, "Trust me this function exists"
```

Library files do not contain a main. You don't invoke them directly.

You keep at function prototypes in headerfile, but functions inside an actual .c file.

Convention is to import the headerfile in the .c file in order to import datatypes that may be required by the functions.

Gcc by default attempts to compile a file and build into an executable, but libraries have no main(). You need to give gcc a switch.

`gcc -c mystuff.c` will emit an object file.

`gcc test.c mystuff.o`

#

headers:

- definitions (#define)
- declarations (names ... int a ... typedef, structs, unions, enums)
  - function prototypes

libraries:

- runnable implementations of function prototypes in header
- no main
- can include other headers/libraries

### Makefiles

In order to make compilation a one-step process, we use makefiles.

Must. be. a. tab.

```Makefile
<directive>: |requirement0 ... |
    <cmd>
```

```Makefile
clean:
    rm a.out; rm mystuff.o
```

A semicolon on the line with the target-prerequisite is the first command line to execute for this rule, at least in GNU make.

- You can automate testing in a Makefile
- http://www.cs.toronto.edu/~penny/teaching/csc444-05f/maketutorial.html

```Makefile
test0:
    ./a.out
```

#

diff - shows you where lines differ between files

```Makefile
testSomething :
	program.exe < input.txt > output.txt | wc (wordcount)
	diff correct.txt output.txt
```

"Make: make your life better - Francisco"

# March 5, 2019

makefiles

- automate workflow, and compilation process

libraries

- a bunch of compiled C functions that can be used by source files
- no main
- compile with '-c' flag to halt compilation after compile phase
  - compiles to object file
- include prototypes for all library functions in a \<libname\>.h

i-nodes as a general representation strategy

- make direct-mapped pointers point to something else
- directories: point to other i-nodes
- processes?: (/proc) point to decoded OS process information
- devices?: (/dev) point to decoded OS IO device information
- inode: metadata attached to pointers

#

# March 7, 2019

talked about the project.

- next project about i-nodes
- they index files
- parse inodes directly
- errno

#

# March 26, 2019

lseek:

- returns number of bytes traversed (size of file)
- can lseek out 300mb, but only gives you memory when you write to file.
  - find length of file
  - move the next file IO operation
  - pad 0's out some amount of s(does not actually write 0's until you write to the file)

open("./output", O_CREAT | O_RDWR, )

```
u   g   o
rwx rwx rwx
110 100 100
6   4   4
```

```
  MEMORY
+--------+
| GLOBAL |
|        |
| INST0  |
|        |
| DATA1  |
| INST0  |
|        |
| HEAP   |
+--------+
```

Stack contains stack frames, and current running stack frame is called the activation record.

#

A **process** is some organization of memory that represents running code.

- OS abstraction for running code
  - address space: memory segment allocated to the process
  - process control block: is allocated in OS space, holds OS metadata about your process like:
    - PID (Process ID)
    - PPID (Parent process ID)
    - Open File Descriptors
    - Signal Disposition

A process is built on your behalf when you write '/'

#

New processes come from a fork (cellular mitosis)

- not actually a duplicate

fork(), called once, returns twice.

Child and Parent called fork and waiting for it to return. Parent returns 0, -1 to child, child returns PID of process to parent.

```C
int pid = fork();

if (pid == 0)
{
    // do child stuff
} else if (pid < 0)
{
    // error
} else {
    // do parent stuff
}

```

#

```C
int pid = fork();

if (pid == 0) {
    exec("./a.out");
}
```

exec() is called once in child, but returned to no one \*

\* in normal operation exec never returns, in error it will return.

#

Must call wait() to ensure the child processes will be closed (zombie process)

Orphan process: parent has left system whether process is finished or not.

Zombie process: ran all executable code but cannot leave the system, parent has not called wait on it whether it exists or not.

Zombie orphan if both states.

Examples:
Main process segfaults, process is now orphaned, when it finishes execution it becomes zombie orphan

# March 28, 2019

create:

- fork()
  - create a 'duplicate' of the current proc
    - current: parent
    - 'duplicate': child
  - immediately after fork():
  - address space
  - pid
  - ppid
  - of parent and child are different, but everything else is the same, including execution context.
    - stack frame (store of instructions and data)
    - values loaded in CPU (registers & program counter)

'context switch' change to a different exec. context

... since parent and child execution contexts are the same, they have to be in the same state, i.e., just called fork() and are waiting for it to return.

... so how do they tell themselves apart?

- parents fork() will return with child's PID (strictly > 0)
- childs fork() will return with 0

how to get child Proc to run a different executable?

- exec()

exec() deallocates everything in current process, and reallocates it for a new executable that loads and runs

#

- ps aux | grep \<username>
- kill \<process_id>

#

How to get rid of a zombie-orphan?

- init() (or scheduler) will call wait() on it

Signal:

- Exceptional computation...
- Swap out your execution content, swap in OS, figure out what to do, do it, then return control to USR (i.e., swap you back in)

If it does not need to quit your code, will resume you at the instruction you were running when the signal went off:

- inst 0
- inst 1
- in... signal...
  - load os
  - figure out what to do
  - do it
  - return to USR
  - reload USR
- inst 2
- inst 3
- inst 4

# April 2, 2019

Zombieorphans are taken care of by the scheduler/init it makes itself the Proc's parent and calls wait() on it.

- Usually done by PID 0 (wait, this is not forkable).

#

PCB - OS metadata about a process

Signals... Software interrupt ... not necessarily a problem, but something imporatnt to be dealt with >now<

Exit signal: a process posts exit after return to indicate it is ready to be reaped

- can cause it with exit() (or just return from main...)
- can catch it with atexit()

#

- return: get out of current stack frame to calling one (i.e. back out of current exec context and restore previous)
- exit: get out of current process, normally
- \_exit(): I want out now! (run minimum of code to get out of current Proc ..no exit signal (will not run atexit() ))
- exit (- 9) is last resort next to rebooting

#

- kill: send a signal to a Proc. by default, signal to end proc
- killall: kill all procs with same name (very strict)

#

tracking procs:

- ps (aux)
- top

before testing anything with fork() ... set ulimit

#

What if you don't need all the resources of a process, but you need another context... (thread)

Execution context:

- Stack : stored in main memory (in Process address space) .. contains instructions & data (local)
- registers and PC

Allocate some heap space, format it to look like a stack

Write instructions in to it, write data into it. Write stored registers and a PC

- jmp to the new stack

#

Flavors of threads:

- User
- \+ faster to build
- \+ complete control over scheduling
- \- notoriously buggy scheduling
- \- can't share runtime over everything in the system
- \- no true simultaneity
- \- blocking will stop Proc

#

- Kernel
- \- slower to build
- \- no control over scheduling
- \+ pretty solid scheduling
- \+ can share runtime over everything in the system
- \+ true simultaneity
- \+ blocking will not stop Proc

```C
int pthread_create(
    thread handle:      pthread_t *thread
    thread attributes:  const pthread_attr_\t *attr
    function for thread to run: void *((start_routine)(void *), void *arg);
    function's args:    void *arg
)
```

# April 4, 2019

Threads:

- Multiple execution contexts in the same Process
  - Parallelization (faster/easier access than Procs)
  - have it do anything that might block you, that you don't want to wait for(\*)

User - scheduled by user

- no:
  - true simul
  - run while another is blocked
  - time based on # of threads
- yes:

  - full control
  - fast build, takedown, swap

- kernel - scheduled by kernel
- yes:
  - true simul
  - run while another is blocked
  - time based on # of threads
- no:
  - full control
  - fast build, takedown, swap

Kernel - scheduled by kernel

#

```C
Thread A        Thread B
mv(%r2) %r3
incr %r3
                mv(%r2) %r3
                incr %r3
                mv %r3 (%r2)
mv %r3 (%r2)
```

In this case there is a race condition between threads, whoever writes last is what the value becomes.

If you want to do the opposite you need to create a mutex.

mutual exclusion => Mutex
