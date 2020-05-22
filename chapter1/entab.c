/*
 * Exercise 1-21.
 *
 * Write a program entab that replaces strings of blanks by the minimum number
 * of tabs and blanks to achieve the same spacing. Use the same tab stops as
 * for detab. When either a tab or a single blank would suffice to reach a tab
 * stop, which should be given preference?
 *
 * Compile with: gcc -o entab entab.c
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define MAX_LINE 512
#define HELP_MSG "Try 'entab -h' for more information."

void usage()
{
    puts("Converts spaces to tabs.\n");

    puts("Usage:");
    puts("  entab [options]\n");

    puts("Options:");
    puts("  -h           show this message.");
    puts("  -t <size>    number of spaces per tab.\n");
}

void parse_opts(int argc, char** argv, int* tab_out)
{
    char c;
    opterr = 0;

    while ((c = getopt(argc, argv, "ht:")) != -1) {
        switch (c) {
        case 'h':
            usage();
            exit(0);
        case 't':
            *tab_out = atoi(optarg);
            break;
        case '?':
            fprintf(stderr, "Error: ");
            if (optopt == 't')
                fprintf(stderr, "option '-%c' requires an argument.\n", optopt);
            else
                fprintf(stderr, "unknown option '-%c'.\n", optopt);
            fprintf(stderr, "%s\n", HELP_MSG);
            exit(1);
        }
    }
}


/* Check that next 'count' chars are equal to 'c' */
int check_next(char* line, int count, char c)
{
    for (int i = 0; i < count; ++i) {
        if (line[i] != c)
            return 0;
    }
    return 1;
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

int main(int argc, char** argv)
{
    int i, len, tab;
    char line[MAX_LINE];

    tab = 8;
    parse_opts(argc, argv, &tab);

    while ((len = get_line(line, MAX_LINE)) > 0) {
        for (i = 0; i < len - tab + 1; ++i)
            if (line[i] == ' ' && check_next(line+i+1, tab-1, ' ')) {
                putchar('\t');
                i += tab - 1;
            } else
                putchar(line[i]);
        printf("%s", line + i);
    }

    return 0;
}
