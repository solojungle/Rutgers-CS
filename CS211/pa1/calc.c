#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

/**
 * No default function exists, made my own to test whether an int is binary or not.
 **/
int isbinary (int c) {
    if (c == '0' || c == '1') {
        return 1;
    }
  return 0;
}

/**
 * Created to be able to reverse the twosToDecimal function's output.
 **/
void reverse (char *s) {
    char temp;
    int i, j, length;
    length = strlen(s);
    for(i = 0; i < length - 1; i++){
        for(j = 0; j < length - 1 - i; j++){
            temp = s[j];
            s[j] = s[j + 1];
            s[j + 1] = temp;
        }
    }
    s[32] = '\0';
}

/**
 * Checks for 0 or 1. Left bit-shifts the number over by 1.
 **/
int binaryToTwos (char *s) {
    int value = 0;
    int i = 0;
    while (s[i] != '\0') {
        switch (s[i]) {
            case '0': value = (value << 1); break;
            case '1': value = (value << 1) + 1; break;
            default: fprintf(stderr, "ERROR: Non-binary char found.\n"); return 0;
        }
        i += 1;
    }
    return value;
}

/**
 * Uses base 10 to create an int number, subtracting '0' removes hex encoding (0x30) from ASCII -> [0x31,0x39].
 **/
int decimalToTwos (char *s) {
    int isNegative = 0;
    int i = 0;
    int value = 0;
    if (s[0] == '-') {
        isNegative = 1;
        i = 1;
    }
    while (s[i] != '\0') {
        value = (10 * value) + (s[i] - '0');
        i += 1;
    }
    if (isNegative) {
        return -value;
    }
    return value;
}

/**
 * Left bit-shifts by 3 (Number of bits octal uses).
 **/
int octalToTwos (char *s) {
    int value = 0;
    int i = 0;
    while (s[i] != '\0') {
        switch (s[i]) {
            case '0': value = value << 3; break;
            case '1': value = (value << 3) + 1; break;
            case '2': value = (value << 3) + 2; break;
            case '3': value = (value << 3) + 3; break;
            case '4': value = (value << 3) + 4; break;
            case '5': value = (value << 3) + 5; break;
            case '6': value = (value << 3) + 6; break;
            case '7': value = (value << 3) + 7; break;
            case '8': value = (value << 3) + 8; break;
            default: fprintf(stderr, "ERROR: Non-octal char found.\n"); return 0;
        }
        i += 1;
    }
    return value;
}

/**
 * Left bit-shifts by 4 (Number of bits hex uses).
 **/
int hexToTwos (char *s) {
    int value = 0;
    int i = 0;
    while (s[i] != '\0') {
        switch (s[i]) {
            case '0': value = (value << 4); break;
            case '1': value = (value << 4) + 1; break;
            case '2': value = (value << 4) + 2; break;
            case '3': value = (value << 4) + 3; break;
            case '4': value = (value << 4) + 4; break;
            case '5': value = (value << 4) + 5; break;
            case '6': value = (value << 4) + 6; break;
            case '7': value = (value << 4) + 7; break;
            case '8': value = (value << 4) + 8; break;
            case '9': value = (value << 4) + 9; break;
            case 'a': case 'A': value = (value << 4) + 10; break;
            case 'b': case 'B': value = (value << 4) + 11; break;
            case 'c': case 'C': value = (value << 4) + 12; break;
            case 'd': case 'D': value = (value << 4) + 13; break;
            case 'e': case 'E': value = (value << 4) + 14; break;
            case 'f': case 'F': value = (value << 4) + 15; break;
            default: fprintf(stderr, "ERROR: Non-hex char found.\n"); return 0;
        }
        i += 1;
    }
    return value;
}

/**
 * Uses bitwise `&` operator to capture bits.
 **/
void twosToBinary (int number, char *s) {
    s[32] = '\0';
    for (int i = 31; i >= 0; i--) {
        int x = number & 0x00000001;
        if (x == 0) {
            s[i] = '0';
        } else {
            s[i] = '1';
        }
        number >>= 1;
    }
}

/**
 * Divides by base 10, saves char in array.
 **/
void twosToDecimal (int number, char *s) {
    int isNegative = 0;
    int x, i = 0;

    // Ints can't represent positive 2147483648 so mulitplying by -1 does nothing.
    if (number == -2147483648) {
        s = "-2147483648";
        exit(0);
    }
    if (number < 0) {
        isNegative = 1;
        number = -number;
    }
    while (number > 0) {
        x = (number % 10);
        s[i] = (x + '0');
        number /= 10;
        i += 1;
    }
    if (isNegative) {
        s[i] = '-';
    }
    reverse(s);
}

/**
 * Uses bitwise `&` operator to capture bits, shifts int right (divides by (2^3) -> 8).
 **/
void twosToOctal (int number, char *s) {
    s[32] = '\0';
    for (int i = 31; i >= 0; i--) {
        int x = number & 0x00000007;
        switch (x) {
            case 0: s[i] = '0'; break;
            case 1: s[i] = '1'; break;
            case 2: s[i] = '2'; break;
            case 3: s[i] = '3'; break;
            case 4: s[i] = '4'; break;
            case 5: s[i] = '5'; break;
            case 6: s[i] = '6'; break;
            case 7: s[i] = '7'; break;
        }
        number >>=3;
    }
}

