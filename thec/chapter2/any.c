/*
 * Exercise 2.5.
 *
 * Write the function any(s1, s2), which returns the first location in a string
 * s1 where any character from the string s2 occurs, or -1 if s1 contains no
 * characters from s2 . (The standard library function strpbrk does the same job
 * but returns a pointer to the location.)
 *
 * Compile with: gcc -o any any.c
 */

#include <stdio.h>

int any(char* s1, char* s2)
{
    int i, j;
    for (i = 0; s2[i] != '\0'; ++i) {
        for (j = 0; s1[j] != '\0'; ++j) {
            if (s2[i] == s1[j])
                return j;
        }
    }
    return -1;
}

int main(int argc, char* argv[])
{
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <s1> <s2>\n", argv[0]);
        return 1;
    }

    printf("%d\n", any(argv[1], argv[2]));

    return 0;
}
