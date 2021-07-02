#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

#define MAX_CELL 3000
#define MAX_CHAR 5000
#define MAX_STACK 1024


void die(const char *fmt, ...) {
    va_list ap;
    va_start(ap, fmt);
    vfprintf(stderr, fmt, ap);
    va_end(ap);
    fputc('\n', stderr);
    exit(1);
}


int init_map(int *map, char *code)
{
    int stack[MAX_STACK];  // enough maybe
    int top = -1;
    int i = 0, l;

    while (*code)
    {
        switch (*code) {
            case '[': stack[++top] = i; break;
            case ']': {
                l = stack[top--];
                *(map+l) = i;
                *(map+i) = l;
            } break;
        }
        ++code;
        ++i;
    }

    return 0;
}


int clean(char *buf, FILE *fp)
{
    int c, i = 0;
    while ((c = fgetc(fp)) != EOF)
    {
        if (c == '>' ||
            c == '<' ||
            c == '+' ||
            c == '-' ||
            c == '.' ||
            c == ',' ||
            c == '[' ||
            c == ']') {
            buf[i++] = (char)c;
        }
    }
    buf[i] = 0;
    return i;
}


int main(int argc, char **argv)
{
    int sp = 0, n;
    char cells[MAX_CELL] = {0};
    int map[MAX_CELL] = {0};
    char code[MAX_CHAR] = {0};

    FILE *fp;

    if (argc < 2)
        die("usage: %s [filename]", argv[0]);

    if ((fp = fopen(argv[1], "r")) == NULL)
        die("no such file: %s", argv[1]);

    n = clean(code, fp);
//    printf("%d character(s)\n", n);

    fclose(fp);

    if (init_map(map, code) < 0)
        die("error linting");

    for (int i = 0; i < n; ++i)
    {
        switch (code[i]) {
            case '>': ++sp; break;
            case '<': --sp; break;
            case '+': ++cells[sp]; break;
            case '-': --cells[sp]; break;
            case '.': putc(cells[sp], stdout); break;
            case ',': cells[sp] = (char) getc(stdin); break;
            case '[': if (cells[sp] == 0) { i = map[i]; }
                break;
            case ']': if (cells[sp] != 0) { i = map[i]; }
                break;
        }

    }

    return 0;
}