/**
 * Uses bitwise `&` operator to capture bits, shifts int right (divides by (2^4) -> 16).
 **/
void twosToHex (int number, char *s) {
    s[32] = '\0';
    for (int i = 31; i >= 0; i--) {
        int x = number & 0x0000000F;
        switch (x) {
            case 0: s[i] = '0'; break;
            case 1: s[i] = '1'; break;
            case 2: s[i] = '2'; break;
            case 3: s[i] = '3'; break;
            case 4: s[i] = '4'; break;
            case 5: s[i] = '5'; break;
            case 6: s[i] = '6'; break;
            case 7: s[i] = '7'; break;
            case 8: s[i] = '8'; break;
            case 9: s[i] = '9'; break;
            case 10: s[i] = 'A'; break;
            case 11: s[i] = 'B'; break;
            case 12: s[i] = 'C'; break;
            case 13: s[i] = 'D'; break;
            case 14: s[i] = 'E'; break;
            case 15: s[i] = 'F'; break;
        }
        number >>= 4;
    }
}

/**
 * Creating a function this way allows me to check both numbers without duplicate functions.
 **/
int numFormatted (int n, char **argv) {
    char type = argv[n][0];
    int length = strlen(argv[n]);
    int isNegative = 0;
    char *number;
    
    if (length < 2 || (type == '-' && length < 3)) {
        fprintf(stderr, "ERROR: Input %d, isn't long enough.\n", n);    
        return 0;
    }
    if (type == '-') {
        isNegative = 1;
        type = argv[n][1];
    }
    if (isNegative && type != 'd') {
        fprintf(stderr, "ERROR: Only decimal numbers may have a '-' as first character.\n");
        return 0;
    }
    if (!(type == 'b' || type == 'o' || type == 'd' || type == 'x')) {
        fprintf(stderr, "ERROR: Input %d, needs to have 'b', 'o', 'd', 'x', or '-' as the first character.\n", n);
        return 0;
    }
    if (isNegative) {
        number = &argv[n][2];
        length = strlen(number);
    } else {
        number = &argv[n][1];
        length = strlen(number);
    }
    switch (type) {
        case 'b':
            for (int i = 0; i < length; i++) {
                if (!isbinary(number[i])) {
                    fprintf(stderr, "ERROR: Input %d, is not a binary number.\n", n);
                    return 0;
                }
            }
            break;
        case 'o':
            for (int i = 0; i < length; i++) {
                if (!(isdigit(number[i]) || number[i] == '9')) {
                    fprintf(stderr, "ERROR: Input %d, is not a octal number.\n", n);    
                    return 0;
                }
            }
            break;
        case 'd':
            for (int i = 0; i < length; i++) {
                if (!isdigit(number[i])) {
                    fprintf(stderr, "ERROR: Input %d, is not a decimal number.\n", n);    
                    return 0;
                }
            }
            break;
        default:
            for (int i = 0; i < length; i++) {
                if (!isxdigit(number[i])) {
                    fprintf(stderr, "ERROR: Input %d, is not a hexadecimal number.\n", n);    
                    return 0;
                }
            }
            break;
    }
    return 1;
}

/**
 * Abstraced switch statement so no duplicate functions needed.
 **/
int convert (char *s) {
    char *number;
    char type = s[0];
    if (type == '-') {
        type = s[1];
        number = &s[1];
        number[0] = '-';
    } else {
        number = &s[1];
    }
    switch (type) {
        case 'b': return binaryToTwos(number);break;
        case 'o': return octalToTwos(number);break;
        case 'd': return decimalToTwos(number);break;
        case 'x': return hexToTwos(number);break;
    }
    return 0;
}

int main (int argc, char **argv) {

    if (argc != 5) {
        fprintf(stderr, "ERROR: You must enter four arguments.\n");
        return -1;
    }

    char op = argv[1][0];
    char base = argv[4][0];

    if (!(op == '+' || op == '-' || op == '*')) {
        fprintf(stderr, "ERROR: Operator not found.\n");
        return -1;
    }
    if (!(base == 'b' || base == 'o' || base == 'd' || base == 'x')) {
        fprintf(stderr, "ERROR: Output base not found.\n");    
        return -1;
    }

    if (!numFormatted(2, argv)) { return -1; }
    if (!numFormatted(3, argv)) { return -1; }

    int num1 = convert(argv[2]);
    int num2 = convert(argv[3]);
    printf("Number One: %d\n", num1);
    printf("Number Two: %d\n", num2);
    int sum;

    switch (op) {
        case '+': sum = num1 + num2;break;
        case '-': sum = num1 - num2;break;
        case '*': sum = num1 * num2;break;
    }

    printf("Decimal Answer (%c): %d\n", op, sum);

    char s[33];

    switch (base) {
        case 'b': twosToBinary(sum, s);break;
        case 'o': twosToOctal(sum, s);break;
        case 'd': twosToDecimal(sum, s);break;
        case 'x': twosToHex(sum, s);break;
    }

    printf("Outputted Answer (%c): %s\n", base, s);

return 0;
}