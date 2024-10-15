#include <stdio.h>
#include <string.h>

/*modify the sort program to handle a -r flag to reverse
 * the output. Should work with the -n flag
 */

#define MAXLINES 5000
char *lineptr[MAXLINES]; /* max #lines to be sorted */

int readlines(char *lineptr[], int nlines);
void writelines(char *lineptr[], int nlines, int reverse);

void myqsort(void *lineptr[], int left, int right,
        int (*comp)(void *, void *));
int numcmp(char *, char *);

/* sort input lines */
int main(int argc, char *argv[]) {
    int nlines; /*number of input lines read*/
    int numeric = 0; /*1 if numeric sort */
    int reverse = 0; /*1 if sort in reverse order */
    
    if (argc == 2 && strcmp(argv[1], "-n") == 0) 
        numeric = 1;
    if (argc == 2 && strcmp(argv[1], "-r") == 0) 
        reverse = 1;

    if (argc == 3 && ((strcmp(argv[1], "-n") == 0) || (strcmp(argv[2], "-n") == 0)))
        numeric = 1;
    if (argc == 3 && ((strcmp(argv[1], "-r") == 0) || (strcmp(argv[2], "-r") == 0)))
        reverse = 1;

    if ((nlines = readlines(lineptr, MAXLINES)) > 0) {
        myqsort((void **) lineptr, 0, nlines-1,
                (int (*)(void*,void*))(numeric ? numcmp : strcmp));
        writelines(lineptr, nlines, reverse);
        return 0;
    } else {
        printf("error: input too big to sort\n");
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
void writelines(char *lineptr[], int nlines, int reverse) {
    int i;
   
    if (reverse) {
        lineptr += (nlines - 1);
        while (nlines-- > 0)
            printf("%s\n", *lineptr--);
    } else {
        while (nlines-- > 0)
            printf("%s\n", *lineptr++);
    }
}

/*qsort: sort v[left] ... v[right] into increasing order */
void myqsort(void *v[], int left, int right,
        int (*comp)(void *, void *)) {
    
    int i, last;
    //i = 0;

    void swap(void *v[], int, int);//declare here because will be used below before its definition
    
    if (left >= right) //base case
        return;
    swap(v, left, (left + right) / 2);
    last = left;
    for (i = left + 1; i <= right; i++)
        if ((*comp)(v[i], v[left]) < 0) 
            swap(v, ++last, i);
    swap(v, left, last);
    myqsort(v, left, last-1, comp);
    myqsort(v, last+1, right, comp);
}

/* swap: interchange v[i] and v[j] */
void swap(void *v[], int i, int j) {
    void *temp;

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

#include <stdlib.h>

int numcmp(char *s1, char *s2) {
    //printf("numeric\n");

    double v1, v2;
    v1 = atof(s1);
    v2 = atof(s2);
    if (v1 < v2)
        return -1;
    else if (v1 > v2)
        return 1;
    else
        return 0;
}
