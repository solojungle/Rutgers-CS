Calc 32-bit:
* Overflow is not checked, buyer beware inputting two numbers that Overflow will result in undefined behavior.

Design
        Program takes in 4 inputs, operator, two numbers and an output base. The program sanitizes the inputs, and converts them to Two's Complement.
    Next it does either, addition, subtraction, or multiplication. Converts that sum (product) into a string and prints.
Challenges
        I had a lot of trouble understanding the concept of Two's Complement in the prompt, whether we were supposed to convert it and then print it
    out etc., I had programmed at least 1,500 lines total (remakes counted), creating this program. When it finally clicked I finished quite quickly.
Analysis
        The largest Big-O bottleneck in my program is the reverse function O(n^2), however is only uses n/2 of digits and is only used to reverse a 
    decimal string after it has been converted from an integer.


Format:

Design
        I created four functions, that work together to print out a IEEE 754 float. `inputFormatted` - sanitizes inputs, `binaryToTwos` - transforms
    binary string into Two's Complement, and `intToDecASCII` - exponent passes a pointer to an array of size 10, I created and populated an array of 12,
    saving 1 for null & 1 for '-'. Then I add numbers to the array, if number == 0 I stop prematurely to remove an extra 0. The function reclaims the negative,
    then copies to the parent array.
Challenges
        I had trouble "reverse engineering" the function that the professor had given, to create a function that would work with it. My orignal function in calc.c
    did not work correctly so I needed to remake a new Two's to Decimal Ascii.
Analysis
        My program will run in O(n).