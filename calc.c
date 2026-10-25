// Sergejs Kruglovs 251RDC089
// https://github.com/sergeyakula/lab1
// Compile with: gcc -O2 -Wall -Wextra -std=c17 -o calc calc.c -lm

#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[]) {
    if (argc != 4 || strcmp(argv[1], "-o") != 0) {
        fprintf(stderr, "usage: calc -o OUTDIR input.txt\n");
        return 1;
    }
    const char *outdir = argv[2];
    const char *input  = argv[3];
    printf("outdir=%s input=%s\n", outdir, input);
    return 0;
}