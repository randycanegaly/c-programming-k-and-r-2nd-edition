#include <stdio.h>
#include <stdlib.h> /*for atof */
#include <math.h> /* for sin, cos, exp and pow */
#include <string.h> /* for strcmp() */
#define MAXOP 100 /*max size for operand or operator */
#define NUMBER '0' /*signal that a number was found */
#define NAME 'z' /*signal that a string NAME was built */

/* add support for sin, cos, exp and pow */
int getop(char []);
void push(double);
double pop(void);
void maths(char []);

/* reverse polish calculator */
int main(void) {
    int type;
    double op2;
    char s[MAXOP];

    while((type = getop(s)) != EOF) {
        switch(type) {
        case NUMBER:
            push(atof(s));
            break;
        case NAME://see the name signal, assume it's the name of a math function
            maths(s);//getops modifies s, so that's what needs passed to maths
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

/*maths: string parameter is a math function name
 * call a matching math function from math.h
 * I will restrict this to sin, cos, exp and pow
 * pop a value as the operand for the math function */
void maths(char s[]) {
    double op2;

    if (strcmp(s, "sin") == 0)
        push(sin(pop()));
    if (strcmp(s, "cos") == 0)
        push(cos(pop()));
    if (strcmp(s, "exp") == 0)
        push(exp(pop()));
    if (strcmp(s, "pow") == 0) {
        op2 = pop();
        push(pow(pop(), op2));
    }
}

#include <ctype.h>

int getch(void);
void ungetch(int);

/*getop: get next operator or numeric operand */
int getop(char s[]) {
    int i, c;

    while((s[0] = c = getch()) == ' ' || c == '\t')
        ;
    s[1] = '\0';
    i = 0;
    
    /*the case where a string name is being entered */
    if (islower(c)) {
        //printf("in islower: %c\n", c);
        while(islower(s[++i] = c = getch()))
            ;
        //now looking at a c that is not a lower case letter
        s[i] = '\0';//terminate that string we collected
        if (c != EOF)//have gone one too far, have to put it back
            ungetch(c);
        //now have a name string
        if (strlen(s) > 0)//check that it's not just one character - would be a regular one letter command
            return NAME;
        else
            return c;//the one letter command mentioned above
    }

    if (!isdigit (c) && c != '.')
        return c;//a single letter command

    if (isdigit(c)) /*gather up an integer part */
        while (isdigit(s[++i] = c = getch()))
                ;
    if (c == '.')
        while (isdigit(s[++i] = c = getch()))
            ;
    s[i] = '\0';
    if (c != EOF)
        ungetch(c);
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
