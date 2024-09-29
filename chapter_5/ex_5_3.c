#include <stdio.h>

/* Write a pointer version of strcat()
strcat: concatenate t to the end of s */
/*void strcat(char s[], char t[]) {
    int i, j;

    i = j = 0;
    while (s[i] != '\0')//go to the end of s
        i++;
    while ((s[i++] = t[j++]) != '\0')
        ;
*/

void my_strcat(char *s, char *t) {
    int i, j;

    i = j = 0;
    while (*s)
        s++;
    while (*s++ = *t++)
        ;
}

int main(void) {
    char s[] = "Hello ";
    char t[] = "Randy!";

    my_strcat(s, t);
    printf("%s\n", s);
}

