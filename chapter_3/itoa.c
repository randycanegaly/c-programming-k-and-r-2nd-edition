#include <stdio.h>
#include <string.h>

#define MAX_ARR 1000
#define abs(x) ((x) < 0 ? -(x): (x))
void itoa(int n, char s[]);
void reverse(char s[]);

int main(void) {
    int big_neg = -2147483648;
    //int big_neg = 101;
    char s[MAX_ARR];

    itoa(big_neg, s);
    printf("%s\n", s);
}


void itoa(int n, char s[]) {//convert an int into a string with those digits
    int i, sign;

    //if ((sign = n) < 0)//sign, is it less than 0?
        //n = -n;//if so, make n negative, this will fail for largest negative number 
        //because the largest positive number is 1 less than the absolute value of the 
        //largest negative number, just changing the sign of big_neg puts it outside the range
        //of possible positive numbers
        //so the n = -n thing has to go. comment it out
    sign = n;

    i = 0;
    do {
        s[i++] = abs(n % 10) + '0';
        //since we are no longer trying to make n negative, for fear of big_neg,
        //use absolute values here - we're going to stick a negative sign on the front later anyway
        //printf("%d\n", s[i]);

    } while ((n /= 10) != 0);
    if (sign < 0)
        s[i++] = '-';
    s[i] = '\0';
    reverse(s);
}


void reverse(char s[]) {
    int c, i, j;

    for(i = 0, j = strlen(s) - 1; i < j; i++, j--) {
        c = s[i];
        s[i] = s[j];
        s[j] = c;
    }
}
