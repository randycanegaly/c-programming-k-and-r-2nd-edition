#include <stdio.h>
#include <string.h>

/* Write a pointer version of strend(), return 1 if string t occurs at the end of string s */

int strend(char *s, char *t) {
    int i, j, len;

/*walk back from end of both, checking for matches */
    len = strlen(t);
 
    while (*s) {
        s++;
    }
    
    while (*t) {
        t++; 
    } 
    
    if (*s == *t) {
        for(j = len - 1; j > 0 && *s == *t; j--) {
            --s;
            --t;
        }
        if (j > 0)
            return 0;
    } else
        return 0;
 
    return 1;
}    
    

int main(void) {
    char s[] = "My name is Randy";
    char t[] = "Randy";

    int result = strend(s, t);
    printf("%d\n", result);
}

