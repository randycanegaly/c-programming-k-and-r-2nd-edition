#include <stdio.h>
#include <string.h>

#define MAX_ARR 1000
#define abs(x) ((x) < 0 ? -(x): (x))

/*Write the function itob(n,s,b) that converts the integer n into a base b character representation
 * in the string s. In particular, itob(n,s,16) formats n as a hexidecimal integer
 */

/*
 * 2730 % 16 = 10 = a, that gives the first digit on the right
 * reduce 2730 to get the next digit - integer division --> 2730 / 16 = 170
 * 170 % 16 = 10 = a, that gives the next digit rightward
 * reduce 170 to get the next digit - integer division --> 170 / 16 = 10
 * 10 % 16 = 10 = a, that gives the next digit rightward
 * reduce 10 to get the next digit --> 10 / 16 = 0 stop
 */

void itob(int n, char s[], int b);
void reverse(char s[]);

int main(void) {
    int to_hex_num = 2730;
    int to_bin_num = 23;
    char s[MAX_ARR];

    itob(to_hex_num, s, 16);
    printf("hex: %s\n", s);
    
    itob(to_bin_num, s, 2);
    printf("bin: %s\n", s);
}


void itob(int n, char s[], int b) {
    int i, j, sign;

    if ((sign = n) < 0)//left expression assigns n to sign and returns the value of sign, test for negative number
        n = -n;//turn the negative number positive, retains the problem that can't do this for the most negative number

    i = 0;
    do {
        //get the next digit
        j = n % b;
        //how do we represent the digit? What base? number or letter?
        //if j is 10 through 15, need to make it a through f
        //the ASCII number of 'a' is 97, so if j = 12, need a c
        //so need to calculate to get 99
        //do this, j + 'a' = 109, that minus 10 (the nominal value of 'a') = 99 --> 'c' from the ASCII table
        //if j is <= 9, then need to calculate its ASCII number relative to ASCII '0'
        //'0's ASCII table number is 30
        //say that j = 4, its int value needs to be 34, 4 + '0' = 34, hence j + '0'
        s[i++] = (j <= 9) ? j + '0' : j + 'a' -10;

    } while ((n /= b) != 0);//this is the dump/reduce a digit to set up to get the next digit
    
    if (sign < 0)
        s[i++] = '-';//we know the number is negative, so stick the neg sign on the right (everything is still backwards)
    s[i] = '\0';//properly terminate the backwards string
    reverse(s);//make it all not backwards
}


void reverse(char s[]) {
    int c, i, j;

    for(i = 0, j = strlen(s) - 1; i < j; i++, j--) {
        c = s[i];
        s[i] = s[j];
        s[j] = c;
    }
}
