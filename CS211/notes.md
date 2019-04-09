# Computer Architecture <small> with Professor Brian Russell</small>

## June 25th, 2018

### Filename: Arglist.c

```C
/**
*   argc: the number of arguments
*   argv: array of pointers (arguments)
*   - returning any non-zero is considered error
**/

int main (int argc, char **argv) {
    int i;
    for (i = 0; i < argc; i++) {
        printf("Arg %d is %s\n", i, argv[i]);
    }
    return 0;
}
```

### How the compiler creates an executable

#### C-Compiler:

| .c, .h              |        .s        |               .o |
| ------------------- | :--------------: | ---------------: |
| Machine Independent | Machine specific | Machine specific |
| OS Independent      |   OS specific    |      OS specific |
| Human-readable      |  Human-readable  |     Not readable |

- Assembly file: gcc -S arglist.c
- Object file: gcc -c arglist.c

#### Java JAVAC:

| .Java source        |      .class      |
| ------------------- | :--------------: |
| Machine Independent | Machine specific |
| OS Independent      |   OS specific    |
| Human-readable      |   Not readable   |

#### C-Headerfile Example:

```C
/**
*   Note:
*   - You don't have to name parameters in declaration
*   - If you're calling assembly use "extern"
*   - You may see "_FACTORIAL_H_" instead
**/

#IFNDEF factorial.h
#DEFINE factorial.h

int factorial(int);

extern int nCr(int n, int r);

#ENDF
```

### C-datatypes

    * Basic arithmetic type specifiers:
        char,
        int,
        float,
        and double.
    * Modifiers:
        signed,
        unsigned,
        short
        and long.

    Examples:
    = char
    = short
    = short int
    = long int
    = long long

_Note: Bit-size will be different lengths depending on the machine_

### C-variables

The first character is alphabetical, other alphanumeric

#### Escape Characters:

    '\'' single quote
    '\a' bell
    '\b' backspace
    '\f' formfeed
    '\n' newline
    '\r' carriage return
    '\t' tab
    '\v' vertical tab
    '\\' backslash
    '\"' double quote
    '\e' escape

### A Faulty Program

```C
/**
*   Program has allocated a given amount of memory
*   for an array, 10. The for-loop attempts to access
*   a pointer to a memory-space that wasn't allocated.
*   C does exactly what you tell it to do, no array
*   bounds check like in Java. The program will begin to
*   overwrite whatever is at that pointer. Variables are
*   stored near eachother but have 'padding' between, in
*   this case, the pointer overwrites the loop counter.
**/

int main() {
    int array[10];
    for (int i = 0; i <= 11; i++) {
        array[i] = i;
    }
    return 0;
}
```

_A process can only touch its address space
under 'user mode'_ (Other being Kernel mode).

Under **_user_** mode, the kernel translation table converts **Virtual** addresses to **Physical** ones,

### C-Library Functions

`#include <stdio.h>`

```C
// FmT is a string that may contain format specifiers

int printf(const char *c, FmT, ...)
int fprintf(FILE * f, const char *c, FmT, ...)
int sprintf(char * str, const char *c, FmT, ...)
int snprintf(char * str, size_T size, const char *c, FmT, ...)
```

Three standard-outputs:

1. STDIN
2. STDOUT
3. STDERR

## June 27th, 2018

### C-structs

```C
struct coord {
    int x;
    int y;
} A, B, C;

struct rectangle {
    struct coord topLeft;
    struct coord bottomRight;
    struct coord origin;
    struct coord endpoint;
}

// Instance with optional initializer
struct rectangle box = {{0,5},{5,6}};

/**
*   Each of a structs' members have a distinct value,
*   changing one doesn't change another.
*   - A Union DOES change other members, discussed later.
**/

struct rectangle boxWhere;
box.topLeft.x = 14;


```

#### Flexibility of Structures:

```C
struct madeItUp {
    int x;
    char c;
    char name[20];
    float w;
};

struct madeItUp obj = {1, 'T', "Fred", 4.37};
```

### C-Pointers

A pointer contains an address, an address is a location in memory.

    (*)POINTER TO <-> (&)ADDRESS OF

- `int x, y;`
- `int *px, *py;`

You can assign the address of a variable to a pointer

- `px = &x`

Use the unary operator \* to access (dereference) value of a given pointer.

- `x = *px;`
- x = 4 (Made up the value).

```C
Set px to the address of x:
- px = &x; // px = MEM-12345

Set the value of address px contains to 3:
- *px = 3; // MEM-12345 = 3

y = *px; // y = *px = 3;
px = 0; // ERROR: You cannot dereference now.

// variable 'y' would point to a NULL-pointer

To dereference (change value) safetly:
px = &y; // px still points to something
*px = 5; // Safetly change value
```

You should never return a pointer to a local variable inside a function. The local variable may be overwritten over the course of your program resulting in a NULL pointer.

### Switch statement lowercase/uppercase (Feb. 5, 2019)

```C
switch(e)
{
    case 'A':
    case 'a':
    printf("Case insensitive switch statement");
    break;
}
```

### Some convenience in C

`char *s = "hello;` - Read-only char array.

```C
struct coord point;
struct coord *p;

p = &point;
p -> x = 3; // (*p).x = 3
p -> y = 5; // (*p).y = 3;
```

`void *vp` - Generic pointer

You can assign **_any type_** of pointer to a **_void_** pointer.
You can also assign **_void_** pointer to **_any type_** of pointer.

### C-Pointer Arithmetic

Incrementing / Decrementing a pointer's value will shift it onto the **_adjacent_** memory-address of equal space.

    ++ p
    -- p
    p ++
    p --

You could assign a pointer to an array, then increment through array.

```C
int x[10] = {1, 2, ..., 10};
int *p = x;
p ++; // Ends up being 2.
```

### ASCII: American Standard Code for Information Interchange

A character coding scheme which maps characters to a bit-pattern.

#### Range of ASCII:

    0 - 127 are ASCII characters

    128 - 255 not ASCII

    0 - 31 are not printable characters*

#### Lexicographical Order:

    Digits < Uppercase letters < Lowercase letters

_Note: Same as their numerical representation_

### Number representation on computer

#### Decimal:

- 625 = 6 _ 100 + 2 _ 10 + 3 \* 1
- 625 = 6 _ 10^2 + 2 _ 10^1 + 3 \* 10^0
- Number = n \* (base)^(position)

#### Ways to represent negative numbers:

1. Signed magnitude: uses a sign-bit - issue: two zeros
2. One's complement: flip the bits - issue: two zeros
3. Two's complement: flip & add 1, ignore carry-bit

### Shifting

#### Left-shift:

Like **_multplying_** number by 2^n. Does **not** save the sign-bit.

    0000 0001 <<
    0000 0010

`y = x << 2;`

#### Right-shift:

Like **_dividing_** number by 2^n. Is a
**Sign-preserving** shift.

    0000 1000 >>
    0000 0100

`y = x << 2;`

#### Arithmetic right-shift:

In **signed**-binary, a _logical shift_ can cause the sign to change.

