Design and Implementation:
    When deciding how to build the formula program, I started first with the base function of factorial,
since it was the "simplest" to implement and made sense given I needed it for nCr.s and formula.c.
I went through a few iterations of factorial in C before deciding on one algorithm I liked. Instead of
including an overflow check in factorial I decided to instead check for overflows in nCr.s, so I wouldn't
have to hoist up the error. Printing a string in x86-64 gave me a lot of trouble, its hard looking for 
resources online when everything is machine specfific or conventions differ such as Linux's System V ABI.
    Without printing the error messages in nCr, I had to send multiple error calls to formula.c which gave
me little insight when I attempted to debug my program. When finally switched, I could send a single '-1' to
exit the program, while having the benefit of an exact error message being printed. I also happened to fix an
error in which Factorial() would not relay an overflow to nCr, I then added an jo call to fix, and returned -1
to fix such an issue.
    Formula.c was the quickest to debug and create, I spent maybe around 5 minutes completing it while the other
parts took me multiple days easily.

Big-O analysis:
    Since int's overflow quite easily with the algorithm given, it might have been worthwhile to just print
pre-calculated results: O(1). Instead I generate all results: O(n). It doesn't take more than a second to calculate
all results in real-time.
