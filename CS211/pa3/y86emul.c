#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum { false, true } bool;

typedef struct CF {
    unsigned int IP;
    int OF;
    int ZF;
    int SF;
} Flags;
Flags CF = {0,0,0,0};

typedef union {
  char bytPart;
  struct {
    unsigned int highBits : 4;
    unsigned int lowBits : 4;
  } bytChars;
} bytUnion;

typedef union {
  int intPart;
  struct {
    char b1;
    char b2;
    char b3;
    char b4;
  } intChars;
} intUnion;

bytUnion * memory; // Global Memory Array.
int reg[8]; // Global Registry.

void increment(int n) {
  CF.IP += n;
}

void nop() {
  increment(1);
}

void rrmovl() {
  increment(1);
  // printf("rrmovl(%d, %d, problem: %d)\n", reg[memory[CF.IP].bytChars.highBits], reg[memory[CF.IP].bytChars.lowBits], memory[CF.IP].bytChars.lowBits);
  reg[memory[CF.IP].bytChars.highBits] = reg[memory[CF.IP].bytChars.lowBits];
  increment(1);
}

void irmovl() {
  increment(1);
  unsigned int rB = memory[CF.IP].bytChars.highBits;
  intUnion temp;
  increment(1);
  temp.intChars.b1 = memory[CF.IP].bytPart;
  increment(1);
  temp.intChars.b2 = memory[CF.IP].bytPart;
  increment(1);
  temp.intChars.b3 = memory[CF.IP].bytPart;
  increment(1);
  temp.intChars.b4 = memory[CF.IP].bytPart;
  // printf("irmovl(%d, %d)\n", reg[rB], temp.intPart);
  reg[rB] = temp.intPart;
  increment(1);
}

void op1() {
  int oper = memory[CF.IP].bytChars.highBits;
  int result;
  increment(1);
  int rA = reg[memory[CF.IP].bytChars.lowBits];
  int rB = reg[memory[CF.IP].bytChars.highBits];
  // printf("OP1: %d\n", oper);
  switch(oper)
  { 
    case 0:
      result = rA + rB;
      ((rA > 0 && rB > 0 && result < 0) || (rA < 0 && rB < 0 && result > 0)) ? (CF.OF = 1) : (CF.OF = 0);
      (result == 0) ? (CF.ZF = 1) : (CF.ZF = 0);
      (result < 0) ? (CF.SF = 1) : (CF.SF = 0);
      reg[memory[CF.IP].bytChars.highBits] = rB + rA;
      break;
    case 1:
      result = rA - rB;
      ((rA < 0 && rB > 0 && result > 0) || (rA > 0 && rB < 0 && result < 0)) ? (CF.OF = 1) : (CF.OF = 0);
      reg[memory[CF.IP].bytChars.highBits] = rB - rA;
      result = reg[memory[CF.IP].bytChars.highBits];
      (result == 0) ? (CF.ZF = 1) : (CF.ZF = 0);
      (result < 0) ? (CF.SF = 1) : (CF.SF = 0);
      break;
    case 2:
      result = reg[memory[CF.IP].bytChars.lowBits] & reg[memory[CF.IP].bytChars.highBits];
      CF.OF = 0;
      (result == 0) ? (CF.ZF = 1) : (CF.ZF = 0);
      (result < 0) ? (CF.SF = 1) : (CF.SF = 0);
      break;
    case 4: // mull
      result = rA * rB;
      ((rA > 0 && rB > 0 && result < 0) || (rA < 0 && rB < 0 && result < 0) || (rA > 0 && rB < 0 && result > 0) || (rA < 0 && rB > 0 && result > 0)) ? (CF.OF = 1) : (CF.OF = 0);
      (result == 0) ? (CF.ZF = 1) : (CF.ZF = 0);
      (result < 0) ? (CF.SF = 1) : (CF.SF = 0);
      reg[memory[CF.IP].bytChars.highBits] = result;
      break;
    case 5:
      CF.OF = 0;
      result = rB - rA;
      (result == 0) ? (CF.ZF = 1) : (CF.ZF = 0);
      (result < 0) ? (CF.SF = 1) : (CF.SF = 0);
      break;
  }
  increment(1);
}

