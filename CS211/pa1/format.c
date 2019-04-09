#include <stdio.h>
#include <string.h>

void intToDecASCII(int number, char * integ) {
	char * ip; // Integer Pointer
    int isNegative = 0;
	char digitArray[12] ={
    '0',
    '0',
    '0',
    '0',
    '0',
    '0',
    '0',
    '0',
    '0',
    '0',
    '0',
    '\0'
    };

	if (number < 0) {
		isNegative = 1;
		number = -number;
	}
    int x;
    for (x = 10;;x--) {
        digitArray[x] = (number % 10) + '0';
        number /= 10;
        if (number == 0) {
            break;
        }
    }
	if (isNegative) {
		x--;
		digitArray[x] = '-';
	}
	ip = integ;
    while (x < 12) {
        *ip = digitArray[x];
        x++;
        ip++;
    }
}

// input:  x is the 32-bit input.
// output:  digit is the output ASCII character
// output:  pow10 is the original pre-normalization power of 10.
// output: remainder is x after subtracting the high-digit value
static void get_float_digit(float x, char * digit, int * pow10, float * remainder) {
    int p10;

    if (x == 0.0) { * digit = '0'; // digit is always '0'
        * pow10 = 0; * remainder = 0.0;
    } else { * pow10 = 0; // start with 10^0
        while (x >= 10.0) // reduce
        {
            x /= 10.0; // large values get smaller
            * pow10 += 1;
        }
        while (x < 1.0) // increase
        {
            x *= 10.0; // small values get larger
            * pow10 -= 1;
        } * digit = '0';
        do { // 10.0 > x >= 1.0
            x -= 1.0; * digit += 1; // digit is always non-'0'zero
        } while (x >= 1.0);
        p10 = 0;
        while (p10 > * pow10) // leading digit is now removed from x
        {
            x /= 10;
            p10 -= 1;
        }
        while (p10 < * pow10) {
            x *= 10;
            p10 += 1;
        } * remainder = x;
    }
}

static void append(char * s, char c) {
    char buf[2];

    buf[0] = c;
    buf[1] = '\0';
    strcat(s, buf);
}

union Number {
    int i;
    float f;
};

void floatToASCII(float x, char * output) {
    char c;
    int pow10, p10, plast;
    int i;
    float remainder;
    char exponent[10];
    union Number a;
    unsigned int biasedExp;
    unsigned int mantissa;
    int sign;

    a.f = x;
    biasedExp = a.i >> 23 & 0x000000ff;
    mantissa = a.i & 0x007fffff;
    sign = a.i >> 31;
    // +/- inf, +/- Nan stuff here
    output[0] = '\0';
    if (x < 0.0) {
        append(output, '-');
        x = -x; // make x positive
    }
    get_float_digit(x, & c, & pow10, & remainder);
    append(output, c);
    append(output, '.');
    x = remainder;
    plast = p10 = pow10; // pow10 set by get_float_digit()
    for (i = 1; i < 7; i++) // 7 significant digits in 32-bit float
    {
        get_float_digit(x, & c, & p10, & remainder);
        if ((plast - p10) > 1) {
            append(output, '0'); // fill in zero to next nonzero digit
            plast -= 1;
        } else {
            append(output, c);
            x = remainder;
            plast = p10;
        }
    }
    if (pow10 < 0) // negative exponent
    {
        exponent[0] = 'e';
        printf("%s \n", exponent);
        intToDecASCII(pow10, exponent + 1);
    } else if (pow10 < 10) // positive single-digit exponent
    {
        exponent[0] = 'e';
        exponent[1] = '+';
        exponent[2] = '0';
        intToDecASCII(pow10, exponent + 3);
    } else // positive multi-digit exponent
    {
        exponent[0] = 'e';
        exponent[1] = '+';
        intToDecASCII(pow10, exponent + 2);
    }
    strcat(output, exponent);
}

/**
 * Checks for 0 or 1. Left bit-shifts the number over by 1.
 **/
int binaryToTwos(char * s) {
    int value = 0;
    int i = 0;
    while (s[i] != '\0') {
        switch (s[i]) {
        case '0':
            value = (value << 1);
            break;
        case '1':
            value = (value << 1) + 1;
            break;
        default:
            fprintf(stderr, "ERROR: Non-binary char found.\n");
            return 0;
        }
        i += 1;
    }
    return value;
}

int inputFormatted(char * binary, char * type) {
    int i = 0;
    while (binary[i] != '\0') {
        if (binary[i] != '0' && binary[i] != '1') {
            fprintf(stderr, "ERROR: First input is not a binary number.\n");
            return -1;
        }
        i += 1;
    }
    if (strcmp(type, "int") == 0) {
        return 0;
    } else if (strcmp(type, "float") == 0) {
        return 1;
    }
    fprintf(stderr, "ERROR: Type not found, please use 'float' or 'int'.\n");
    return -1;
}

int main(int argc, char * * argv) {
    if (argc != 3) {
        fprintf(stderr, "ERROR: You must enter two arguments.\n");
        return -1;
    }
    char * binary = argv[1];
    char * type = argv[2];
    if (strlen(binary) > 64) {
        fprintf(stderr, "ERROR: Too many bits in binary number.\n");
        return -1;
    }

    // 0 = int
    // 1 = float
    int typ = inputFormatted(binary, type);
    if (typ != 0 && typ != 1) {
        return -1;
    }

    union Number number;
    number.i = 10;

    while ( * binary != '\0') {
        number.i <<= 1;
        number.i += * binary - '0';
        binary += 1;
    }

    char answer[15];

    if (typ == 0) {
        intToDecASCII(number.i, answer);
    } else {
        floatToASCII(number.f, answer);
    }

    printf("%s\n", answer);
    return 0;
}