- An Arithmetic shift is used on a two's complement number
- The sign-bit is copied, as well as, shifted to the right
- Arithmetic left-shift = Logical left-shift

Why use it? Ideal for signed two's complement numbers

#### Logical right-shift:

- Ideal for unsigned binary numbers, since most significant-bit isn't lost

#### Logical & Arithmetic left-shift:

- Arithmetic left-shift = Logical left-shift
- Useful for multiplying numbers
- Should only be used on unsigned numbers

### Type Protection Rules in C

- Types will be implicitly converted if two different types are used together
- Using the unsigned modifier will convert normal types into unsigned

        Normal:
        char -> short -> int -> long
        |
        v
        Unsigned:
        char -> short -> int -> long

### Bitwise Operators

- |
- &
- ^
- ~

OR, AND, XOR, NOT

XOR is like binary add but with no carry bit

Operands are a bit-pattern, result is also a bit pattern

### PA1: Data Representation and Computer Arithmetic

```C
/**
*   Decimal ASCII to Two's Complement
*
*   inputs: - char *s   // Decimal string, NUL terminated
*           - int *n    // Pointer to Two's Complement Num
*   output: - success / failure
*
*   Pseudocode, s[i] - '0' works because of the way that
*   characters are represented in a computer versus their
*   true values, essentially (N + 30) is the character code
*   for a number, and '0' = 30, so subtracting '0' from the
*   ASCII representation of a number is the same as for
*   example, 39 - 30 = 9, the Two's
*   Complement representation of 9.
**/

if (s == \0) {
    complain
    return failure
}
if (s[0] == '-') {
    isNegative = 1;
    i = 1;
} else {
    isNegative = 0;
    i = 0;
}
value = 0;
while (s[i] != '\0') {
    if (isDigit(s[i])) {
        value = 10 * value + s[i] - '0';
    } else {
        complain
        return failure
    }
    i += 1;
}
```

ASCII 0 & 9, In Hex:

- `'0' = 0x30`
- `'9' = 0x39`

```C
if (isNegative) {
    *output = - value;
} else {
    *output = value;
}
return success;
```

```C
/**
*   Hex ASCII to Two's Complement
*
*   inputs: - unsigned long value
*           - char *s   // Pointer to 65-char ASCII string
*   output: - success / failure
**/

if (s == 0) {
    complain
    return failure
}
value = 0;
int i = 0;
while (s[i] != '\0) {
    switch (s[i]) {
        case '0': value = value << 4; break;
        case '1': value = value << 4 + 1; break;
        case '2': value = value << 4 + 2; break;
        case '3': value = value << 4 + 3; break;
        case '4': value = value << 4 + 4; break;
        case '5': value = value << 4 + 5; break;
        case '6': value = value << 4 + 6; break;
        case '7': value = value << 4 + 7; break;
        case '8': value = value << 4 + 8; break;
        case '9': value = value << 4 + 9; break;
        case 'a': case 'A': value = value << 4 + 10; break;
        case 'b': case 'B': value = value << 4 + 11; break;
        case 'c': case 'C': value = value << 4 + 12; break;
        case 'd': case 'D': value = value << 4 + 13; break;
        case 'e': case 'E': value = value << 4 + 14; break;
        case 'f': case 'F': value = value << 4 + 15; break;
        default : complain + fail
    }
    i += 1;
}
```

```C
/**
*   Two's Complement to Decimal ASCII
*
*   inputs: - long value
*           - char *s   // Pointer to ASCII string
*   output: - success / failure
**/
if (s == 0) {
    return failure;
}
if (value < 0) {
    value = - value;
    isNegative = 1;
} else {
    isNegative = 0;
}
int i = 0;
do {
    x = value % 10;
    s[i] = '0' + x;
    value = value / 10;
    i += 1;
} while (value > 0);
if (isNegative) {
    s[i] = '-';
    i += 1;
    s[i] = '\0';
}
reverse(s); // String is currently backwards
return success;
```

```C
/**
*   Two's Complement to Binary ASCII
*
*   inputs: - unsigned long value
*           - char *s   // Pointer to 65-char ASCII string
*   output: - success / failure
**/

if (s == 0) {
    complain
    return failure
}
s[64] = '\0';
for (int i = 63; i >= 0; i--) {
    x = value & 0x00000001; // Masking to get low-bit
    if (x == 0) {
        s[i] = '0';
    } else {
        s[i] = '1';
    }
    value >>= 1;
}
return success;
```

## July 9th, 2018

```C
struct FI {
    float fpart;
    int ipart;
}

union FI {
    float fpart;
    int ipart;
}
```

1. Size of union is size of largest member of the union
2. All members of a union occupy the same space
3. All members point to same memory-address

### Bit-Ordering

A bit identification convention independent of byte ordering (endianess).

+------+ +-------+ +-----+ +------+
| char | | short | | int | | long |
+------+ +-------+ +-----+ +------+
7 0 15 0 31 0 63 0

+---------+
| bit |
+---------+
MSB LSB

### Bit-Masking

Using bitwise operations (and, or, not) on intergers of various sizes to capture and manipulate single or multiple-bit values.

1. Use bitwise OR with a pattern of 1's to ensure certain bits are on (set to 1).
2. Use bitwise AND with a pattern of 0's to ensure certain bits are off (set to zero).

Capture low-order 23 bits of a 32 bit number

```C
int x, y;
:set x;
y = x & 0x007fFFFF; // 0111 1111
```

Capture some bits: bitwise and with a pattern of 1-bits. The result is captured bits, all other bits are zero

What is the mask to capture the low order 52-bits of a 64-bit long?

- `0x000F-FFFF-FFFF-FFFF`

### C-Library Functions for NUL-Terminated Strings

```C
#include <string.h>

char *strcpy(char *DST, const char *SRC);
char *strncpy(char *DST, const char *SRC, size_T MAXLEN);
// MAXLEN = sizeof(dest buffer)
char *strcat(char *DST, const char *SRC);
char *strncat(char *DST, const char *SRC, size_T MAXLEN);
int strcmp(const char *S1, const char *S1);
int strlen(const char *String);
```

- S1 < S2 = -1
- S1 = S2 = 0
- S1 > S2 = 1

### C-Library Functions for Raw Memory

```C
#include <string.h>

void *memcpy(void *dst, const void *src, size_T length);
int memcmp(const void *s1, const void *s2, size_T length);
```

### C-Program Structure

- source files .c
  - definitions of functions
  - global variables
  - static variables
  - a single source file is a scope
- header files .h
  - function declarations
  - program specific type definitions
  - \#Defines
  - \#include of other header files
  - typedefs

## July 11th, 2018

### Makefiles

- The 'make' command looks for a makefile with the following names:
  - makefile > Makefile > s.makefile > s.Makefile
- Tabs are standard syntax of makefiles, be careful not to use spaces for indents

        make -i     will continue over errors
             -n     will show whats being compiled
             -f     filename

