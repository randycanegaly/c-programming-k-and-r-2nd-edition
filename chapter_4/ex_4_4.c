#include <stdio.h>
#include <stdlib.h> /*for atof */

#define MAXOP 100 /*max size for operand or operator */
#define NUMBER '0' /*signal that a number was found */
#define COMMAND 'c' /*signal that a COMMAND was found */

int getop(char []);
void push(double);
double pop(void);
void clear(void);

/* reverse polish calculator */
int main(void) {
    int type;
    double op2, temp1, temp2;
    char s[MAXOP];

    while((type = getop(s)) != EOF) {
        switch(type) {
        case NUMBER:
            //printf("NUMBER case.\n");
            push(atof(s));
            break;
        case '+':
            //printf("+ case.\n");
            push(pop() + pop());
            break;
        case '*':
            //printf("* case.\n");
            push(pop() * pop());
            break;
        case '-':
            //printf("- case.\n");
            op2 = pop();
            push(pop() - op2);
            break;
        case '/':
            //printf("/ case.\n");
            op2 = pop();
            if (op2 != 0.0)
                push(pop() / op2);
            else
                printf("error: dividing by zero\n");
            break;
        case '%':
            //printf("percent case.\n");
            op2 = pop();
            push((int) pop() % (int) op2);
            break;
        case 'p'://print the top item on the stack without removing it
            op2 = pop();
            printf("%f\n", op2);
            push(op2);
            break;
        case 'd'://duplicate the top two elements on the stack
            op2 = pop();
            push(op2);
            push(op2);
            break;
        case 's'://swap the top to items on the stack
            temp1 = pop();
            temp2 = pop();
            push(temp1);
            push(temp2);
            break;
        case 'c'://clear the stack
            clear();
            break;
        case '\n':
            //printf("n case.\n");
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

/* reset the stack pointer to "clear" the stack */
void clear(void) {
    sp = 0;
}

#include <ctype.h>

int getch(void);
void ungetch(int);

/*getop: get next operator or numeric operand */
int getop(char s[]) {
    int i, c;

    while ((s[0] = c = getch()) == ' ' || c == '\t')
        ;
    s[1] = '\0';//TO DO - what? At this point have a non-whitespace char in s[0], put terminator in s[1]
    //so we have a legitimate strint to begin with
    /*if (isalpha(c)) {//build up a string of consecutive letters
        while (isalpha(s[i++] = c = getch()))
            ;
        s[i] = '\0';
        if (c != EOF)
            ungetch(c);
        return COMMAND;
    }*/
        
    if (!isdigit(c) && c != '.')
        return c;//return an operator
    i = 0;
    if (isdigit(c)) //gather up an integer part
        while (isdigit(s[++i] = c = getch()))
                ;
    if (c == '.')//gather up digits for the rational part
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

