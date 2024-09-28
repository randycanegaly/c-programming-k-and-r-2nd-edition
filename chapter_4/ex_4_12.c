#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_ARR 1000
void itoa(int n, char s[]);

int main(void) {
    int n = 123;
    char s[MAX_ARR];

    itoa(n, s);
    printf("%s\n", s);
}
/* make a recursive version of itoa */

void itoa(int n, char s[]) {
    static int i;

    if (n / 10)
        itoa(n / 10, s);//call itself with the next smaller piece
    else {//cant divide any more, left most digit
        i = 0;//for tracking just inside this recursion layer
        if (n < 0)
            s[i++] = '-';//put negative sign in front
    }
    //put the digit in s now
    s[i++] = abs(n) % 10 + '0';//this gets the ASCII table value, abs is because we already handled if negative above
    s[i] = '\0';//terminate the string properly     
    //printf("%s\n", s);
}

