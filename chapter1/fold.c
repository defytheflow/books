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

#define FOLD     40
#define MAXLINE 256

int get_line(char* s, int lim);
void print_fold(const char* line);

int main(void)
{
    int len, fold_count;
    char line[MAXLINE];

    while ((len = get_line(line, MAXLINE)) > 0) {
        if (len < FOLD)
           printf("%s", line);
        else {
            fold_count = 0;
            while (len > FOLD) {
                print_fold(line + FOLD * fold_count);
                len -= FOLD;
                ++fold_count;
            }
            printf("%s", line + FOLD * fold_count);
        }
    }

    return 0;
}

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

void print_fold(const char* line)
{
    for (int i = 0; i < FOLD; ++i)
        putchar(line[i]);
    putchar('\n');
}