```makefile
cc = gcc
cflags = -std99 -g -Wall

all: factorial calc
        gcc $(CFLAGS) -o factorial factorial.c main.c

factorial: factorial.o main.o
        gcc $(CFLAGS) -c factorial.c

main.o: main.c factorial.h
        gcc $(CFLAGS) -c main.c

clean:
	-rm -f *.o
	-rm -f *.h.gch
```

- Macros tend to be all caps
- Macros at top of file
- Macros defined before use
- Commands indented by one character
- End-of-line comments starts with \#

### C-Typedefs

create new names for data types

```C
typedef int length;
length len, maxlen;
length * PTR;

typedef char * string;
string p; // Same type
char * p2; // Same type

typedef int area;
area a,b,c;
length x,y,z;

// Pointer to function
typedef int (*comparator)(const void *, const void *);

int myIntFcn(const int *, const *);
qsort(mylist, 34, 22, (int(*)(const void *, const void *)) myIntFcn);
```

### C-Enumeration Types

**_Enums are scalar_**

```C
enum stoplight {red, yellow, green};
enum stoplight EaF;
EaF = green;

switch (EaF) {
    case RED:; break;
    case YELLOW:; break;
    case GREEN:; break;
    default:;
}
// Note: There is no quotes around an enum
```

### IEEE-754

#### Decimal Scientific Notation:

Some magnitude times 10 to some positive or negative power

    1 = 1x10^0
    3000 = 3000x10^0
    412 = 412x10^0
    .001 = .001x10^0 = 1x10^(-3)
    1 = 1x10^0

a floating point number has:

- a magnitude
- an exponent
- a sign

A **normalized** decimal scientific notation number has a magnitude:

- 0 <= magnitude < 10

#### Binary Floating Point:

A binary magnitude times 2 to some positive or negative power

```
              *Normalized*
1 = 1 x 2^0
2 = 1 x 2^1   = 1 x 2^1
4 = 1 x 2^2   = 1 x 2^2
3 = 11 x 2^0  = 1.1 x 2^0
5 = 101 x 2^0 = 1.01 x 2^2
```

Binary floating point:

- 0 <= magnitude < 2

```
1/2 = 1 x 2^(-1)
1/4 = 1 x 2^(-2)
1/8 = 1 x 2^(-3)
1/3 = 1.010101 x 2^(-2)
1/5 = 1.0011001100 x 2^(-3)
```

A binary floating point has:

1. A magnitude
2. A exponent
3. A sign

#### Exponent Bias:

IEEE floating point numbers need to represent positive and negative exponents in k-bits => A range of 2^k different values.

Exponent bias maps negative and positive exponents to a range of positive numbers by adding a **_bias value_** to the exponent. The bias values for k-bits is 2^(k-1) - 1

An exponent of value n is representable as an IEEE-754 exponent as: n+2^(k-1) - 1

Any fixed pointer k-bit integer has m many representations noted as 2^k.

Exponent range for 32-bit float: [127, -126]
Bias exponent value in IEEE-754

- 127 + -126 = 1
- 127 + 127 = 254

| Exponent | Exponent + Bias | Repping |
| -------- | :-------------: | ------- |
| 127      |    254 + FE     | 2^127   |
| 2        |    129 + 81     | 2^2     |
| 1        |    128 + 80     | 2^1     |
| 0        |    127 + 7F     | 2^0     |
| -1       |    126 + 7E     | 2^-1    |

Converting 263.3 into IEEE-754

```
263 % 2 = 1
131 % 2 = 1
65  % 2 = 1
32  % 2 = 0
16  % 2 = 0
8   % 2 = 0
4   % 2 = 0
2   % 2 = 0
1   % 2 = 1
Binary: 100000111 = 263

0.3 x 2 = 0.6   0
0.6 x 2 = 1.2   1
0.2 x 2 = 0.4   0
0.4 x 2 = 0.8   0
0.8 x 2 = 1.6   1
0.6 x 2 = 1.2   1
Binary: 0100110011... = 0.3

Merge binary together
1) 263.3 = 100000111.0100110011
Scientific Notation: left-shift dot 8 times
2) 1.000001110100110011 x 2^8

IEEE-754
sign-bit | exponent-bits | (fraction-bits / mantissa)
x|xxxxxx|xxxxxxx

0 | 127 + 8 = 135 | Decimal from #2

3) 0 10000111 000001110100110011

263.3 = 0100 0011 1000 0011 1010 0110 0110 0110 (32-bits)
```

Positive \ Negative: Inf, NaN

### Dynamic Memory

```C
#include <stdlib.h>
void * malloc (size_t size);
void * realloc (void * ptr, size_t newSize);
void free (void *);

typedef struct node {
    int data;
    struct node * next;
} node;

node * P;
    P = malloc(sizeOf(node));
    P -> data = 3;
    P -> next = 0;

Node * head = 0;
Node * tail = 0;
int i;
for (i = 0;i < 10;i++) {
    if((p = malloc(sizeof(node))) == 0) {
        // complain about malloc failure;
    }
    else if (head == 0) {
        head = tail = p;
        p -> data = i;
        p -> next = 0;
    }
    else {
        tail -> next = p;
        tail = p;
        p -> data = i;
        p -> next = 0;
    }
} // End of loop

for (p = head; p != 0; p = next) {
    printf("%d\n", p -> data);
}
Node * next;
for (p = head; p != 0; p = next) {
    next = p -> next;
    free(p);
}
```

1. Only free things made from malloc or realloc
2. Always free things you malloc.
3. Never use pointer to something you free
4. No pointer arithmetic from what you free
5. Do not free local or global variables

## July 16th, 2018

Assembler is machine specific, prints out machine instructions

### Von Neumann Architecture

- Cannot push memory or machine code at the same time.
- Link between CPU and Memory is called a bus
- Instruction fetch, and data transfer share same bus.

### Harvard Architecture

- Added another bus

### Computer Internal Components

Central proccessing unit (CPU)

- Arithmetic logic unit
- Registers - local fast storage
- Program Counter / Instruction Pointer
- FLAGs

Memory

- Random Access Memory (RAM)
  - Address specified in hex
  - Volatile
  - Holds instructions, data

Bus

- Connects CPU, Memory
- I/O devices

Arithmetic Logic Unit (ALU)

- Fixed point arithmetic instructions:
  - ADD, SUB, MUL, DIV, ...
- Floating point arithmetic
- Bitwise operations
- Comparision operations:
  - FIXED-PT
  - FLOATING-PT
  - SET CONDITIONAL FLAGS
- Control-Flow Changing Instruction Pointer Value (May use condition flags)
- Character operations
- Interrupt operations

Fetch, Decode, Execute Cycle

START:
A hard-wired (non-volatile) architecture-specific value is put into Instruction Pointer when computer is powered up. Starts loading and executing OS, thus "booting" the OS.

FETCH:
Get instruction from memory at address in Instruction Pointer register

DECODE:
Determine operation rom instruction get operands

EXECUTE:
Do operation, put outputs of operation in output operands. Change Instruction Pointer to point to next instruction to execute - not necessarily next physically adjacent instruction.

### Register Intel Architecture

### Assembly Instructions

- SHRL
- SHLL
- SARL
- SALL

## July 18th, 2018 - Was 30 mins. late

