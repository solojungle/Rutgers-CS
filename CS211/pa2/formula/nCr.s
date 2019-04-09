.data
.strA:
        .string "Error: n < r\n"
.strB:
        .string "Error: n < zero\n"
.strC:
        .string "Error: r < zero\n"
.strD:
        .string "Error: fact(n) has overflowed\n"
.strE:
        .string "Error: fact(r) * fact(n - r) has overflowed\n"
.strF:
        .string "Error: Factorial has overflowed.\n"

.globl nCr
.type  nCr, @function
nCr:
    # Your code for nCr should go here
    # Setup
    pushq   %rbp
    movq    %rsp, %rbp
    subq    $16, %rsp
    movl    %edi, -4(%rbp)
    movl    %esi, -8(%rbp)
    # N < R
    movl    -4(%rbp), %eax
    cmpl    -8(%rbp), %eax
    jge     .L2
    # Print error
    movl    $.strA, %eax
    movq    %rax, %rdi
    movl    $0, %eax
    call    printf
    movl    $-1, %eax
    jmp     .L1
.L1:
    movq   %rbp, %rsp
    popq   %rbp
    ret
.L2:
    cmpl   $0, -4(%rbp)
    jl     .L3
    cmpl   $0, -8(%rbp)
    # I'm sure r can never be < 0, but whatever
    jl     .L4
    movl   -4(%rbp), %edi
    movl   $0, %eax
    call   Factorial
    cmpl   $-1, %eax
    je     .L1
    movl   %eax, -16(%rbp)
    jo     .L5
    # r! can't overflow and neither can (n - r)!
    movl   -8(%rbp), %edi
    movl   $0, %eax
    call   Factorial
    movl   %eax, -12(%rbp)
    movl   -4(%rbp), %eax
    subl   -8(%rbp), %eax
    movl   %eax, %edi
    movl   $0, %eax
    call   Factorial
    movl   %eax, -8(%rbp)
    # r! * (n-r)!
    movl   -8(%rbp), %eax
    imull  -12(%rbp), %eax
    movl   %eax, -4(%rbp)
    jo     .L6
    # n! / m!
    movl   -16(%rbp), %eax
    cltd
    idivl  -4(%rbp), %eax
    jmp .L1

.L3:
    movl   $.strB, %eax
    movq   %rax, %rdi
    movl   $0, %eax
    call   printf
    movl   $-1, %eax
    jmp    .L1
.L4:
    movl   $.strC, %eax
    movq   %rax, %rdi
    movl   $0, %eax
    call   printf
    movl   $-1, %eax
    jmp    .L1
.L5:
    movl   $.strD, %eax
    movq   %rax, %rdi
    movl   $0, %eax
    call   printf
    movl   $-1, %eax
    jmp    .L1
.L6:
    movl   $.strE, %eax
    movq   %rax, %rdi
    movl   $0, %eax
    call   printf
    movl   $-1, %eax
    jmp    .L1

.globl Factorial
.type   Factorial, @function
Factorial:
        # Your code for Factorial should go here
        # Setup
        pushq   %rbp
        movq    %rsp, %rbp
        movl    %edi, -20(%rbp)
        # Extra space was added
        movl    $1, -4(%rbp)
        movl    $2, -8(%rbp)
        jmp     .Factorial_end
.Factorial_overflow:
        movl   $.strF, %eax
        movq   %rax, %rdi
        movl   $0, %eax
        call   printf
        movl   $-1, %eax
        movq   %rbp, %rsp
        popq   %rbp
        ret
.Factorial_loop:
        movl    -4(%rbp), %eax
        imull   -8(%rbp), %eax
        # Fixes bug where Factorial would
        # overflow and would not tell nCr.
        jo      .Factorial_overflow
        movl    %eax, -4(%rbp)
        addl    $1, -8(%rbp)
.Factorial_end:
        # Start loop
        movl    -8(%rbp), %eax
        cmpl    -20(%rbp), %eax
        jle     .Factorial_loop
        movl    -4(%rbp), %eax
        popq    %rbp
        ret
