/*
 * Exercise 1-24.
 *
 * Write a program to check a C program for rudimentary syntax errors like
 * unmatched parentheses, brackets and braces. Don't forget about quotes, both
 * single and double, escape sequences, and comments. (This program is hard if
 * you do it in full generality.)
 *
 * Compile with: gcc -o syntax syntax.c
 */

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define STACKSIZE 1024
#define STACKEMPTY '\0'
#define NOPAIR '\0'

bool stack_empty(void);
char stack_pop(void);
void stack_print(void);
void stack_push(char c);
char stack_end(void);

char token_pair(char c);

void skip_oneline_comment(FILE* stream);
void skip_multiline_comment(FILE* stream);

char stack[STACKSIZE];
int sp = 0;  // Stack pointer.
int ln = 1;  // Line number.

int main(int argc, char* argv[])
{
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <fname>\n", argv[0]);
        return 1;
    }

    FILE* in;
    if (!(in = fopen(argv[1], "r"))) {
        fprintf(stderr, "Error: unable to open file '%s'\n", argv[1]);
        return 1;
    }

    char c, d;
    while ((c = getc(in)) != EOF) {

        // Skip comments.
        if (c == '/') {
            if ((d = getc(in)) == '/') {
                skip_oneline_comment(in);
                continue;
            }
            else if (d == '*') {
                skip_multiline_comment(in);
                continue;
            }
            else
                ungetc(d, in);
        }

        // Ignore inside quotes.
        if (strchr("'\"", c)) {
            stack_push(c);
            while ((d = getc(in)) != c) {
                if (d == '\\')
                    getc(in);  // Ignore escape sequences.
            }
            stack_pop();
        }

        if (strchr("()[]{}", c)) {
            if (!stack_empty() && stack_end() == token_pair(c)) {
                stack_pop();
                continue;
            }
            stack_push(c);
        }

        if (c == '\n')
            ++ln;
    }

    stack_print();

    return 0;
}

void skip_oneline_comment(FILE* stream)
{
    int c;
    while ((c = getc(stream)) != '\n')
        ;
    ungetc('\n', stream);
}

void skip_multiline_comment(FILE* stream)
{
    int c = getc(stream);
    int d = getc(stream);
    while (c != '*' || d != '/') {
        if (c == '\n')
            ++ln;
        c = d;
        d = getc(stream);
    }
}

char token_pair(char c)
{
    static const char* open = "([{\"'";
    static const char* close = ")]}\"'";

    char* p;
    if ((p = strchr(open, c)))
        return close[p - open];

    if ((p = strchr(close, c)))
        return open[p - close];

    return NOPAIR;
}

bool stack_empty(void)
{
    return sp == 0;
}

char stack_pop(void)
{
    if (sp < 0)
        return STACKEMPTY;
    printf("%d: Popped %c\n", ln, stack[sp - 1]);
    return stack[--sp];
}

void stack_print(void)
{
    printf("Stack: ");
    for (int i = 0; i < sp; ++i)
        printf("%c ", stack[i]);
    puts("");
}

void stack_push(char c)
{
    if (sp == STACKSIZE) {
        fprintf(stderr, "Error: stack overflow.\n");
        exit(1);
    }
    stack[sp++] = c;
    printf("%d: Pushed %c\n", ln, c);
}

char stack_end(void)
{
    return stack[sp - 1];
}