void jmp() {
  intUnion temp;
  temp.intChars.b1 = memory[CF.IP].bytPart;
  increment(1);
  temp.intChars.b2 = memory[CF.IP].bytPart;
  increment(1);
  temp.intChars.b3 = memory[CF.IP].bytPart;
  increment(1);
  temp.intChars.b4 = memory[CF.IP].bytPart;
  // int pre = CF.IP;
  CF.IP = temp.intPart;
  // printf("JMP: %d, %d\n", pre, CF.IP);
}

void jump() {
  int oper = memory[CF.IP].bytChars.highBits;
  // printf("JO: %d\n", oper);
  increment(1);
  switch (oper) {
      case 0: jmp(); break;
      case 3: (CF.ZF == 1) ? (jmp()) : (increment(4)); break;
      case 4: (CF.ZF == 0) ? (jmp()) : (increment(4)); break;
  }
}

void write() {
  int oper = memory[CF.IP].bytChars.highBits;
  increment(1);
  int rA = reg[memory[CF.IP].bytChars.lowBits];
  intUnion temp;
  increment(1);
  temp.intChars.b1 = memory[CF.IP].bytPart;
  increment(1);
  temp.intChars.b2 = memory[CF.IP].bytPart;
  increment(1);
  temp.intChars.b3 = memory[CF.IP].bytPart;
  increment(1);
  temp.intChars.b4 = memory[CF.IP].bytPart;
  increment(1);
  rA += temp.intPart;
  (oper == 0) ? (printf("%c", memory[rA].bytPart)) : ({
    temp.intChars.b4 = memory[rA + 3].bytPart;
    temp.intChars.b3 = memory[rA + 2].bytPart;
    temp.intChars.b2 = memory[rA + 1].bytPart;
    temp.intChars.b1 = memory[rA + 0].bytPart;
    printf("%d", temp.intPart);
  });
}

void read() {
  int oper = memory[CF.IP].bytChars.highBits;
  increment(1);
  int rA = reg[memory[CF.IP].bytChars.lowBits];
  intUnion temp;
  increment(1);
  temp.intChars.b1 = memory[CF.IP].bytPart;
  increment(1);
  temp.intChars.b2 = memory[CF.IP].bytPart;
  increment(1);
  temp.intChars.b3 = memory[CF.IP].bytPart;
  increment(1);
  temp.intChars.b4 = memory[CF.IP].bytPart;
  increment(1);
  rA += temp.intPart;
   (oper == 0) ? ({
    memory[rA].bytPart = getchar();
    (memory[rA].bytPart == -1) ? (CF.ZF = 1) : (CF.ZF = 0);
  }) : ({
    (EOF == scanf("%d", &temp.intPart)) ? (CF.ZF = 1) : (CF.ZF = 0);
    memory[rA + 3].bytPart = temp.intChars.b4;
    memory[rA + 2].bytPart = temp.intChars.b3;
    memory[rA + 1].bytPart = temp.intChars.b2;
    memory[rA + 0].bytPart = temp.intChars.b1;
  });
}

void movsbl() {
  increment(1);
  int rA = memory[CF.IP].bytChars.lowBits;
  int rV = reg[memory[CF.IP].bytChars.highBits];
  intUnion temp;
  increment(1);
  temp.intChars.b1 = memory[CF.IP].bytPart;
  increment(1);
  temp.intChars.b2 = memory[CF.IP].bytPart;
  increment(1);
  temp.intChars.b3 = memory[CF.IP].bytPart;
  increment(1);
  temp.intChars.b4 = memory[CF.IP].bytPart;
  increment(1);
  rV += temp.intPart;

  //Check MSB for 1000 bit-pattern
  (memory[rV].bytChars.lowBits >= 8) ? ({
    // Max out bits then return old value
    temp.intPart = -1;
    temp.intChars.b1 = memory[rV].bytPart;
  }) : ({
    // Max out bits then return old value
    temp.intPart = 0;
    temp.intChars.b1 = memory[rV].bytPart;
  });
  // printf("movsbl(%d, %d)\n", reg[rA], temp.intPart);
  reg[rA] = temp.intPart;
}

