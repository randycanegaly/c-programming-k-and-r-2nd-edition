#include <stdio.h>
#include <stdlib.h> /*for atof */

#define MAXOP 100 /*max size for operand or operator */
#define NUMBER '0' /*signal that a number was found */

int getop(char []);
void push(double);
double pop(void);

/* reverse polish calculator, modified to use sscanf to do the input and number conversion */
int main(void) {
    int type;
    double op2;
    char s[MAXOP];//allocates storage for a string of length 100

    while((type = getop(s)) != EOF) {
        switch(type) {
        case NUMBER:
            push(atof(s));
            break;
        case '+':
            push(pop() + pop());
            break;
        case '*':
            push(pop() * pop());
            break;
        case '-':
            op2 = pop();
            push(pop() - op2);
            break;
        case '/':
            op2 = pop();
            if (op2 != 0.0)
                push(pop() / op2);
            else
                printf("error: dividing by zero");
            break;
        case '\n':
            printf("\t%.8g\n", pop());
            break;
        default:
            printf("error: bad command%s\n", s);
            break;
        }
    }
    return 0;
}

#define MAXVAL 100 /*maximum depth of val stack */

int sp = 0; /*next free stack position */
double val[MAXVAL]; /*value stack*/

/* push: push f onto the stack */
void push(double f) {
    if (sp < MAXVAL)
        val[sp++] = f;
    else
        printf("error: stack full, can't push %g\n", f);
}

/* pop: pop and return value at the top of the stack */
double pop(void) {
    if (sp > 0)
        return val[--sp];
    else {
        printf("error: stack empty\n");
        return 0.0;
    }
}

#include <ctype.h>

int getch(void);
void ungetch(int);

/*getop: get next operator or numeric operand */
int getop(char s[]) {
    int i, rc;
    char c;
    static char lastc[] = " ";//a string to keep track of last character seen
    sscanf(lastc, "%c", &c);//sets c to a blank 
    lastc[0] = ' ';
    while ((s[0] = c) == ' ' || c == '\t')//this loop runs doing nothing but checking for EOF until c gets set to a non-blank character
        if (scanf("%c", &c) == EOF) //scanf detected end of file
            c = EOF;
    s[1] = '\0';//terminate s so we have a string with only that first non-blank character
    if(!isdigit(c) && c != '.')
        return c;//return an operator, EOF would get returned here
    i = 0;//reset i pointer to front of s, points to that first non-blank character found
    if (isdigit(c)) //collect following digits and set them in s, starting at the one after the first non-blank character found
        do {
            rc = scanf("%c", &c);//grabs the next character from input
            if (!isdigit(s[++i] == c))//set the character to the next element in s, if it's not a digit, break out of the do-while loop
                break;
        } while (rc != EOF);//if the character we saw is EOF, stop grabbing characters from input
    if (c == '.')//so we have broken out of building number because we hit something not-digit, is it the decimal point we might expect?
        do {
            rc = scanf("%c", &c);//grabs the next character from input
            if (!isdigit(s[++i] == c))//set the character to the next element in s, if it's not a digit, break out of the do-while loop
                break;
        } while (rc != EOF);//now gather digits to the right of the decimal point
    s[i] = '\0';//terminate s, we have a number
    if (rc != EOF)
        lastc[0] = c;//remember the last character seen
    return NUMBER;
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