```
32-bit src    dst
imul   mem32, reg32
imul   reg16, reg32
imul   reg32, reg32
imul   imm8,  reg32
imul   imm16, reg32
imul   imm32, reg32
```

```
64-bit src      dst
imul   mem,     reg64
imul   reg16,   reg64
imul   reg32,   reg64
imul   reg64,   reg64
imul   imm8,    reg64
imul   imm16,   reg64
imul   imm32,   reg64
imul   imm64,   reg64
```

```
CONDITION FLAGS:
CF - carry flag
ZF - zero flag
SF - sign flag
OF - overflow flag
```

```
JUMPS:
JLE
JBE
JS
JNS
JNG
JNA
```

## July 23th, 2018

Ordering of bytes differ per hardware

#### Big Endian

MSB first decreasing numberic signifigance as byte address increases: Motorola, Sparc, IBM

- `0A0B0C0D` = `0A0B0C0D`

#### Little Endian

LSB first increasing numeric significanes as byte address increases:
Intel, Vax, Z80

- `0A0B0C0D` = `0D0C0B0A`

### Overflow

- Arithmetic operation attempts to creae a numeric value that is outside the range of that can be represented with a given number of bits.

```
8-bits [0, 255]
16-bits [0, 65535]
32-bits [0, 4294967295]
```

- When arithmetic produces a result larger than max-value for an n-bit integer, an overflow reduces the result to modulo 2^n retaining only the least signifigant bits of result.

```
ADDL rA, rB
(rA > 0 && rB > 0 && Difference < 0 ||
 rA < 0 && rB < 0 && Difference > 0)

SUBL rA, rB
(rA < 0 && rB > 0 && Difference < 0 ||
 rA > 0 && rB < 0 && Difference > 0)

MULL rA, rB
(rA > 0 && rB > 0 && Product < 0 ||
 rA < 0 && rB < 0 && Product < 0 ||
 rA < 0 && rB > 0 && Product > 0 ||
 rA > 0 && rB < 0 && Product > 0)
```

### Formatted Input

Format Specifiers

```
chars   %c
strings %s
ints    %d
        %o
        %u
        %x
floats  %f
        %e
        %g
doubles %lf
        %le
        %lg

scanset for char arrays
    %[ABCDEF]
    %[A-F0-9]
    %[^\n]
```

```C
while (printf("Enter an integer >>"), scanf(" %d", &x) > 0)
 {
     do stuff with x
 }
```

Comma operator seperates multiple expressions, value of comma-seperated list is right-most expression in the list.

### Sizeof

- sizeof(char) = 1
- sizeof(int) = 4
- sizeof(float) = 4
- sizeof(long) = 8
- sizeof(double) = 8

#### Const:

Qualifier **const** can be applied to any declaration to ensure the variable will not change value.

`const double pi = 3.141592...`

Must have initializer, can apply to formal parameter to ensure function does not change value

## July 25th, 2018

### C-Preprocessor

- Macro Substitution
- Inclusion of Named Files
- Conditional Compilation

```C
#include <filename> // Look in /usr/ include
#include "filename" // Look in local
```

Filenames can be:

1. **simple** no "./" local to current directory
2. **relative** does not start with "/" but contains "/"
3. **absoulute** starts with "/" unambiguous

#### C-processor conditionals:

```
#IF constant-expression
#IFDEF IDENTIFIER
#IFNDEF IDENTIFIER // previous from #define
#ELIF constant-expression
#ELSE
#ENDIF
```

conditional compilation statements can nest

```
#IFNDEF myhdr_h    // Best use of conditional compilation:
#DEFINE myhdr_h     // Multiple inclusion protection

#ENDIF
```

gcc -c DDEBUG myProg.c

printf("y is %d File %s Line %d\n", y, \_\_File\_\_, \_\_Line\_\_);

```
#IFDEF ENTERTEXT
printf("Enter function somfcn %s: %d\n", \_\_File\_\_, \_\_Line\_\_);
#ENDIF
#IFDEF ENTEREXIT
printf("Exit function somfcn %s: %d\n", \_\_File\_\_, \_\_Line\_\_);
```

Static: can't access outside of source file

1. function
2. variable
   - in a function
   - outside function

`extern int indent; // Nonstatic variable`

1. Only one instance of a static variable within a function even if function is recursive
2. Static variables do not reside in the processes callstack
3. Static variables retain their value between calls

#### Process Address Space:

```
+---------+ 0000 (LOW)
|  .text  |
+---------+
|  .data  |
+---------+
|  .bss   |
+---------+
| .rodata |
+---------+
|  HEAP   |
|    |    |
|    v    |
|         |
|    ^    |
|    |    |
|  STACK  |
+---------+ FFFF (HIGH)
```

- registers are not in memory

Load effective address

- LEAL : 32-bit
- LEAQ : 64-bit
- LEAQ (SRC, DST)
  - SRC : any indirect addressing mode
  - DST : must be a 64-bit register
- LEAL 40(%EAX), %EBX
  - Adds 40 to content of %EAX, puts sum in %EBX
  - Moves variable address
- LEAQ -12(%RBP), %RAX
- MOVQ %RAX, -20(%RBP)

```C
int x;
int *p;
p = &x;
```

```
Efficient Sum Code:
LEAL (%EDI, %ESI), %EAX
RET
```

```C
Char ** argv
// We want argv[0][0]
movq (%RBX), %RAX #DEREF
movb (%RAX), %AH #DEREF AGAIN
```

#### Call stacks:

calling a function:

1. Caller evaluates args, put args in register or on stack (per compiler implementation).
2. Caller calls function
3. Function saves frame pointer, makes new frame pointer for new frame
4. Called function claims space for auto variables by subtracting size of all auto variables from stack pointer

- You shouldn't call functions before moving rsp, if you prematurely allocate memory on the stack, any push/pop will overwrite.

```
+-------------+
VARIABLE SPACE
+-------------+
OLD %RBP
RET ADDR
+-------------+
```

```
PUSHQ %RBP
MOVQ %RSP, %RBP
SUBQ $70, %RSP
```

%ax is the accumulator register

axiom: rbp points to current frame

- a frame contains:
  - local auto variables, if any
  - previous frame pointer
  - return address

```
call GCD
movq %rax, -8(%rbp)
movq %rbp, %rsp
popq %rbp
ret
```

call instruction:

- push address of next adjacent instruction onto callstack, this is return address
- move (copy) target address in call instruction into intruction pointer (%rip)

ret instruction:

- pop return address into %rip
- compiler adds extra space, for variables for unknown reasons (performance?)
- subq is used on 64-bit system, does not effect variables differently.
- can you use subl on 64-bit? guess so.

SALL - shift arithmetic long left
MOVL 0xDEADBABE, %EAX
SALL \$7, %EAX

## July 30th, 2018

### Phase 1: Read .Y86 Files, Build Memory Image

- .size directive (in file, malloc) tells you how much memory your program needs.
- .text gives initial value of an Instruction Pointer and HEX representation of Y86 machine instructions.
- .byte says put a one-byte value at specified address.
- .string says put the bytes in the string in Y86 memory, starting at a specified address.

