#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>
#include "nCr.h"

int main(int argc, char** argv)
{
    if (argc != 2) {
        fprintf(stderr, "ERROR: You must enter an argument.\n");
        return 1;
    }
    if (argv[1][0] == '-') {
        if (argv[1][1] == 'h') {
            printf("Usage: formula <positive integer>\n");
            return 0;
        }
        else {
            fprintf(stderr, "ERROR: Did you mean '-h'?\n");
            return -1;
        }
    }
    int number = (int)strtol(argv[1], NULL, 10);
    if (number < 0) {
        fprintf(stderr, "ERROR: Only non-negative numbers are allowed.\n");
        return -1;
    }
    int r = 1;
    int ans;
    struct timeval start, end;
    gettimeofday(&start, NULL);
    if (Factorial(number) == -1) {
        gettimeofday(&end, NULL);
        printf("Time Required = %lu microseconds\n",
        (end.tv_sec - start.tv_sec) / 10000000 + (end.tv_usec - start.tv_usec));
        exit(1);
    }
    printf("(1 + x)^%d = 1 ", number);
    while (r < number + 1) {
        ans = nCr(number, r);
        if (ans == -1) {
            exit(1);
        }
        printf("+ %d*x^%d ", ans, r);
        r++;
    }
    printf("\n");
    gettimeofday(&end, NULL);
    printf("Time Required = %lu microseconds\n",
    (end.tv_sec - start.tv_sec) / 10000000 + (end.tv_usec - start.tv_usec));
    return 0;
}