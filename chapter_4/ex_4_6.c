#include <stdio.h>
#include <stdlib.h> /*for atof */

#define MAXOP 100 /*max size for operand or operator */
#define NUMBER '0' /*signal that a number was found */

/* handle variables
 * make an array for 26 variables corresponding to A-Z
 * add '=' operator that will assign a value to a variable
 *  by putting the value a at the variableth position in the array
 * in the default switch case, if you see a variable, pull the variableth value out of the array
 * and push it onto the stack
 * also, in the default switch case, if you see a 'v', push the value of 'v' onto the stacl
 * in the newline switch case, assign the popped top of stack value to 'v' and then print it
 *  so that v always holds the last value printed
*/

int getop(char []);
void push(double);
double pop(void);

/* reverse polish calculator */
int main(void) {
    int i, type, var;
    var = 0;
    double op2, v;
    char s[MAXOP];
    double variable[26];//the 26 A-Z variables
    
    for (i = 0; i < 26; i++)
        variable[i] = 0.0;
    
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
        case '=':
            //since we would have just seen an 'A-Z', that would have pushed the 'old'
            //Ath element of variables onto the stack
            //we are doing a new assignment to A, need to throw the old one away
            //so, pop()
            //printf("in ="); 
            pop();
            //the top of the stack now has the operand for '='
            //pop it and push it into the Ath position in variables
            //var now has the last type seen -- A 
            if (var >= 'A' && var <= 'Z')
                variable[var - 'A'] = pop();//var - 'A' gets the A-relative index into variables. 'B' would yield index 1
            else
                printf("error: no variable name\n");
            break;
        case '\n':
            //set v to be what is about to be the last thing printed out
            v = pop();
            printf("\t%.8g\n", v);//having remembered in v the last thing to be printed, print it
            break;
        default:
            if(type >= 'A' && type <= 'Z')//we see a variable, get that value out of variables and push it
                push(variable[type - 'A']);
            else if (type == 'v')//if we see v, we want to use the last thing printed, so push it
                push(v);
            else//otherwise we don't know what is going on, so punt
                printf("error: bad command%s\n", s);
            break;
        }

        var = type;//at the end of every loop iteration, set var equal to the type last seen
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
        //printf("error: stack empty\n");
        return 0.0;
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
    s[1] = '\0';//TO DO - what?
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

