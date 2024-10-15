#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/*
 * Starting with the code from pages 108 to 110 - use the alloc storage
 * approach below
 * write a program "tail" which prints the last n lines of its input
 * default n = 10
 * but tail -n will change the number of lines when passed as a 
 * command line argument
 *
 */

#define MAXLINES 5000
#define DEFAULTLINES 10

char *lineptr[MAXLINES]; /* max #lines to be sorted lineptr is where all the lines are stored*/

int readlines(char *lineptr[], int nlines);
void writelines(char *lineptr[], int nlines, int tail_lines);

/* sort input lines */
int main(int argc, char *argv[]) {
    int nlines, tail_lines; /*number of input lines read and number of tail lines to print out*/
    
    if(argc == 1)
        tail_lines = 10;
    else if (argc > 2) {
        printf("Usage: \"tail -n\"\n");
        return 1;
    } else 
        tail_lines = atoi(++argv[1]);
        
    if ((nlines = readlines(lineptr, MAXLINES)) >= 0) {
        writelines(lineptr, nlines, tail_lines);
        return 0;
    } else {
        printf("error: input too big\n");
        return 1;
    }
}

#define MAXLEN 1000 /* max length of any input line */
int mygetline(char *, int);
char *alloc(int); //provides a block of memory of the requested size
void afree(char *p);//free the storage pointed to by p

/*readlines: read input lines */
int readlines(char *lineptr[], int maxlines) {
    int len, nlines;
    char *p, line[MAXLEN];

    nlines = 0;
    while ((len = mygetline(line, MAXLEN)) > 0)
        if (nlines >= maxlines || (p = alloc(len)) == NULL)
            return -1;
        else {
            line[len-1] = '\0'; /* delete newline */
            strcpy(p, line);
            lineptr[nlines++] = p;
        }
     
    return nlines;
}

/* writelines: write output lines */
void writelines(char *lineptr[], int nlines, int tail_lines) {
    int i, back;

    //start at the tail_linesth element from the end of lintptr
    if ( tail_lines >= nlines )
        i = 0;
    else
        i = nlines - tail_lines;

    for (; i < nlines; i++) {
        printf("%s\n", lineptr[i]);
    }
}

/* getline: read a line into s, return length */
int mygetline(char s[], int lim) {
    int c, i;

    for (i=0; i<lim-1 && (c=getchar()) != EOF && c!='\n'; ++i)
        s[i] = c;
    if (c == '\n') {
        s[i] = c;
        ++i;
    }
    s[i] = '\0';
    return i;
}

#define ALLOCSIZE 1000

static char allocbuf[ALLOCSIZE];
static char *allocp = allocbuf;

char *alloc(int n) {
    if (allocbuf + ALLOCSIZE - allocp >= n) { //it fits
        allocp += n;
        return allocp - n;
    } else
        return 0;
}

void afree(char *p) {//put the alloc pointer back to the start of the block allocated for p - "put storage back"
    if (p >= allocbuf && p < allocbuf + ALLOCSIZE)
        allocp = p;
}
