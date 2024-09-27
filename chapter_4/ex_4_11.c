#include <stdio.h>
#include <stdlib.h> /*for atof */

/* use a static variable so that getop() doesn't have to use
* ungetch() */

#define MAXOP 100 /*max size for operand or operator */
#define NUMBER '0' /*signal that a number was found */

int getop(char []);
void push(double);
double pop(void);

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
#define BUFSIZE 100

int getch(void);

/*getop: get next operator or numeric operand 
modify it to not have to use ungetch 
use static variables
assume one character of pushback
*/


int getop(char s[]) {
    int i, c;
    static int last = 0;

    if (last == 0)//no last character
        c = getch();
    else {
        c = last;
        last = 0; 
    }

    while((s[0] = c) == ' ' || c == '\t')//if c is whitespace, get the next char and do nothing
        c = getch();//when done, s[0] will have a whitespace character
    s[1] = '\0';//make that a real string with a terminator
    if(!isdigit(c) && c != '.')
        return c;//return an operator
    i = 0;
    if (isdigit(c)) /*gather up an integer part */
        while (isdigit(s[++i] = c = getch()))
                ;
    if (c == '.')
        while (isdigit(s[++i] = c = getch()))
            ;
    s[i] = '\0';
    if (c != EOF)
        last = c;
    return NUMBER;
}


int getch(void) {
    return getchar();    
}