#### Y86 Needs:

- Memory
- Flags: ZF, OF, SF
- Registers need 8, 32-bit registers (array of ints) encoded in instructions as 0-7
- Instruction Pointer register 32-bit initial value in .text directive implicitly changed as instruction execution proceeds.
- %ESP implicity decremented for push, incremented for pop

#### Reading Files:

    FILE * fopen(const char * filename, const char * mode);
    filename - from argv[1]
    mode:
        -r  read from beginning
        -w write
        -a append
    int fscanf(FILE *, const char * fmt, ...);
    int fclose(FILE *);

Some useful fscanf format specifiers:

- %s for directives (.size, .string, .byte, .text, etc)
- %x for size, address values
- %2x to read .text machine instructions put into int, then assign (with cast) to char

#### Phase 1 Test:

Put in debugging printf()s that say what (value, in hex) was put where (address)

### Phase 2: Fetch Decode Execute

Directives in .Y86 file initialize some Y86 memory. Registers and flags are not initialized
Implementation suggestion: one C function each Y86 instruction (some if-statements no loops) access is shared instruction pointer, registers, and flags. Returns state: Ok, Halted, Addrerror, Illegal Instruction

```C
// Only looping construct needed.
do {
    opcode = memory[ip];
    switch (opcode) {
        case 0x00: state = nop(); break;
        case 0x10: state = halt(); break;
    }
} while (state == ok);
```

    +------------+
    | 30F4...    | Machine Instructions.
    |------------|
    | Data       |
    | Local Vars |
    | Old %EBP   | <- %EBP
    | Ret Addr   | <- %ESP
    +------------+

```C
// Fetch, Decode, Execute Loop
do {
    opcode = memory[ip];
    switch (opcode) {
        case 0x00: state = nop(); break;
        case 0x10: state = halt(); break;
        case 0x20: state = rrmovl(); break;
        default: state = illegal instruction; break;
    }
} while (state == OK);
```

```C
state nop() {
    ip +=1;
    return OK;
}
```

```C
state halt() {
    ip +=1;
    return HALTED;
}
```

Instruction functions do decode and execute:

- decode: read remaining bytes of instruction if necessary, opcode determines length and bit-pattern of entire instruction.
- execute: do the operation, set condition flags as needed, put results back into memory or register as needed, change Instruction Pointer.

```C
// Fetch, Decode, Execute Loop
State Addl() {
    int sum;
    int RA, RB;
    RA =
    RB =
    sum = reg[RA] + reg[RB];
    reg[RB] = sum;
    OF =
    SF = sum < 0;
    ZF = sum == 0;
    IP += 2;
    return OK;
}
```

#### Incremental Implementation:

- write really small prog Y86 programs.

```
CALL 00000007
HALT
RET
```

## August 1st, 2018

### Y86 Flags

- OF: Overflow flag
- ZF: Zero flag
- SF: Sign flag

```
JE  ZF
JHE ~ZF
SIGNED > ~(SF^OF) & ~ZF
SIGNED >= ~(SF^OF)
SIGNED < SF^OF
SIGNED <= (SF^OF) | ZF
```

All Set Condition Flags:

```
CMPL
ANDL
XORL
ADDL
MULL
SUBL
```

- Conditional jumps use condition flags

### Digital Logic I

- Digital values: 0, 1
- 0's range is [0, .5]
- 1's range is [2.4, 2.9]
- Anything in between is illegal

### Basic Logic Gate Symbols

```
NOT: A ->* `A

OR: A -\ A + B
    B -/

NOR: A -\ `(A + B)
     B -/*

AND: A -) AB
     B -)

NAND: A -) `(AB)
      B -)*

```

- AND is like multiplication
- OR is (sort of) like addition
- You can put an \* (essentially an inverter) on input or output

### Logical Completeness

- You can implement ANY truth table with AND, OR, NOT.

### DeMorgan's Law

### More Than 2 Inputs

You split an AND up into the number of inputs: two AND gates for three inputs

### Decoder

For n inputs, can choose any one of 2^n seperate outputs.

### Multiplexer (MUX)

- bit selector and 2^n inputs, one output
- output equals one of the inputs, depending on selector
- 4-to-1 mux

### Half-adder

- How about an (almost) useful circuit?
- A Half-adder: Takes two binary inputs produces sum and carry as outputs
- Sum looks like XOR
- sum = A\`B + \`AB
- Carry looks like AND
- Carry = AB
- Half-adder can only add two bits, can't be combined to add more than two bits. We need a **Full-adder**

### Full-adder

Adds two input bits plus carry from earlier full adder

| A, B, CARRYin | Sum, CARRYout |
| :-----------: | :-----------: |
|    0, 0, 0    |     0, 0      |
|    1, 0, 0    |     1, 0      |
|    0, 1, 0    |     1, 0      |
|    1, 1, 0    |     0, 1      |
|    0, 0, 1    |     1, 0      |
|    1, 0, 1    |     0, 1      |
|    0, 1, 1    |     0, 1      |
|    1, 1, 1    |     1, 1      |

- Sum = A\`B\`C + \`AB\`C + \`A\`BC
- CARRYout = AB\`C + A\`BC + \`ABC + ABC
- Sum of Products
- Logical Expression
- ANDing of inputs (multiplication) takes place before ORing of bits (~= addition)

#### Let's Add Many Bits Together:

- 32-bit (Intel) long-bit
- Going to ADD:
- x = {x31, x32, ... x0}, to y = {y31, y32, ... y0}
- You will need 31 Full-adders

```
CARRY-FLAG: (x)
x1, y1  x2, y2    ...    x31, y31
+-----+ +-----+ +-----+ +------+
| FA1 | | FA2 | | ... | | FA31 |
+-----+ +-----+ +-----+ +------+
 sum1    sum2     ...    sum31
