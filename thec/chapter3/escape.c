/*
 * Exercise 3.2.
 *
 * Write a function escape(s, t) that converts characters like newline and tab
 * into visible escape sequences like \n and \t as it copies the string t to s.
 * Use a switch . Write a function for the other direction as well, converting
 * escape sequences into the real characters.
 *
 * Compile with: gcc -o escape escape.c
 */

#include <stdio.h>

#define MAXLINE 512
#define TAB_SPACES 8

char* escape(char* s, const char* t)
{
    int i, j;
    for (i = j = 0; t[i] != '\0'; ++i) {
        switch (t[i]) {
        case '\n':
            s[j++] = '\\';
            s[j++] = 'n';
            break;
        case '\t':
            s[j++] = '\\';
            s[j++] = 't';
            break;
        default:
            s[j++] = t[i];
            break;
        }
    }
    s[j] = '\0';
    return s;
}

char* escape_back(char* s, const char* t)
{
    int i, j;
    for (i = j = 0; t[i] != '\0'; ++i) {
        if (t[i] == '\\') {
            switch (t[i+1]) {
            case 't':
                for (int k = 0; k < TAB_SPACES; ++k)
                    s[j++] = ' ';
                ++t;
                break;
            case 'n':
                s[j++] = '\n';
                ++i;
                break;
            default:
                s[j++] = t[i];
                break;
            }
        } else
            s[j++] = t[i];
    }
    s[j] = '\0';
    return s;
}

int main(void)
{
    char s[MAXLINE], t[MAXLINE];
    while (fgets(t, sizeof(t), stdin)) {
        printf("%s\n", escape(s, t));
        printf("%s\n", escape_back(t, s));
    }
    return 0;
}
