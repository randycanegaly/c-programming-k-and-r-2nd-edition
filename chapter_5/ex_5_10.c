#include <stdio.h>
#include <stdlib.h> /*for atof */
#include <string.h>
#include <ctype.h>

#define MAXOP 100 /*max size for operand or operator */
#define NUMBER '0' /*signal that a number was found */

/* reverse polish calculator, changed to use command lines arguments 
 * design philosophy - only use push() and pop() to support main()
 * ditch getops, etc.
 */

void push(double);
double pop(void);

int main(int argc, char *argv[]) {//argv is an array of pointers to chars, each is the first char of a string
    double op2, temp1, temp2;
    int c, type;
    /*
     * walk argv[]. is next element a digit? If so, set its type to NUMBER and let the switch statement
     * handle it.
     * if it isn't a digit, it's an operator. set it to type and let the switch statement handle it
     *
     */


    while(--argc > 0) {//while there are still args
        *++argv;//advance pointer to next arg string. first one will skip the program name
        if (!isdigit(c = **argv) && strlen(*argv) == 1)//**argv means the thing that pointer to the pointer points to
            type = c;//making type the one character - an operator
        else
            type = NUMBER;

        switch(type) {
        case NUMBER:
            push(atof(*argv));//*argv - the thing that argv points to, a number string
            break;
        case '+':
            push(pop() + pop());
            break;
        case 'x':
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
        default:
            printf("error: bad command%c\n", type);
            argc = 1;//just assume bad command means that there were no valid commands and argv only has the program name 
            break;
        }
    }
    
    printf("answer:\t%.8g\n", pop());
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
