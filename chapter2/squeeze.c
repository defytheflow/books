/*
 * Exercise 2.4.
 *
 * Write an alternative version of squeeze(s1,s2) that deletes each character in
 * s1 that matches any character in the string s2 .
 *
 * Compile with: gcc -o squeeze squeeze.c
 */

#include <stdio.h>

void squeeze(char* s1, char* s2)
{
    int i, j, k;
    for(i = 0; s2[i] != '\0'; ++i) {
        for (j = k = 0; s1[j] != '\0'; ++j) {
            if (s1[j] != s2[i])
                s1[k++] = s1[j];
        }
        s1[k] = '\0';
    }
}

int main(int argc, char* argv[])
{
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <s1> <s2>\n", argv[0]);
        return 1;
    }

    squeeze(argv[1], argv[2]);
    puts(argv[1]);

    return 0;
}
