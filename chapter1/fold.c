/*
 * Exercise 1-22.
 *
 * Write a program to fold long input lines into two or more shorter lines after
 * the last non-blank character that occurs before the n-th column of input.
 * Make sure your program does something intelligent with very long lines, and
 * if there are no blanks or tabs before the specified column.
 *
 * Compile with: gcc -o fold fold.c
 */

#include <stdio.h>

#define WRAP 40
#define MAX_LINE 256

void print_wrap(const char line[])
{
    for (int i = 0; i < WRAP; ++i)
        putchar(line[i]);
    puts("");
}

/* get_line: read a line into s, return length */
int get_line(char s[], int lim)
{
    int c, i;

    for (i=0; i < lim-1 && (c=getchar())!=EOF && c!='\n'; ++i)
        s[i] = c;

    if (c == '\n')
        s[i++] = c;

    s[i] = '\0';
    return i;
}

int main(void)
{
    int len, wrap_count;
    char line[MAX_LINE];

    while ((len = get_line(line, MAX_LINE)) > 0) {
        if (len < WRAP)
           printf("%s", line);
        else {
            wrap_count = 0;
            while (len > WRAP) {
                print_wrap(line + WRAP * wrap_count);
                len -= WRAP;
                ++wrap_count;
            }
            printf("%s", line + WRAP * wrap_count);
        }
    }

    return 0;
}
