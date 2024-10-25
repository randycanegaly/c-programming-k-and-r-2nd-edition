#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

#define MAXWORD     100
#define MAXNODES    1000

/*Write a program that prints the distinct words in its input sorted into decreasing order of occurrence
 * Precede each word by its count.
*/

/* Implementation steps:
 * 1. count the number of occurences for words 
 */

struct tnode {
    char *word;
    int times;
    struct tnode *left;
    struct tnode *right;
};

struct tnode *nodes[MAXNODES];
int node_count = 0;

struct tnode *addtreex(struct tnode *, char *);
void nodestore(struct tnode *);
int getword(char *, int);
void nodesort();
void nodeprint();

int main(void) {
    struct tnode *root;
    char word[MAXWORD];
    int linenum = 1;

    root = NULL;
    while (getword(word, MAXWORD) != EOF) 
        if (isalpha(word[0])) 
            root = addtreex(root, word);
    nodestore(root);
    nodesort();
    nodeprint();
    return 0;
}

struct tnode *talloc(void);
void addtime(struct tnode *);

/* addtree: add a node with w, at or below p */
struct tnode *addtreex(struct tnode *p, char *w) {
    int cond;

    if (p == NULL) { //base case
        p = talloc();
        p->word = strdup(w);
        p->left = p->right = NULL;
        p->times = 1;
    } else if ((cond = strcmp(w, p->word)) == 0) //the word passed in matches this node's word, increment occurrences
        addtime(p);
    else if (cond < 0)
        p->left = addtreex(p->left, w);
    else
        p->right = addtreex(p->right, w);
    return p;
}

/* addtime: increment the occurrences for the word */
void addtime(struct tnode *p)
{
    ++p->times;
}

/* nodestore: dump the nodes into an array */ 
void nodestore(struct tnode *p)
{
    if (p != NULL) {
        nodestore(p->left);
        if (node_count < MAXNODES)
            nodes[node_count++] = p;            
        nodestore(p->right);
    }
}

/*nodesort: shell sort to put nodes in order by number of occurences */
void nodesort()
{
    int gap, i, j;
    struct tnode *temp;

    for (gap = node_count/2; gap > 0; gap /= 2)
        for (i = gap; i < node_count; i++)
            for (j = i-gap; j >= 0; j-=gap) {
                if ((nodes[j]->times) >= (nodes[j+gap]->times))
                        break;
                temp = nodes[j];
                nodes[j] = nodes[j+gap];
                nodes[j+gap] = temp;
            }
}

void nodeprint()
{
    int i;
    for (i = 0; i < node_count; i++)
        printf("%4d %10s\n", nodes[i]->times, nodes[i]->word); 
}

/* talloc: make a tnode */
struct tnode *talloc(void)
{
    return (struct tnode *) malloc(sizeof(struct tnode));
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

