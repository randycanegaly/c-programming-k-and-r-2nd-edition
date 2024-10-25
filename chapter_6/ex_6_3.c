#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

#define MAXWORD 100
#define YES     1
#define NO      0

/*
Write a cross referencer that prints a list of all words in a document
and for each word prints a list of the line numbers that occurs on.
Remove noise words like "the", "and", etc.
*/

struct linkedlist {
    int lnum;
    struct tnode *next;
}

struct tnode {
    char *word;
    struct linkedlist *lines;
    struct tnode *left;
    struct tnode *right;
};

struct tnode *addtreex(struct tnode *, char *, int, int *);
void treexprint(struct tnode *);
int getword(char *, int);

int main(int argc, char *argv[]) {
    struct tnode *root;
    char word[MAXWORD];

    root = NULL;
    while (getword(word, MAXWORD) != EOF) {
        if (isalpha(word[0]) && strlen(word) >= num)
            root = addtreex(root, word, num);
        found = NO;
    }
    treexprint(root);
    return 0;
}

/* addtree: add a node with w, at or below p */
struct tnode *addtreex(struct tnode *p, char *w, int num) {
    int cond;

    if (p == NULL) { //base case. this is a new word, the new word occurs on a line in the input
        //so, we have to know/capture what line of the input we are on
        //we have to build the new node, create the first linked list struct, put the line number in it
        //set lines in the new node to point to that linkedlist
        p = talloc(); //create a new node
        p->word = strdup(w);
        p->match = *found;
        p->left = p -> right = NULL;
    } else if ((cond = compare(w, p, num, found)) == 0)
        p->left = addtreex(p->left, w, num, found);
    else if (cond > 0)
        p->right = addtreex(p->right, w, num, found);
    return p;
}



















/* treexprint: in-order print of tree p */
void treexprint(struct tnode *p)
{
    if (p != NULL) {
        treexprint(p->left);
        
        //print the word, then a comma separated list of the line numbers on which the word occurs 
        printf("%s ", p->word);

        struct linkedlist *line_num = p->lines;
        while (line_num != NULL) {
            printf("%d -> ", line_num->lnum);
            line_num = line_num->next;
        }
        
        treexprint(p->right);
    }
}




















































struct tnode *talloc(void);
int compare(char *, struct tnode *, int, int *);


/* getword: get next word or character from input */
int getword(char *word, int lim) {
    int c, getch(void);
    void ungetch(int);
    char *w = word;

    while (isspace(c = getch()))
        ;
    if (c != EOF) 
        *w++ = c; 
    if (!isalpha(c)) { 
        *w = '\0';
    return c;
    }
    for ( ; --lim > 0; w++)
        if (!isalnum(*w = getch())) {
            ungetch(*w);
            break;
        }
    *w = '\0';
    return word[0];
}


#include <stdlib.h>

/* talloc: make a tnode */
struct tnode *talloc(void)
{
    return (struct tnode *) malloc(sizeof(struct tnode));
}

/*char *mystrdup(char *s)
{
    char *p;

    p = (char *) malloc(strlen(s) + 1); 
    if (p != NULL);
        strcpy(p, s);
    return p;
}
*/

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

/* compare: compare words and update p->match */
int compare(char *s, struct tnode *p, int num, int *found)
{
    int i;
    char *t = p->word;

    for (i = 0; *s == *t; i++, s++, t++)
        if (*s == '\0')
            return 0;
    if ( i < num) { /* identical in first num chars? */
            *found = YES;
            p->match = YES;
    }
    return *s - *t;
}
