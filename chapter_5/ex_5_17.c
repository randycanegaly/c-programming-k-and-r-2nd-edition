#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

/*Take two optional arguments for a start and end position of a range in the input
 * strings to sort with
 */

#define NUMERIC 1 //numeric sort
#define DECR    2 //sort in decreasing order
#define FOLD    4 //fold upper and lower cases
#define DORDER  8 //directory order
#define LINES   100 //max # of lines to be sorted

int charcmp(char *, char *);
int numcmp(char *, char *);
void readargs(int argc, char *argv[]);
int readlines(char *lineptr[], int maxlines);
void myqsort(void *v[], int left, int right,
        int (*comp) (void *, void *));
void writelines(char *lineptr[], int nlines, int order);
void error(char *);
//int atoi(char *);

char option = 0;//static here means that this variable is only visible within this file
int pos1 = 0;
int pos2 = 0;

/* sort input lines */
int main(int argc, char *argv[]) {
    char *lineptr[LINES]; //array of pointers to chars. pointers to the first character
    //in each command line string
    int nlines; /*number of input lines read*/
    int c, rc = 0;
    
    readargs(argc, argv);
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
        return rc;
}


/* readargs: read program arguments */
void readargs(int argc, char *argv[]) {
    int c;
    //int atoi(char *);

    while (--argc > 0 && (c = (*++argv)[0]) == '-' || c == '+') {
        if (c =='-' && !isdigit(*(argv[0]+1)))
            while (c = *++argv[0])
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
                        error("Usage: sort -dfnr [+pos1] [-pos2]");
                        break;
                    }
        else if (c == '-')
            pos2 = atoi(argv[0]+1);
        else if ((pos1 = atoi(argv[0]+1)) < 0)
            error("Usage: sort -dfnr [+pos1] [-pos2]");
    }
    if (argc || pos1 > pos2)
        error("Usage: sort -dfnr [+pos1] [-pos2]");
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
    int i, j, endpos;
    int fold = (option & FOLD) ? 1 : 0;
    int dir = (option & DORDER) ? 1 : 0;

    i = j = pos1;
    if (pos2 > 0)
        endpos = pos1;
    else if ((endpos = strlen(s)) > strlen(t))
        endpos = strlen(t);
    do {
        if (dir) {
            while (i < endpos && !isalnum(s[i]) && s[i] != ' ' && s[i] != '\0')
                i++;
            while (j < endpos && !isalnum(t[j]) && t[j] != ' ' && t[j] != '\0')
                j++;
        }
        if (i < endpos && j <  endpos) {
            a = fold ? tolower(s[i]) : s[i];
            i++;
            b = fold ? tolower(t[j]) : t[j];
            j++;
        if (a ==b && a == '\0')
            return 0;
        }

    } while (a == b && i < endpos && j < endpos);
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

#define MAXSTR 100
void substr(char *s, char *t, int maxstr);

int numcmp(char *s1, char *s2) {

    double v1, v2;
    char str[MAXSTR];

    substr(s1, str, MAXSTR);
    v1 = atof(s1);
    substr(s2, str, MAXSTR);
    v2 = atof(s2);
    if (v1 < v2)
        return -1;
    else if (v1 > v2)
        return 1;
    else
        return 0;
}

/*substr: get a substring of s and put it in str */
void substr(char *s, char *str, int maxstr) {
    int i, j, len;
    extern int pos1, pos2;

    len = strlen(s);
    if (pos2 > 0 && len > pos2)
        len = pos2;
    else if (pos2 > 0 && len < pos2)
        error("substr: string too short");
    for (j = 0, i = pos1; i < len; i++, j++)
        str[j] = s[i];
    str[j] = '\0';
}

/* error: print error message and exit */
void error(char *s) {
    printf("%s\n", s);
    exit(1);
}

/*int atoi(char *s) {
    int n, sign;

    for ( ; isspace(*s); s++)
        ;
    sign = (*s == '-') ? -1 : 1;
    if (*s == '+' || *s == '-')
        s++;
    for (n = 0; isdigit(*s); s++)
        n = 10 * n + *s - '0';
    return sign * n;
}*/