```

### Alternate Circuit Using XOR Gate

```
|-A ----|
|-B----XOR ---|
| C-----|--- OR -> Sum
| |     |
| |----AND ---|
|------AND---OR -> CARRYout
```

### Logical AND Looks Like Multiplication

- ABC
- Logical OR looks likes addition
- A + B + C
- Logical Negation
- \`A

### Algebraic Rules For Logic Expressions

- Commutative: w+y = y+w | wy = yw
- Associative: (w+y)+z = w+(y+z) | (wy)z = w(yz)
- Distributive: w+yz = (w+y)(w+z) | w(y+z) = wy + wz
- Idempotent: w + w = w | ww = w
- Involution: \`\`w = w
- Complement: w+w = 1 | w\`w = 0

#### DeMorgan:

- \`(w+y) = \`w \`y | \`(wy) = \`w + \`y
- 1+w = 1 | 0w = 0
- 0+w = w | 1w = w
- w+\`wy = w+y
- We can apply the algebraic rules to simplify a sum of products expression.
- Simplified expression -> Fewer circuit elements doing exactly the same job

Original SOOP expression for carry:

- \`ABC + A\`BC + AB\`C + ABC

Algebraic reordering

- \`ABC + ABC + A\`BC + AB\`C

Apply complement rule w+\`w = 1

- BC + A\`BC + AB\`C

Refactoring

- B(C+A\`C) + A\`BC

Apply Demorgan | w+\`wy = w+y

- BC + AB + A\`BC

Refactoring

- BC + A(B + \`BC)

Demorgan Again

- BC + AB + AC

### Reflective Binary Numbering System Where Successive Values Differ By One Bit

Formal Definition: A gray code assigns to each of a contiguous set of integers or to each member of a circular list, a word of symbols such that any two adjacent words differ by just one symbol for binary, our symbols are 0 and 1.

To go from 1-bit => 2-bit

1. Reflect (Make exact copy of list above)
2. Prefix ("Prefix" first half of list with 0 and 1 to other half)

1-bit gray code

- 0
- 1

2-bit gray code

- 00
- 01
- 11
- 10

3-bit gray code

- 000
- 001
- 011
- 010
- 110
- 111
- 101
- 100

1. n-bit binary gray code is a permutation of [0,2^n-1], with each number appearing once in the gray code list.
2. The n-1 bit gray code is embedded in the top half of the n-bit gray code list

### Karnaugh Maps or K-Maps

Graphical technique to view min-terms and how they relate

- The map is a diagram made up of square, with each square representing a single min-term
- More 1's simpler the expression becomes
- If a 1 exists in more than one cell, you need to see if the other adjacent cells contain contradictory switches, and nullify them out.
- If no adjacent cell with a 1 exists, the expression cannot be simplified

```
  `B  B
`A 0  1
 A 0  1

`AB + AB
```

\`AB + A\`B : no common row or column does not simplify

#### 3-Variable Karnaugh Map:

```
  00  01  11  10    <- gray binary
0
1
```

#### 4-Variable Karnaugh Map:

- Will be on final

```
              | C |
        00 01 11 10
    00
    01             - B
A - 11             -
  - 10
        | D |
```

- Truth Table > Sum of Product Expression > Karnaugh Map > Simplified Expression > Circuit Design

Groups can only contain in 1,2,4, or 8 number ones

Split 5-Variable Karnaugh Map into two 4-Variable maps, making 5-Variable map, 3-dimensional

## August 6th, 2018

### Digital Logic II

Combinational circuit:

- Given same inputs, you will always get same outputs.

Sequential Circuit:

- Stores information
- Output depends on stored information (sate) plus input
- Example: ticket counter

#### R,S Latch NAND Gates:

Outputs from NAND gates are inputs to other NAND gates in the circuit (Memory Circuit)

- Must enter R and S together

- Set R = 0, S = 1 -> Set Qa = 1, Qb = 0
- Set R = 1, S = 0 -> Set Qa = 0, Qb = 1
- After changing input R to 1:
- Set R = 1, S = 1 -> Qa = 1, Qb = 0 (State doesn't change)
- After changing input S to 1:
- Set R = 1, S = 1 -> Qa = 0, Qb = 1 (State doesn't change)
- \*\* Can't start with 1 \& 1 or 0 \& 0
- If I set R = 0 and S = 0, later attempts to set R=1 and S = 1 changes output state. Not a memory circuit anymore

#### R,S Latch NOR Gates:

Sets or resets state of circuit no matter what:

- Set R = 0, S = 1 -> Set Qa = 1, Qb = 0
- Set R = 1, S = 0 -> Set Qa = 0, Qb = 1

Preserves state:

- Set R = 0, S = 0 -> Output state depends on previous state.

Undefined:

- R = 1, S = 1 -> Undefined

### Memory

Main memory is a linear array of bytes that can be accessed given a memory address.

#### Random Access Memory:

Key features:

- RAM is packaged as a chip
- Basic storage unit is a cell (one bit per cell)

Static RAM (SRAM):

- Each cell stores bit with a six-transistor circuit
- Retain value indefinetly as long as it is kept powered
- Relatively insensitive to distrubances such as electrical noise
- Faster and more expensive than DRAM

Dynamic RAM (DRAM):

- Each cell stores bit with a capacitor and transistor
- Value must be refreshed every 10-100 ms
- Sensitive to disturbances
- Slower and cheaper than SRAM

#### Memory Hierarchy:

- L0: Registers
- L1: On-chip cache
- L2: Off-chip cache
- L3: Main memory (DRAM)
- L4: Local secondary storage (Local Disks)
- L5: Remove Secondary Storage (Distributed File Systems, Web Servers)

Higher on Hierarchy:
Decreasing capacity, Higher per-bit cost, Faster Access

Lower on Hierarchy:
Increasing Capacity, Lower per-bit cost, Slower Access

#### Locality:

Memory references are bunched together

- A small portion of address space is accessed at any given time

Cache this portion of the address space in faster memories

The Case for Locality:

1. Auto variables in stack frames repeated access to most recently created stack frame
2. Loops in functions access same variables
3. Loops in functions access same machine instructions
4. Array element and struct member access

**Temporal Locality**:

- Recently accessed locations will likely be accessed again in the near future

```c
// Temporal Locality
int i;
for (i = 0; i < 200; i++) {
    // Use i in loop
}
// i is used very often
```

**Spacial Locality**:

- Will likely accessed locations close to the ones recently accessed in the near future

```C
// Spacial Locality
int array2D[100][100];
int i, j;
for (i = 0; i < 100; i++) {
    for (j = 0; j < i; j++) {
        array2D[i][j] = i + j;
    }
}
// A0, A1, A2, ... An
// Laid out next to eachother in memory
```

C, Java, C++ : Arrays are row-major order.

Fortran : Arrays are column-major order. (Designed by the misguided)

#### Static RAM:

RAM using latching circuitry. Note that latches are **_bistable circuits_** with two stable states. There may be other hardware states, but the bistable device will move toward one of the two stable states, and having reached a stable state, will remain in that state until externally altered.

SRAM cell (bit) will retain its value indefinitely without refresh as long as power is on. SRAM is used for cache memories.

SRAM:

- Faster than DRAM
- Structurally more complex than DRAM
- Does not need periodic refresh
- More expensive per unit storage than DRAM

#### Dynamic RAM:

- **_Cell_** is the memory term for bit.
- **_Supercell_** is the bits in a machine word.
- **_Word_** is the amount transferred to and from memory.
- **_WordSize_** is the number of bits transferred

DRAM Organization:

**_Notation_** : d x w

- d : number of words on a chip
- w : word size in bits

**_word_** is also called **_supercell_**.
**_Supercells_** are arranged in 2-dimensional arrays with R rows, C columns. Product : r \* c = d

Access requires **_Row Access Strobe_** and **_Column Access Strobe_**.

Memory is accessed as 2D array requiring separate row-access strobe to locate the proper row, then a separate column-access strobe to locate the desired supercell (word) in the selected row.

- What are the pros and cons of this 2D arrangement?
  - Pro:
    - 2D array reduces number of pins on DRAM chip (cheap)
  - Con:
    - Memory access is done in two steps (RAS then CAS), which increases access time

Each data bit is stored in a spearate (small) capacitor
in the memory chip. The capacitor is either charged (1) or discharged (0).

Capacitors gradually lose charge over time, so capacitor must be periodically refreshed to prevent loss of data. The capacitor refresh requirement is what makes DRAM dynamic. 64 milliseconds is the typical refresh interval.

DRAM:

- The architectural difference between the two is that DRAM uses transistors and capacitors in an array of repeating circuits (where each circuit is one bit), whereas SRAM uses several transistors in a circuit to form one bit.
- DRAM has a controller, handles refresh, the added complexity does not change the netgain of space efficiency

#### Realistic Example:

64 megabyte memory module uses 64-megabit DRAM chips, each chip (8 meg \* 8) each chip is numbered [0 - 7] for 64-bit access. Word/Supercell size is 8-bits. Two dimensional array in each DRAM chip is (4096 x 2048) (r,c). Not quite square, but as square as possible to minimize number of access pins on this chip. (12 in this case 2^12 = 4096).

To access main memory, memory controller translates linear main memory address into row ( i ) and column ( j ). i and j are sent to memory module which accesses the same cell on each chip. Circuitry in memory module aggregates or distributes the bytes into 64-bit transfers to/from memory module.

Adjacent bytes of main memory are actually stored in seperate DRAM chips

#### SIMM \& DIMM:

Single Incline Memory Module:

- Memory chips with 72 pins, 32-bit memory transfers. Originally used in 32-bit machines. Used in pairs on 64-bit machines to get 64-bit transfers

Dual Inclince Memory Module:

- Memory chips with 168 pins for 64-bit memory transfers, replaced paired SIMMS in 64-bit machines

## August 8th, 2018

### Caching

#### Motivation:

CPU and memory access speeds are increasing.

The CPU is speeding up much faster than memory and is creating a gap between itself and memory access speed.

#### Terminology:

Cache - is a small fast storage device used to hold a subset of data from a larger slower storage device

Cache Block - thick sized, chunks of data that goes between the cache and main memory.

Cache Lines - meta information about the blocks in the cache

Set - a collection of one or more lines in the cache

Cache Capacity - total number of blocks it can hold

Placement Policy - dictates where cache places the meta information, the blocks, etc.

Hit - when desired block is already in the cache

Cold Miss (Compulsory Miss) - the first reference to a block of memory, starting with an empty cache.

Conflict Miss - two blocks are mapped to the same location and there is not enough room to hold both.

Capacity Miss - the cache is not big enough to hold every block you want to use.

#### General Organization of Cache Memories:

Main memory address of m-bits

```
      t             s                  b
