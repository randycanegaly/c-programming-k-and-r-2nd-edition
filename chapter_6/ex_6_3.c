#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

#define MAXWORD 100

/*
Write a cross referencer that prints a list of all words in a document
and for each word prints a list of the line numbers that occurs on.
Remove noise words like "the", "and", etc.
*/

struct linkedlist {
    int lnum;
    struct linkedlist *next;
};

struct tnode {
    char *word;
    struct linkedlist *lines;
    struct tnode *left;
    struct tnode *right;
};

struct tnode *addtreex(struct tnode *, char *, int);
void treexprint(struct tnode *);
int getword(char *, int);
int noiseword(char *);

int main(void) {
    struct tnode *root;
    char word[MAXWORD];
    int linenum = 1;

    root = NULL;
    while (getword(word, MAXWORD) != EOF) 
        if (isalpha(word[0]) && noiseword(word) == -1) 
            root = addtreex(root, word, linenum);
        else if (word[0] == '\n') {
            linenum++;
        }
    
    treexprint(root);
    return 0;
}

struct tnode *talloc(void);
struct linkedlist *lalloc(void);
void addln(struct tnode *, int);

/* addtree: add a node with w, at or below p */
struct tnode *addtreex(struct tnode *p, char *w, int linenum) {
    int cond;

    if (p == NULL) { //base case
        p = talloc();
        p->word = strdup(w);
        p->left = p->right = NULL;
        p->lines = lalloc();
        p->lines->next = NULL;
        p->lines->lnum = linenum;
    } else if ((cond = strcmp(w, p->word)) == 0) //the word passed in matches this node's word, increment line number
        addln(p, linenum);
    else if (cond < 0)
        p->left = addtreex(p->left, w, linenum);
    else
        p->right = addtreex(p->right, w, linenum);
    return p;
}

/* addln: add a line number to the linked list */
void addln(struct tnode *p, int linenum)
{
    struct linkedlist *temp;
    temp = p->lines; //temp also points to lines so that any changes made with temp will apply to lines
    while(temp->next != NULL && temp->lnum != linenum) //walk the linked list. stop if hit the end (NULL) or if linenum is already there
        temp = temp->next;
    
    //if reached the end, set lnum in temp to linenum, do nothing if linenum is already there
    if(temp->lnum != linenum) { //new line number to enter 
        temp->next = lalloc();
        temp->next->lnum = linenum;
        temp->next->next = NULL;//to indicate that this is now the end of the linkedlist
    }
}

/* treexprint: in-order print of tree p */
void treexprint(struct tnode *p)
{
    struct linkedlist *temp; 

    if (p != NULL) {
        treexprint(p->left);
        printf("%10s ", p->word);
        for (temp = p->lines; temp != NULL; temp = temp->next)
            printf("%4d ", temp->lnum);
        printf("\n");
        treexprint(p->right);
    }
}

/* talloc: make a tnode */
struct tnode *talloc(void)
{
    return (struct tnode *) malloc(sizeof(struct tnode));
}

/* lalloc: make a tnode */
struct linkedlist *lalloc(void)
{
    return (struct linkedlist *) malloc(sizeof(struct linkedlist));
}

/* getword: get next word or character from input */
int getword(char *word, int lim) {
    int c, getch(void);
    void ungetch(int);
    char *w = word;

    while (isspace(c = getch()) && c != '\n')
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

/* noiseword: identify a word as a noiseword */
int noiseword(char *w)
{
    static char *nw[] = {"a", "am", "an", "and", "are", "in", "is", "of", "or", "that", "the", "this", "to"};
    int cond, mid;
    int low = 0;
    int high = sizeof(nw) / sizeof(char *) - 1;

    while(low <= high) {
        mid = (low + high) / 2;
        if((cond = strcmp(w, nw[mid])) < 0)
            high = mid - 1;
        else if (cond > 0)
            low = mid + 1;
        else
            return mid;
    }
    return -1;
}
