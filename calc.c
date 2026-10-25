// Sergejs Kruglovs 251RDC089
// https://github.com/sergeyakula/lab1
// Compile with: gcc -O2 -Wall -Wextra -std=c17 -o calc calc.c -lm

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[])
{
    if (argc != 4 || strcmp(argv[1], "-o") != 0)
    {
        fprintf(stderr, "usage: calc -o OUTDIR input.txt\n");
        return 1;
    }
    const char *outdir = argv[2];
    const char *input = argv[3];
    FILE *f = fopen(input, "rb");
    if (f == NULL)
    {
        fprintf(stderr, "calc: cannot open %s\n", input);
        return 1;
    }

    // Read the whole file at once, so position = index + 1.
    fseek(f, 0, SEEK_END);
    long size = ftell(f);
    rewind(f);

    char *buf = malloc((size_t)size + 1);
    if (buf == NULL)
    {
        fprintf(stderr, "calc: out of memory\n");
        fclose(f);
        return 1;
    }

    size_t len = fread(buf, 1, (size_t)size, f);
    fclose(f);
    buf[len] = '\0';

    printf("read %zu bytes from %s, output goes to %s\n", len, input, outdir);

    free(buf);
    return 0;
}