+------------------------------------------------+
| Tag Bits | Set Selector Bits | Offset in Block |
+------------------------------------------------+
MSB                                            LSB
```

- t + s + b = m

Implications:

- Block size is 2^b
- Number of sets is 2^s
- Tag bits uniquely identify the block

Block Size: 4096

- Offset in Block: 0 - 4096

Cache Capacity

- C = 2^s _ E _ 2^b
- 2^s = number of sets
- E = number of lines per set
- 2^b = block size in bytes

Direct - Mapped Cache

- Each set has just one line
- Multiple sets, one line per set
- Search cache by extracting selector bits from input address.
- Identical selector bits from any address always map to same line
- Thrashing : when cache constantly rewrites same block of memory instead of utilizing other blocks, occurs because of selector bits.
- Direct caches are larger and more expensivve

Meta-Information

- Valid Bit - is this line in use? initial value 0 => no.
- Tag Bits - to identify the block
- Dirty Bit - has the block been written to

Design #1

- Meta-memory is seperate from the cache.

```
Meta Information:
+---+
|   |
+---+

Block Buffer:
+-------+
|       |
+-------+
|       |
+-------+
|       |
+-------+
```

Design #2

- Line selection is determined by selector bits.
- Line selection is direct mapping from selector bits.
- Direct mapping is fast
- Can thrash if multiple blocks have same selector bits even when other cache blocks are not used

```
+----------+
| Meta Info|
|  Data0   |
+----------+
| Meta Info|
|  Data1   |
+----------+
| Meta Info|
|  Data2   |
+----------+
| Meta Info|
|  Data3   |
+----------+
```

For any memory address x, block address is:

- y = x \& ~((2^b) - 1)
- 4096 = 100000000000 Binary
- 4095 = 0111111111111
- ~4095 = 11111 ... 111000000000000

In any m-bit number, any representable power of 2 is represented as a single 1 bit with all other m-1 bits equal to 0.
2, 4, 8, 16 ...

- Power of 2
- Power of 2 minus 1
- Flip bits

#### Bitfields:

Bitfields don't have addresses:

- bitfields members are (typically) smaller than the granularity allowed by pointers
- to store/retrieve such a member the compiler must know exactly where it is located in the bitfield (and no "regular" pointer type can carry such information).

Bitfields allow access to bits or groups of bits

- Specify them as struct members

```C
struct example {
    unsigned int f1 : 10;
    unsigned int f2 :  3;
    unsigned int    :  4;
    unsigned int f3 :  7;
    unsigned int f4 :  0;
}


typedef union {
    int Number;
    struct {
        char b1;
        char b2;
        char b3;
        char b4;
    } bits;
} bitSplitter


