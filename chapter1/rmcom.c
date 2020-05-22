/*
 * Exercise 1-23.
 *
 * Write a program to remove all comments from a C program. Don't forget to
 * handle quoted strings and character constants properly. C comments don't nest.
 *
 * Compile with: gcc -o rmcom rmcom.c
 */

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char** argv)
{
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
        return 1;
    }

    FILE* file = fopen(argv[1], "r");
    if (!file) {
        perror("Error");
        return 1;
    }

    int c, d; // Well, hello there!
    while ((c = fgetc(file)) != EOF) {
        if (c == '/') {
            if ((d = fgetc(file)) == '/') { // Oneline comment.
                while ((d = fgetc(file)) != '\n')
                    ;
                putchar(d);
            } else if (d == '*') { // Multiline comment.
                c = fgetc(file);
                d = fgetc(file);
                while (c != '*' || d != '/') {
                    c = d;
                    d = fgetc(file);
                }
            } else { // Not a comment.
                putchar(c);
                putchar(d);
            }
        } else if (c == '"' || c == '\'') { // String or character literal.
            putchar(c);
            while ((d = fgetc(file)) != c) {
                putchar(d);
                if (d == '\\')
                    putchar(fgetc(file));  // Ignore escape sequence.
            }
            putchar(c);
        } else { // Not a comment.
            putchar(c);
        }
    }

    fclose(file);
    return 0;
}
