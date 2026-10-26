// Sergejs Kruglovs 251RDC089
// https://github.com/sergeyakula/lab1
// Compile with: gcc -O2 -Wall -Wextra -std=c17 -o calc calc.c -lm

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

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

    // Output name is the input name without folders and without .txt.
    const char *base = strrchr(input, '/');
    base = (base != NULL) ? base + 1 : input;
    size_t base_len = strlen(base);
    if (base_len >= 4 && strcmp(base + base_len - 4, ".txt") == 0)
        base_len -= 4;

    char path[4096];
    snprintf(path, sizeof path, "%s/%.*s_sergejs_kruglovs_251RDC089.txt",
             outdir, (int)base_len, base);

    if (mkdir(outdir, 0755) != 0 && errno != EEXIST)
    {
        fprintf(stderr, "calc: cannot create %s\n", outdir);
        free(buf);
        return 1;
    }

    FILE *out = fopen(path, "w");
    if (out == NULL)
    {
        fprintf(stderr, "calc: cannot write %s\n", path);
        free(buf);
        return 1;
    }

    // op starts as +, so the first number is added to 0.
    long long result = 0;
    char op = '+';
    int has_number = 0; // Blank lines give no output.
    size_t i = 0;

    while (i < len)
    {
        char c = buf[i];
        if (c == '\n')
        {
            if (has_number)
                fprintf(out, "%lld\n", result);
            result = 0;
            op = '+';
            has_number = 0;
            i++;
        }
        else if (c == ' ' || c == '\t')
        {
            i++;
        }
        else if (c >= '0' && c <= '9')
        {
            long long num = 0;
            while (i < len && buf[i] >= '0' && buf[i] <= '9')
            {
                num = num * 10 + (buf[i] - '0');
                i++;
            }
            if (op == '+')
                result += num;
            else
                result -= num;
            has_number = 1;
        }
        else if (c == '+' || c == '-')
        {
            op = c;
            i++;
        }
        else
        {
            i++;
        }
    }

    // Last line may have no \n at the end.
    if (has_number)
        fprintf(out, "%lld\n", result);

    fclose(out);
    free(buf);
    return 0;
}