typedef union{
  struct{
    unsigned int partTwo : 4;
    unsigned int partOne : 4;
  } nibb;
  char byteChar;
} byte;
```

#### Set Associative Cache:

- multiple sets
- each set contains multiple lines
- any line in a set can hold any block in the set
- searching for block within a set is done in parallel

```
One set, four lines
+-----+
| TAG |
+-----+
| TAG |
+-----+
| TAG |
+-----+
| TAG |
+-----+
```

Selector bits say what set, but not what line in the set, must use meta-information, if it doesn't provide, must use their block replacement policy

- Block Placement Policy
- Block Replacement Policy
  - select **_victim_** to **_evict_** to make room for a new block. which block to select?
    - random selection
    - least recently used
    - least frequently used

### Fully-Associative Cache

- only one set
- all lines in same set
- no selector bits because there is only one set
- memory address broken into tag bits, block offset bits.
- search by tag, parallel or linear
- likely to thrash
- are small

|         Type          | Number of Sets | Number of Lines Per Set | Blocksize |
| :-------------------: | :------------: | :---------------------: | :-------: |
|     Direct-mapped     |      2^s       |            1            |    2^b    |
| N-way set associative |      2^s       |            N            |    2^b    |
|   Fully Associative   |       1        |            E            |    2^b    |

In review he says that direct-mapped has 2^s lines in cache, S slector bits from middle of input address

s^b is blocksize, offset in block is [0,2^b-1]

### Factors in Cache Design

C = 2^s _ E _ 2^b

- with same number of selector bits and same block size, an n-way set associative cache is n-times as large as a direct-mapped cache

Size

- Cache size
- Block size
  - small blocks conflict with locality
- Block Replacement Algorithm
- Write Policy

#### Block Replacement Algorithms:

Given a set of blocks in a cache, which block should be selected for eviction to make space for a new block?

- Option #1 - Random Selection
- Option #2 - Least Recently Used
  - LRU Implementation Ideas
    - Each block has an associated counter as part of block meta-information
    - There is a single universal counter
    - All counters initially set to 0
    - Every memory access increments universal counter
    - counter for each accessed block set equal to universal counter
    - need to evict? evict block with lowest counter value
  - Beating Overflow: Red-Blue infinite squencing
    - Unsigned fixed-point counter has a "color" red or blue.
    - Start with Blue 0
    - Increment blue counter as needed
    - On overflow, counter becomes red
    - Increament red couter as needed
    - On overflow, counter becomes blue
  - Comparision rules:
    - Small blue value < Large blue value
    - Small red value < Large red value
    - Large blue value < Small red value
    - Large red value < Small blue value
- Option #3 - Least Frequently Used
  - Each block get a frequency counter, initial value 0
  - Every access to a block, increments its counter
  - Need to evict? Select block with lowest counter. Read in new block, reset frequency counter to 0.
  - Do you see the problem here?

### Cache Write Policies

Write-Through : all data writes sent immediately to main memory.

- Pros:
  - Simple to implement (Does anyone care?)
  - Data in memory and cache always consistent
  - Good if reads greatly outnumber writes
- Cons:
  - Caching advantage lost if lots of writes to memory

Write-Back : writes to cache are copied to memory when block is evicted. Blocks with changed contents are copied only if dirty bit is set. Unchanged blocks are considered clean and can be safely overwritten without copying.

- Pros:
  - Fast than write-through (Fewer writes to main memory)
- Cons:
  - More complicated (Does anyone care?)

What if process (CPU) wants to write to an address that is not in the cache?

- Write-Allocate: Load missed block into cache and write to block in cache.
  - Pros:
    - Good use of spatial locality
  - Cons:
    - Every missed write causes block loaded into cache
- No-Write-Allocated : Missed writes go directly to memory, leaving cache unchanged.
  - Pros
    - No cache modification overhead
  - Cons
    - Show access write to memory

### Memory Hierarchy

Faster, Smaller, More Expensive, Closer to ALU

- registers
  - L1 cache SRAM
  - L2 cahce SRAM
- main memory DRAM
- local hard disk

Slower, Larger, Cheaper, Further from ALU

- Higher levels more likely to use write-through because of smaller block sizes
- Lower levels more likely to use write-back because of larger block sizes

#### Program for the cache by:

- Access data sequantially
- Reuse variables instead of creating new ones

#### Take-Aways:

- Spacial and Temporal Locality
- Economics of Cache
- Direct Map Cache
- Associative Cache
- Fully Associative Cache
- Parallel Search
- Writing to Cache
- LRU

## August 13th, 2018

- Last Lecture

### Parallel Processing

Multiple processors (CPUs) sharing common memory.

- SISD single instruction stream, singled data stream
- SIMD single instruction stream, multiple data streams
  - one instruction acts on multiple scalar values
  - vector machine
  - example: graphical proccessing units (GPUs) intel architecture supports a set of vector instructions
- MISD multple instruction stream, single data stream
  - fault-tolerant system where multiple processors operate on same data, compare results to ensure that no processor is malfunctioning
- MIMD multple instruction stream, multiple data stream
  - broadly defined: all forms of computers with multiple processors, each processor with its own programs to run.

If one processor writes to a common memory, other processors can read from the common memory. Processors in a multiprocessor communicate through a common memory.

How are the processors connected?

1. A bus, all processors communicated with the common memory through a bus.

```
+-----+ +-----+ +-----+
| CPU | | CPU | | CPU |
+-----+ +-----+ +-----+
    |       |       |
    -----------------
            |
        +--------+
        | MEMORY |
        +--------+
```

- Bottleneck: only one bus. Multiple CPUs cannot access common memory at the same time, even when accessing nonoverlapping areas of memory

Symmetric multiprocessor (SMP)

- multiple processors share common memory SMP achitecture is characterized by uniform memory access (UMA) where any processor can access any part of memory with the same latency

```
+-------+ +-------+ +-------+
|  CPU  | |  CPU  | |  CPU  |
| CACHE | | CACHE | | CACHE |
+-------+ +-------+ +-------+
    |         |         |
    ---------------------
              |
          +--------+
          | MEMORY |
          +--------+
```

Cache for each CPU reduces contention for bus but introduces **_cache coherence_** problem where on CPU changes data that is mirrored in another cache.

- One CPU changed the data but the others don't know since their cache hasn't updated

Solutions to cache coherence problem:

1. Write through cache: Any CPU write is copied to common memory. This is not enough to ensure coherence
2. Other CPUs and their cache need to know about memory change that might affect their caches. Snoopy caches can monitor memory changes through the common bus and update their local cache contents as needed

A **_switch_** is an electronic component that can break a circuit or redirect current to different destinations.

An **_M x N crossbar_** is a switching mechanism that allows any of **_M_** elements to be switched to any of **_N_** elements.

Different CPUs can access different parts of the common memory in parallel, the only constraint, no two CPUs can talk to the same memory segment at the same time.

```
        +--------+ +--------+ +--------+
        | MEMORY | | MEMORY | | MEMORY |
        +--------+ +--------+ +--------+
+-----+     |          |           |
| CPU | ----+----------+-----------+
+-----+     |          |           |
+-----+     |          |           |
| CPU | ----+----------+-----------+
+-----+     |          |           |
+-----+     |          |           |
| CPU | ----+----------+-----------+
+-----+
```

Switch Logic

1. For each input there is at most one output
2. There may be mutple inputs per switch
3. No two inputs can use the same output at the same time
4. A switch can provide separate outputs for separate inputs

### Avoiding Memory Access Delays in Multiprocessors (NUMA)

Non-uniform memory acess (NUMA) (Most Common)

- Each CPU has its own memory segment that it can access quickly.
- Any CPU can access any other memory segment only more slowly. All memory is shared, among all CPUs. NUMA provides faster memory access as long as each processor tends to access its own local memory segment

### MIDTERM #1

1. Name Internal Components Of A CPU
2. Difference between Von Neumann and Harvard
3. How many numbers can k-bits represent? 2^k
4. Converting to and from Binary, Hex, Octal, Decimal
5.

```C
char *
FCN()
{
    char str[20];
    return str;
}
```

You return a pointer to an auto variable, and it gets freed when function returns

6. Negative, Positive infinity
7. Negative, Positive NaN
8. How much memory in each?

```C
struct one {
    // 48 bytes
    int x[6];
    int y[12];
}
union two {
    // 28 bytes
    int x[6];
    int y[12];
}
```

9. %RBP contains address of current (Topmost) stack frame
   - memory at (%RBP) holds %RBP for previous stack frame
   - we have a linked list of varaible-sized stack frames
   - stack grows from larger addresses toward smaller addresses
10. Convert assembly to C
11. Hex Speak
12. Implicit 1 in IEEE

### Proofs using truth tables

It is Possible to prove the equivalence of two logical expressions using truth tables

Caching, Full adder, cheat sheet, front and back, k-map, formula, totality/speciality, truth tables

Direct mapped c
