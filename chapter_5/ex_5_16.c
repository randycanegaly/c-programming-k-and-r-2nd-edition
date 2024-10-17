#include <stdio.h>
#include <ctype.h>
#include <string.h>

/*Add the -d ("directory order") option, which makes comparisons only on letters, numbers and blanks. 
 * Make sure it works in conjunction with -f
 */

#define NUMERIC 1 //numeric sort
#define DECR    2 //sort in decreasing order
#define FOLD    4 //fold upper and lower cases
#define DORDER  8 //directory order
#define LINES   100 //max # of lines to be sorted

int charcmp(char *, char *);
int numcmp(char *, char *);
int readlines(char *lineptr[], int maxlines);
void myqsort(void *v[], int left, int right,
        int (*comp) (void *, void *));
void writelines(char *lineptr[], int nlines, int order);

static char option = 0;//static here means that this variable is only visible within this file

/* sort input lines */
int main(int argc, char *argv[]) {
    char *lineptr[LINES]; //array of pointers to chars. pointers to the first character
    //in each command line string
    int nlines; /*number of input lines read*/
    int c, rc = 0;

    while (--argc > 0 && (*++argv)[0] == '-') //walk down the array of pointers to the command line strings
        while (c = *++argv[0])//walking along the command line string, haven't hit '\0' yet
            switch (c) {
                case 'd'://directory order
                    option |= DORDER;
                    break;
                case 'f'://fold upper and lower cases
                    option |= FOLD;
                    break;
                case 'n'://numeric sort
                    option |= NUMERIC;
                    break;
                case 'r'://sort in decreasing order
                    option |= DECR;
                    break;
                default:
                    printf("sort: illegal option %c\n", c);
                    argc = 1;
                    rc = -1;
                    break;
                }
        if (argc)
            printf("Usage: sort -dfnr \n");
        else {
            if ((nlines = readlines(lineptr, LINES)) > 0) {
                if (option & NUMERIC)
                    myqsort((void **) lineptr, 0, nlines-1,
                        (int (*)(void *,void *)) numcmp);
                else
                    myqsort((void **) lineptr, 0, nlines-1,
                        (int (*)(void *,void *)) charcmp);
                writelines(lineptr, nlines, option & DECR);
            } else {
                printf("error: input too big to sort\n");
                rc = -1;
            }
        }
        return rc;
}

#define MAXLEN 1000 /* max length of any input line */
int mygetline(char *, int);
char *alloc(int); //provides a block of memory of the requested size
void afree(char *p);//free the storage pointed to by p

/*readlines: read input lines */
int readlines(char *lineptr[], int maxlines) {
    int len, nlines, i;
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

/* charcmp: return <0 if s>t, 0 if s==t, >0 if s>t */
int charcmp(char *s, char *t) {
    char a, b;
    int fold = (option & FOLD) ? 1 : 0;
    int dir = (option & DORDER) ? 1 : 0;

    do {
        if (dir) {
            while (!isalnum(*s) && *s != ' ' && *s != '\0')
                s++;
            while (!isalnum(*t) && *t != ' ' && *t != '\0')
                t++;
        }
        a = fold ? tolower(*s) : *s;
        s++;
        b = fold ? tolower(*t) : *t;
        t++;
        if (a ==b && a == '\0')
            return 0;
    } while (a == b);
    return a - b;
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
