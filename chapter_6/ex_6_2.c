#include <stdio.h>
#include <ctype.h>
#include <string.h>

#define MAXWORD 100

/*
 Write a program that reads a C program and prints in 
 alphabetical order each group of variable names that are 
 identical in the first 6 characters, but differ somewhat 
 thereafter. Don't count words within strings and comments.
 Make 6 a parameter that can be set from the command line.
 */

/*
1. Identify type variable grouping
2. Pull out the variable
3. Run tree as is but making word the variable pulled
4. Modify addtree so that it will only compare the first 6 characters
    when making comparisons
5. Change to take "6" from the command line 
*/


/*
 *How to find groups of variable names? They will be at the start of a line,
 in a declaration of the form - type variable
 Pick a few types to work with:
 char
 int
 float
 First, collect simple, identical character names
 Where would such code go? in main() AA
 * 
*/






struct tnode *addtree(struct tnode *, char *);
void treeprint(struct tnode *);
int getword(char *, int);

struct tnode {
    char *word;
    int count;
    struct tnode *left;
    struct tnode *right;
};

/* word frequency count */
int main(void) {
    struct tnode *root;
    char word[MAXWORD];

    root = NULL;
    while (getword(word, MAXWORD) != EOF) {
        if (isalpha(word[0]))
            root = addtree(root, word);
    }
    treeprint(root);
    return 0;
}

struct tnode *talloc(void);
char *mystrdup(char *);

/* addtree: add a node with w, at or below p */
struct tnode *addtree(struct tnode *p, char *w) {
    int cond;

    if (p == NULL) { //base case. this is a new word
        p = talloc(); //create a new node
        p->word = mystrdup(w);
        p->count = 1;
        p->left = p -> right = NULL;
    } else if ((cond = strcmp(w, p->word)) ==0)
        p->count++;
    else if (cond < 0)
        p->left = addtree(p->left, w);
    else
        p->right = addtree(p->right, w);
    return p;
}

/* getword: get next word or character from input */
int getword(char *word, int lim) {
    int c, getch(void);
    void ungetch(int);//going to use these two functions in here, have to declare them first
    char *w = word;

    while (isspace(c = getch())) //skip white space
        ;
    if (c != EOF) //not a space and not end of file
        *w++ = c; //* and ++ have equal precedence and associate right to left. increment w pointer to next character, assign c to what the pointer points to
    if (!isalpha(c)) { //if c is not an alpha, terminate the w string, return that character
        *w = '\0';
    return c;
    }
    for ( ; --lim > 0; w++) //walk the word up to the limit
        if (!isalnum(*w = getch())) { //get the next character, if it's not an alpha or number, push that too far character back
            ungetch(*w);
            break;
        }
    *w = '\0'; //past the end of the word, terminate the string
    return word[0];
}

/* treeprint: in-order print of tree p */
void treeprint(struct tnode *p)
{
    if (p != NULL) {
        treeprint(p->left);
        printf("%4d %s\n", p->count, p->word);
        treeprint(p->right);
    }
}

#include <stdlib.h>

/* talloc: make a tnode */
struct tnode *talloc(void)
{
    return (struct tnode *) malloc(sizeof(struct tnode));
}

char *mystrdup(char *s)
{
    char *p;

    p = (char *) malloc(strlen(s) + 1); /* +1 for the ending '\0' */
    if (p != NULL);
        strcpy(p, s);
    return p;
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
