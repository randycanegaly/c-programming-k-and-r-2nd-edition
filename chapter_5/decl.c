#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAXTOKEN 100

enum { NAME, PARENS, BRACKETS };

int gettoken(void);
int tokentype;
char token[MAXTOKEN];
char name[MAXTOKEN];
char datatype[MAXTOKEN];
char out[1000];
int getch(void);
void ungetch(int c);
void dcl(void);
void dirdcl(void);

void main(void) {
    while (gettoken() != EOF) {
        strcpy(datatype, token);
        out[0] = '\0';
        dcl();
        if (tokentype != '\n')
            printf("syntax error\n");
        printf("%s: %s %s\n", name, out, datatype);
    }
}

int gettoken(void) {
    int c; 
    char *p = token; //p is a pointer to a char, the beginning element of the token array

    while ((c = getch()) == ' ' || c == '\t') //skip whitespace
         ; 
    if (c == '(') { //see a left paren
        if ((c = getch()) == ')') { //get the next char. is it the closing paren?
            strcpy(token, "()"); //saw a matching pair of parens, so that's the token. strcpy copies "()" into token
            return tokentype = PARENS; //returns a 1
        } else {
            ungetch(c); //oops, didn't see the matching paren, have to push the first one seen back into input
            return tokentype = '('; //the token seen is just one left paren
        }
    } else if (c == '[') { //saw a left bracket
        //advance the pointer one position
        //set the thing the pointer points to, to c
        //or, the next position in token now has c
        //keep advancing the pointer and getting the next input character 
        //and placing each input character into token
        //until hit a right bracket
        for (*p++ = c; (*p++ = getch()) != ']'; ) 
            ;
        *p = '\0'; //so at this point, token has whatever is between the brackets, terminate that string
        return tokentype = BRACKETS; //return a 2
    } else if (isalpha(c)) { //not whitespace nor parens nor brackets - name characters
        for ( *p++ = c; isalnum(c = getch()); ) //get characters, insert them in token while they are letters or numbers
            *p++ = c;
        *p = '\0'; //terminate when not seeing a letter or a number
        ungetch(c); //stopped seeing letter or number and went one past. put it back
        return tokentype = NAME; //have collected a name
    } else
        return tokentype = c; //seeing something else
}
#define BUFSIZE 100

char buf[BUFSIZE];
int bufp = 0;

int getch(void) {
    return (bufp > 0) ? buf[--bufp] : getchar();
}

void ungetch(int c) {
    if (bufp >= BUFSIZE)
        printf("ungetch: too many characters\n");
    else
        buf[bufp++] = c;
}

/* dcl: parse a declarator */
void dcl(void) {
    int ns;

    for (ns = 0; gettoken() == '*'; ) //count the *s
        ns++;
    dirdcl();
    while (ns-- > 0)
        strcat(out, " pointer to");
}

/* dirdcl: parse a direct declarator */
void dirdcl(void) {
    int type;

    if(tokentype == '(') {
        dcl();
        if (tokentype != ')')
            printf("error: missing )\n");
    } else if (tokentype == NAME)
        strcpy(name, token);
    else
        printf("error: expected name or (dcl)\n");
    while ((type = gettoken()) == PARENS || type == BRACKETS)
        if(type == PARENS)
            strcat(out, " function returning");
        else {
            strcat(out, " array");
            strcat(out, token);
            strcat(out, " of ");
        }
}
