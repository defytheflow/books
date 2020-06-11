/*
 * Exercise 3.3.
 *
 * Write a function expand(s1,s2) that expands shorthand notations like a-z in
 * the string s1 into the equivalent complete list abc...xyz in s2 . Allow for
 * letters of either case and digits, and be prepared to handle cases like a-b-c
 * and a-z0-9 and -a-z. Arrange that a leading or trailing - is taken literally.
 *
 * Compile with: gcc -o expand expand.c
 */

#include <ctype.h>
#include <stdio.h>

#define MAXLINE 512

char* expand(const char* s1, char* s2)
{
    int i, j, k;
    for (i = j = 0; s1[i] != '\0'; ++i) {
        if (s1[i+1] == '-' && s1[i] <= s1[i+2]) {
            if ((isdigit(s1[i]) && isdigit(s1[i+2])) ||
                (islower(s1[i]) && islower(s1[i+2])) ||
                (isupper(s1[i]) && isupper(s1[i+2]))) {
                for (k = s1[i]; k < s1[i+2]; ++k)
                    s2[j++] = k;
                ++i;
            }
        } else
            s2[j++] = s1[i];
    }
    s2[j] = '\0';
    return s2;
}

int main(int argc, char* argv[])
{
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <s>\n", argv[0]);
        return 1;
    }

    char s[MAXLINE];
    printf("%s\n", expand(argv[1], s));

    return 0;
}
