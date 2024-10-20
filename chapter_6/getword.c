#include <stdio.h>
#include <ctype.h>
#include <string.h>

#define MAXWORD 100

struct key {
    char *word;
    int count;
} keytab[] = { //an array of struct key types
    {"auto", 0},
    {"break", 0},
    {"case", 0},
    {"char", 0},
    {"const", 0},
    {"continue", 0},
    {"default", 0},
    /*......*/
    {"unsigned", 0},
    {"void", 0},
    {"volatile", 0},
    {"while", 0}
};

#define NKEYS (sizeof keytab / sizeof (struct key))

int getword(char *, int);
int binsearch(char *, struct key *, int);

/* count C keywords */
int main (void) {
    int n;
    char word[MAXWORD];
    
    while (getword(word, MAXWORD) != EOF)  //fetch the next word from input and return the first character of the word 
        if(isalpha(word[0])) //if the first character of the word fetched is an alpha
            if ((n = binsearch(word, keytab, NKEYS)) >= 0) //found that word in keytab
                keytab[n].count++; //increment the count for that keyword
    for (n = 0; n < NKEYS; n++) //print the count and keyword for all where count > 0
        if( keytab[n].count > 0 )
            printf("%4d %s\n", keytab[n].count, keytab[n].word);
    return 0;
}

/* binsearch: find word in the keyword structure array */
int binsearch(char *word, struct key tab[], int n) { //a binary search
    int cond;
    int low, high, mid;

    low = 0;
    high = n - 1;
    while (low <= high) { //low and high will be moving as the search progresses, when they cross, search is done
        mid = (low + high) / 2; 
        if ((cond = strcmp(word, tab[mid].word)) < 0) //compare word passed in to word in tab array
            high = mid - 1;//tab is sorted. if word passed in is less than word in array mov high to one below mid -- binary search slice in half
        else if (cond > 0)//other way, shift and search upper half
            low = mid + 1;
        else
            return mid;//words match, return a value > 0
    }
    return -1; //no match, return a value < 0
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