void mrmovl() {
  increment(1);
  unsigned int rA = memory[CF.IP].bytChars.lowBits;
  unsigned int rB = memory[CF.IP].bytChars.highBits;
  intUnion temp;
  increment(1);
  temp.intChars.b1 = memory[CF.IP].bytPart;
  increment(1);
  temp.intChars.b2 = memory[CF.IP].bytPart;
  increment(1);
  temp.intChars.b3 = memory[CF.IP].bytPart;
  increment(1);
  temp.intChars.b4 = memory[CF.IP].bytPart;
  temp.intPart += reg[rB];
  intUnion dest;
  dest.intChars.b1 = memory[temp.intPart + 0].bytPart;
  dest.intChars.b2 = memory[temp.intPart + 1].bytPart;
  dest.intChars.b3 = memory[temp.intPart + 2].bytPart;
  dest.intChars.b4 = memory[temp.intPart + 3].bytPart;
  reg[rA] = dest.intPart;
  increment(1);
}

void rmmovl() {
  increment(1);
  unsigned int rA = memory[CF.IP].bytChars.lowBits;
  unsigned int rB = memory[CF.IP].bytChars.highBits;
  intUnion temp;
  increment(1);
  temp.intChars.b1 = memory[CF.IP].bytPart;
  increment(1);
  temp.intChars.b2 = memory[CF.IP].bytPart;
  increment(1);
  temp.intChars.b3 = memory[CF.IP].bytPart;
  increment(1);
  temp.intChars.b4 = memory[CF.IP].bytPart;
  temp.intPart += reg[rB];
  intUnion dest;
  dest.intPart = reg[rA];
  memory[temp.intPart + 0].bytPart = dest.intChars.b1;
  memory[temp.intPart + 1].bytPart = dest.intChars.b2;
  memory[temp.intPart + 2].bytPart = dest.intChars.b3;
  memory[temp.intPart + 3].bytPart = dest.intChars.b4;
  increment(1);
}

void call() {
  increment(1);
  intUnion temp;
  intUnion ret;
  // Destination Address
  temp.intChars.b1 = memory[CF.IP].bytPart;
  increment(1);
  temp.intChars.b2 = memory[CF.IP].bytPart;
  increment(1);
  temp.intChars.b3 = memory[CF.IP].bytPart;
  increment(1);
  temp.intChars.b4 = memory[CF.IP].bytPart;
  increment(1);
  // Old IP Stored
  ret.intPart = CF.IP;
  // Change address in %ESP
  memory[reg[4] - 4].bytPart = ret.intChars.b1;
  memory[reg[4] - 3].bytPart = ret.intChars.b2;
  memory[reg[4] - 2].bytPart = ret.intChars.b3;
  memory[reg[4] - 1].bytPart = ret.intChars.b4;
  // Reset position in %ESP
  reg[4] -= 4;
  CF.IP = temp.intPart;
}

void push() {
  increment(1);
  intUnion ret;
  ret.intPart = reg[memory[CF.IP].bytChars.lowBits];
  memory[reg[4] - 4].bytPart = ret.intChars.b1;
  memory[reg[4] - 3].bytPart = ret.intChars.b2;
  memory[reg[4] - 2].bytPart = ret.intChars.b3;
  memory[reg[4] - 1].bytPart = ret.intChars.b4;
  reg[4] -= 4;
  increment(1);
}

void pop() {
  increment(1);
  intUnion temp;
  // %ESP
  temp.intChars.b1 = memory[reg[4] + 0].bytPart;
  temp.intChars.b2 = memory[reg[4] + 1].bytPart;
  temp.intChars.b3 = memory[reg[4] + 2].bytPart;
  temp.intChars.b4 = memory[reg[4] + 3].bytPart;
  reg[4] += 4;
  // printf("POP: %d\n",temp.intPart);
  reg[memory[CF.IP].bytChars.lowBits] = temp.intPart;
  increment(1);
}

