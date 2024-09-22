#include <stdio.h>
#include <string.h>

#define MAX_ARR 1000
#define abs(x) ((x) < 0 ? -(x): (x))
void itoa_width(int n, char s[], int w);
void reverse(char s[]);

/*Write a version of itoa that accepts three arguments instead of two. The third argument is a minimum field width;
 * the converted number must be padded with blanks on the left if necessary to make it wide enough.
 */

int main(void) {
    int some_num = 129;
    int min_width = 11;
    char s[MAX_ARR];

    itoa_width(some_num, s, min_width);
    printf("padded num: %s\n", s);
}


void itoa_width(int n, char s[], int w) {//convert an int into a string with those digits
    int i, sign, j;

    sign = n;

    i = 0;
    do {
        s[i++] = abs(n % 10) + '0';//fix for the "I can't handle the most negative-ist number in 2s complement

    } while ((n /= 10) != 0);
    if (sign < 0)
        s[i++] = '-';
    //it's backwards at this point. 
    //after reverse, if w is 10, then we would want 129 to come out as "^^^^^^^129", 
    //where ^ is my marker for a space
    //so, before reversing, it should look like "921^^^^^^^"
    //that means we just need to figure out how many spaces need to get to the minimum field width and tack that
    //many blanks on the end
    for (j = i; j < w; j++) {
        s[j] = ' ';
    }
    s[j] = '\0';
    
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
