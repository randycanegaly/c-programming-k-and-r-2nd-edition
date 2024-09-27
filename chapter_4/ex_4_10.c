#include <stdio.h>
#include <stdlib.h> /*for atof */

#define MAXOP 100 /*max size for operand or operator */
#define NUMBER '0' /*signal that a number was found */

int getop(char []);
void push(double);
double pop(void);

/* reverse polish calculator */
/* use getline to read an entire line. Modify to not use getch or ungetch */:w

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

int getch(void);
void ungetch(int);
int mygetline(char s[], int lim);

//getop gets called multiple times when processing an input
//so need a walker variable external to getop to track where we are in the input line
int lw;

/*getop: get next operator or numeric operand */
int getop(char s[]) {//when something (number or operator or newline) is found put it in s for the caller to use
    //get an entire line and then process it for operators and operands 
    char line[MAXOP];
    mygetline(line, MAXOP);
    
    int i, c;

    //line now has the whole math equation like "3 4 +"
    //walk that line and look for:
    //  white space
    //  operators
    //  left digits
    //  decimal places
    //  right digits
    
    //process line for whitespace
    while((c = line[lw++]) = ' ' || c == '\t') 
        ;

    if(!isdigit(c) && c != '.')
        return c;//send an operator signal to the caller
    lw++;
    
    i = 0; 
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

/* read an input line into s, return its length */
int mygetline(char s[], int lim) {
    int c, i;

    for (i=0; i<lim-1 && (c = getchar()) != EOF && c!='\n'; ++i) {
        s[i] = c;
    }

    if (c == '\n') {
        s[i] = c;
        ++i;
    }
    s[i] = '\0';
    return i-1;
}

/*
#define BUFSIZE 100
char buf[BUFSIZE];
int bufp = 0; 

int getch(void) {
    return (bufp > 0) ? buf[--bufp] : getchar();
}

void ungetch(int c) {
    if (bufp  >= BUFSIZE)
        printf("ungetch: too many characters");
    else 
        buf[bufp++] = c;
}
*/
