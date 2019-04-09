Discovery:
    After compiling the mystery.s inside an iLab machine, and entering numbers 1-10, the function
of the program was determined to return the Nth number of a Fibonacci sequence. It should be noted that
there is no error returned on improper input. After many compiles I've finally been able to reverse engineer
the source code from the executable. There are 3 functions, add, compute_fib and main. Compute_fib is
a recursive function, main is a driver, and add is a helper function. Since compute_fib is recursive
it has an upper limit of 64-bits since the function utilizes long versus int. My method for reversing
the assembly was as follows: read through the .s file and try to pick up as many clues as possible, the
only thing I could'nt pick up from the code alone was the structure of all of the if, elses within the
file. Through many compiles I finally figured out all of the necessary code snippets.

Optimization:
    First thing to notice is that the compiler moves the array declaration to the bottom.
Add was optimized to use the one-line LEAQ trick shown in class. Compute_fib has omited moving
the stack pointer to the base pointer on initial call. Subtracts from stack only when needed.
Compiler uses TEST instead of CMPQ\L. It also uses the lower bit pointers such as %AL where
applicable. Uses LEAQ extensively, dwindling down the lines needed too as few necessary.
