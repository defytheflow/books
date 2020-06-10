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

#define STACK_SIZE 1024
#define STACK_EMPTY '\0'
#define NO_MATCH_PAREN '\0'
#define MAX_ERR_MSG 80

bool stack_empty(void);
char stack_pop(void);
void stack_print(void);
void stack_push(char c);

void skip_oneline_comment(FILE* stream);
void skip_multiline_comment(FILE* stream);

bool are_opposite_paren(char c1, char c2);
char get_match_paren(char c);
bool is_open_paren(char c);
bool is_close_paren(char c);

void syntax_error(const char* fname, const char* err_msg);
int getch(FILE* stream);

int sp = 0;  // Stack pointer.
int ln = 1;  // Line number.
int cn = 1;  // Char number.
char stack[STACK_SIZE];

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

    char c, d, err_msg[MAX_ERR_MSG];
    while ((c = getch(in)) != EOF) {
        // Ignore syntax inside comments.
        if (c == '/') {
            if ((d = getch(in)) == '/') {
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

        // Ignore syntax inside quotes.
        if (strchr("'\"", c)) {
            while ((d = getch(in)) != c) {
                if (d == '\n') { // No matching quote.
                    snprintf(err_msg, MAX_ERR_MSG, "missing terminating %c character", c);
                    syntax_error(argv[1], err_msg);
                }
                if (d == '\\')
                    getch(in);  // Ignore escape sequences.
            }
        }

        if (strchr("()[]{}", c)) {
            if (!stack_empty()) {
                if (stack[sp-1] == get_match_paren(c)) { // If paren matches.
                    stack_pop();
                    continue;
                } else if (are_opposite_paren(stack[sp-1], c)) { // If doesn't match.
                    snprintf(err_msg, MAX_ERR_MSG, "expected '%c'", get_match_paren(stack[sp-1]));
                    syntax_error(argv[1], err_msg);
                }
            }
            stack_push(c);
        }

        if (c == '\n')
            ++ln;
    }

#ifdef DEBUG
    stack_print();
#endif

    if (!stack_empty()) { // If didn't match all parens.
        snprintf(err_msg, MAX_ERR_MSG, "expected '%c'", get_match_paren(stack[sp-1]));
        syntax_error(argv[1], err_msg);
    }

    return 0;
}

/*
 * Wrapper around getch, that updates char number.
 */
int getch(FILE* stream)
{
    int c = getc(stream);
    cn = (c == '\n') ? 0 : cn + 1;
    return c;
}

/*
 * Reports a syntax error with line and char numbers, terminates the program.
 */
void syntax_error(const char* fname, const char* err_msg)
{
    fprintf(stderr, "%s:%d:%d: error: %s\n", fname, ln, cn, err_msg);
    exit(1);
}

void skip_oneline_comment(FILE* stream)
{
    int c;
    while ((c = getch(stream)) != '\n')
        ;
    ungetc('\n', stream);
}

void skip_multiline_comment(FILE* stream)
{
    int c = getch(stream);
    int d = getch(stream);
    while (c != '*' || d != '/') {
        if (c == '\n')
            ++ln;
        c = d;
        d = getch(stream);
    }
}

char get_match_paren(char c)
{
    switch (c) {
        case '(': return ')';
        case ')': return '(';
        case '[': return ']';
        case ']': return '[';
        case '{': return '}';
        case '}': return '{';
        default: return NO_MATCH_PAREN;
    }
}

bool is_open_paren(char c)
{
    return c == '(' || c == '[' || c == '{';
}

bool is_close_paren(char c)
{
    return c == ')' || c == ')' || c == '}';
}

bool are_opposite_paren(char c1, char c2)
{
    return (is_open_paren(c1) && is_close_paren(c2)) ||
            (is_open_paren(c2) && is_close_paren(c1));
}

bool stack_empty(void)
{
    return sp == 0;
}

char stack_pop(void)
{
    if (sp < 0)
        return STACK_EMPTY;
#ifdef DEBUG
    printf("%d: Popped %c\n", ln, stack[sp - 1]);
#endif
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
    if (sp == STACK_SIZE) {
        fprintf(stderr, "Error: stack overflow.\n");
        exit(1);
    }
    stack[sp++] = c;
#ifdef DEBUG
    printf("%d: pushed %c\n", ln, c);
#endif
}