void ret() {
  intUnion temp;
  temp.intChars.b4 = memory[reg[4] + 3].bytPart;
  temp.intChars.b3 = memory[reg[4] + 2].bytPart;
  temp.intChars.b2 = memory[reg[4] + 1].bytPart;
  temp.intChars.b1 = memory[reg[4] + 0].bytPart;
  reg[4] += 4;
  CF.IP = temp.intPart;
}

int main (int argc, char **argv) {
    if (argc != 2) {
        fprintf(stderr, "ERROR: Please enter a filename or \"-h\".\n");
        return(1);
    } else if (strcmp(argv[1], "-h") == 0) {
        printf("Usage: y86emul <y86 file>\n");
  		return(0);
    }

    FILE * file = fopen(argv[1], "r");
    if (!file) {
        fprintf(stderr, "ERROR: Could not find file \"%s\".\n", argv[1]);
        return(1);
    }

    char directive[1000]; // Arbitrary amount of space
    while (fscanf(file, "%s", directive) != EOF) {
        if (strcmp(directive, ".size") == 0) {
            unsigned int size;
            fscanf(file, "%x", &size);
            memory = malloc(size*sizeof(bytUnion));
            break;
        }
    }

    if (memory == NULL) {
        fprintf(stderr, "ERROR: .size directive not found.\n");
        return(1);
    }

    int value;
    int address;
    bool textExists;
    while (fscanf(file, "%s", directive) != EOF) {
        if (strcmp(directive, ".byte") == 0)
        {
            fscanf(file, "%x %x", &address, &value);
            memory[address].bytPart = (char)value;
            // printf("%c\n", memory[address].bytPart);
        }
        else if (strcmp(directive, ".text") == 0)
        {
            textExists = true;
            int length;
            char string[1000];
            fscanf(file, "%x", &address);
            CF.IP = address;
            fgets(string, 1000, file); 
            length = strlen(string) - 1;
            fseek(file, -length, SEEK_CUR);

            for (int i = 0; i < length / 2; i++) {
                fscanf(file, " %1x", &value);
                memory[address].bytChars.lowBits = value;
                fscanf(file, " %1x", &value);
                memory[address].bytChars.highBits = value;
                address++;
            }
            address++;
        }
        else if (strcmp(directive, ".string") == 0)
        {
            char c;
            fscanf(file, "%x", &address);
            fscanf(file, " %c", &c);
            do {
                fscanf(file, "%c", &c);
                if (c != '\"') {
                    memory[address++].bytPart = c;
                }
            } while (c != '\"');
        }
        else if (strcmp(directive, ".long") == 0)
        {
            fscanf(file, "%x %x", &address, &value);
            intUnion longVal;
            longVal.intPart = value;

            memory[address + 0].bytPart = longVal.intChars.b1;
            memory[address + 1].bytPart = longVal.intChars.b2;
            memory[address + 2].bytPart = longVal.intChars.b3;
            memory[address + 3].bytPart = longVal.intChars.b4;
        }
        else
        {   
            fprintf(stderr, "ERROR: Unidentified directive, memory allocation failed.\n");
            return(1);
        }
    }

    if (!textExists) {
        fprintf(stderr, "ERROR: .text directive is missing from file.\n");
        return(1);
    }

    int op = 0; // To remove compiler warning
    while (1) {
        op = memory[CF.IP].bytChars.lowBits;
        // printf("OP:%d IP:%d%d ESP: %d reg[5]: %d\n", instr, memory[CF.IP].bytChars.lowBits, memory[CF.IP].bytChars.highBits, reg[4], reg[5]);
        switch (op) 
        {
        case 0:  nop();     break;
        case 1:  exit(0);   break;
        case 2:  rrmovl();  break;
        case 3:  irmovl();  break;
        case 4:  rmmovl();  break;
        case 5:  mrmovl();  break;
        case 6:  op1();     break;
        case 7:  jump();    break;
        case 8:  call();    break;
        case 9:  ret();    break;
        case 10: push();    break;
        case 11: pop();     break;
        case 12: read();    break;
        case 13: write();   break;
        case 14: movsbl();  break;
        default: fprintf(stderr, "ERROR: Undefined instruction, %d.\n", op); return(1);
        }
    }
    fprintf(stderr, "ERROR: No halt instruction found.\n");
    exit(1);
}