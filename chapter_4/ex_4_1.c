#include <stdio.h>
#define MAXLINE 1000

/*Write the function strrindex that returns the index of the the rightmost occurrence of 
 *t in s
 */

int my_getline(char line[], int max);
int strindex(char source[], char searchfor[]);
int strrindex(char source[], char searchfor[]);

char pattern[] = "ould";

int main(void) {
    char line[MAXLINE];
    int found = 0;
    int foundIndex;

    while (my_getline(line, MAXLINE) > 0)
        if ((foundIndex = strrindex(line, pattern)) >= 0) {
            printf("Found rightmost \"%s\" at index %d\n", pattern, foundIndex);
            found++;
        }
    return found;
}

int my_getline(char s[], int lim) {
    int c, i;

    i = 0;
    while (--lim > 0 && (c = getchar()) != EOF && c != '\n')
        s[i++] = c;
    if (c == '\n')
        s[i++] = c;
    s[i] = '\0';
    return i;
}

int strindex(char s[], char t[]) {
    int i, j, k;

    for (i = 0; s[i] != '\0'; i++) {//walk s, stop at terminating char
        for (j = i, k = 0; t[k] != '\0' && s[j] == t[k]; j++, k++) //sit on i in s
            //walk t until hit the end of as long element at j in s matches element k in t
            ;
        if (k > 0 && t[k] == '\0') {//hit the end of k and return i
            return i;
        }
    }
    return -1;
}

//return the rightmost occurrence of t in s, or -1 if no occurrence
int strrindex(char s[], char t[]) {
    int i, j, k, rightmost;
    rightmost = -1;
    for (i = 0; s[i] != '\0'; i++) {//walk s, stop at terminating char
        for (j = i, k = 0; t[k] != '\0' && s[j] == t[k]; j++, k++) //sit on i in s
            //walk t, but only while we are not at the end the elements in t match s
            //and do nothing at each loop iteration
            ;
        if (k > 0 && t[k] == '\0') {//hit the end of k
            rightmost = i;//store i, where the matching first started as rightmost
            //since we are moving left to right, each successive match of t in s will be rightmost
        }
    }

    if (rightmost != -1)
        return rightmost;
    else
        return -1;
}
