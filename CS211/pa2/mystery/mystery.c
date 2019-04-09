#include <stdio.h>
#include <stdlib.h>

long num[200];

long add(long a, long b) {
    return a + b;
}

long compute_fib(long n) {
    if (num[n] != -1) {
        return num[n];
    }
    long a = -1;
    if (n == 0) {
        a = 0;
    } else {
        if(n == 1) {
            a = 1;
        } else {
            a = add(compute_fib(n-1),compute_fib(n-2));
        }
    }
    if(num[n] == -1) {
        num[n] = a;
    }
    return num[n];
}

int main (int argc, char **argv) {
    int arg = atoi(argv[1]);
    int i = 0;

    while (i < 200) {
        num[i] = -1;
        i++;
    }
    printf("Value:   %d\n", compute_fib(arg));
    return 0;
}
