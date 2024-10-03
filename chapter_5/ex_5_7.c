#include <stdio.h>
#include <string.h>

#define MAXLINES 5000
#define MAXLEN 1000 /* max length of any input line */
#define MAXSTOR 5000 /*size of available storage space */

/* change readlines to use an array provided by main rather than an alloc() within readlines */


char *lineptr[MAXLINES]; /* max #lines to be sorted */
char linestor[MAXSTOR];
int readlines(char *lineptr[], char *linestor, int nlines);
void writelines(char *lineptr[], int nlines);

void qsort(char *lineptr[], int left, int right);

/* sort input lines */
int main(void) {
    int nlines; /*number of input lines read*/

    if ((nlines = readlines(lineptr, linestor, MAXLINES)) > 0) {
        qsort(lineptr, 0, nlines-1);
        writelines(lineptr, nlines);
        return 0;
    } else {
        printf("error: input too big to sort\n");
        return 1;
    }
}


int mygetline(char *, int);
//char *alloc(int); //provides a block of memory of the requested size
//void afree(char *p);//free the storage pointed to by p

/*readlines: read input lines */
int readlines(char *lineptr[],  char *linestor, int maxlines) {
    int len, nlines;
    char line[MAXLEN];//array to take 'this' line
    char *p = linestor;//points to first element in linestor    
    char *linestop = linestor + MAXSTOR;//points to the end of linestor

    nlines = 0;
    while ((len = mygetline(line, MAXLEN)) > 0)
        if (nlines >= maxlines || p+len > linestop)//adding the line to linestor would exceed linestor's capacity
            return -1;
        else {
            line[len-1] = '\0'; /* delete newline */
            strcpy(p, line);
            lineptr[nlines++] = p;
            p += len;//advance the pointer to next open area of linestor
        }
     
    return nlines;
}

/* writelines: write output lines */
void writelines(char *lineptr[], int nlines) {
    int i;

    while (nlines-- > 0)
        printf("%s\n", *lineptr++);
}

/*qsort: sort v[left] ... v[right] into increasing order */
void qsort(char *v[], int left, int right) {//v is an array of pointers to chars, each
    //element is a pointer to the first character in an array
    int i, last;
    i = 0;

    void swap(char *v[], int i, int j);//declare here because will be used below before its definition
    
    if (left >= right) //base case
        return;
    swap(v, left, (left + right) / 2);
    last = left;
    for (i = left + i; i <= right; i++)
        if (strcmp(v[i], v[left]) < 0) 
            swap(v, ++last, i);
    swap(v, left, last);
    qsort(v, left, last-1);
    qsort(v, last+1, right);
}

/* swap: interchange v[i] and v[j] */
void swap(char *v[], int i, int j) {
    char *temp;

    temp = v[i];
    v[i] = v[j];
    v[j] = temp;
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
