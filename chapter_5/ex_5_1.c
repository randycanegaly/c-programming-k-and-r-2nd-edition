#include <ctype.h>
#include <stdio.h>

int getch(void);
void ungetch(int);
//int getint(int *pn);

#define SIZE 80

/*As written, getint treats a + or - not followed by a digit as valid representation of zero. Fix
* it to push such a character back onto the input
*/

int main(void) {
    int n, val, array[SIZE], getint(int *);

    //for (n = 0; n < SIZE && getint(&array[n]) != EOF; n++)
     //   ;
    for (n = 0; n < SIZE && (val = getint(&array[n])) != EOF; n++)
		printf("array[%d] = %d\n", n, array[n]);
}

/* getint: get next integer from input into *pn */
int getint(int *pn) {
    
    int c, d, sign;

    while(isspace(c = getch())) //skipping whitespace
        ;

    
    if ( !isdigit(c) && c != EOF && c != '+' && c != '-') {
        ungetch(c);
        return 0; 
    }

    sign = (c == '-') ? -1 : 1;
    
    /* catch the case where a + or - is seen and followed by a non-digit character */
    if (c == '+' || c == '-') {
        //caught a + or -
        d = c;//remember it
        //check the next character. if not a digit, push it back
        if (!isdigit(c = getch())) {
            if (c != EOF)
                ungetch(c);//push back the non-digit character after + or -
            ungetch(d);//push back the + or -n
            return d;
        }  
    }

    if (c == '+' || c == '-')
        c = getch();

    for (*pn = 0; isdigit(c); c = getch())
        *pn = 10 * *pn + (c -'0');
 
    *pn *= sign;

    if (c != EOF)
        
    
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
