#include <ctype.h>
#include <stdio.h>

int getch(void);
void ungetch(int);

#define SIZE 80

/*Write getfloat, starting with getint. What type does getfloat return?
getfloat still returns an int because the return value is the signal to the caller about what was found */

int main(void) {
    int n, getfloat(float *);
    float array[SIZE];

    for (n = 0; n < SIZE && getfloat(&array[n]) != EOF; n++)
		printf("array[%d] = %f\n", n, array[n]);
}

/* getfloat: get next integer from input into *pn */
int getfloat(float *pn) {
    
    int c, sign;
    float power;

    while(isspace(c = getch())) //skipping whitespace
        ;

    
    if ( !isdigit(c) && c != EOF && c != '+' && c != '-') {
        ungetch(c);
        return 0; 
    }

    sign = (c == '-') ? -1 : 1;
    if (c == '+' || c == '-')
        c = getch();

    for (*pn = 0; isdigit(c); c = getch())
        *pn = 10 * *pn + (c -'0');
 
    if (c == '.')//see a decimal point, get the character after that
        c = getch();

    //walk the characters after '.', build up the fractional part digits
    //keep track of the power variable - 10 ** number of digits after '.'
    for (power = 1.0; isdigit(c); c = getch()) {
        *pn = 10 * *pn + (c -'0');//shift 'old' digits left one position and add numeric value of 'this' character
        power *= 10;//for every digit found raise power by 10 times. 123.456 will yield power = 1000 
    }

    *pn *= sign / power;

    if (c != EOF)
        ungetch(c);
    
    return c;
}


#define BUFSIZE 100 
char buf[BUFSIZE];/* buffer for ungetch() */ 
int bufp = 0; /* next free positionin buf */ 

int getch(void) { 
    return (bufp > 0) ? buf[--bufp] : getchar(); 
} 

void ungetch(int c) { 
    if (bufp  >= BUFSIZE) 
        printf("ungetch: too many characters"); 
    else  
        buf[bufp++] = c; 
}
