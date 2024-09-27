/* Couldn't get this one.
* this solution is from Franz Fritsche
* https://clc-wiki.net/wiki/K%26R2_solutions:Chapter_4:Exercise_10
*/

#include <stdio.h>
#include <stdlib.h>

#define MAXOP    100  /* max size of operand or operator */
#define NUMBER   '0'  /* signal that a number was found */
#define MAXLINE 1000

int getop(char []);
void push(double);
double pop(void);
int mygetline(char [], int);

char line[MAXLINE];
int line_i;

/* reverse Polish calculator */
int main(void)
{
    int type;
    double op2;
    char s[MAXOP];

    while (mygetline(line, MAXLINE) != 0)
    {
        line_i = 0;
        while ((type = getop(s)) != '\0')
        {
            switch (type)
            {
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
                        printf("error: zero divisor\n");
                    break;
                case '\n':
                    printf("\t%.8g\n", pop());
                    break;
                default:
                    printf("error: unknown command \'%s\'\n", s);
                    break;
            }
        }
    }
    
    return 0;
}

#define MAXVAL   100  /* maximum depth of val stack */

int sp = 0;           /* next free stack position */
double val[MAXVAL];   /* value stack */

/* push:  push f onto value stack */
void push(double f)
{
    if (sp < MAXVAL)
        val[sp++] = f;
    else
        printf("error: stack full, can't push %g\n", f);
}

/* pop:  pop and return top value from stack */
double pop(void)
{
    if (sp > 0)
        return val[--sp];
    else
        printf("error: stack empty\n");

    return 0.0;
}

/* mygetline:  get line into s, return length */
int mygetline(char s[], int lim)
{
    int c, i;

    i = 0;
    while (--lim > 0 && (c = getchar()) != EOF && c != '\n')
        s[i++] = c;
    if (c == '\n')
        s[i++] = c;
    s[i] = '\0';

    return i;
}

#include <ctype.h>

/* getop:  get next character or numeric operand */
int getop(char s[])
{
    int i, c;

    while ((s[0] = c = line[line_i++]) == ' ' || c == '\t')
        ;
    s[1] = '\0';
    if (!isdigit(c) && c != '.')
        return c;      /* not a number */
    i = 0;
    if (isdigit(c))    /* collect integer part */
        while (isdigit(s[++i] = c = line[line_i++]))
            ;
    if (c == '.')      /* collect fraction part */
        while (isdigit(s[++i] = c = line[line_i++]))
              ;
    s[i] = '\0';
    line_i--;

    return NUMBER;
}
