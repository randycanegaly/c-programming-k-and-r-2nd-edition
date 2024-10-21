#include <stdio.h>
#include <ctype.h>
#include <string.h>

#define MAXWORD 100
/* update getword() to properly handle underscores, string constants, comments, preprocessor directives
DONE - underscores can't be in a keyword 
-keywords in comments don't count so ignore lines that start with // or anything between / * and * /
-any keyword inside a string constant doesn't count so ignore words between " and "
DONE - accept # as an acceptable first character in a word and only look for keywords starting with the first character after that
*/

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
    {"define", 0},
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
   
    while (getword(word, MAXWORD) != EOF) //passing the word array name is in effect passing a pointer to the first 
        //element in the array to getword(). Changes to word made by getword will be available to main() 
        if(isalpha(word[0])) //if the first character of the word fetched is an alpha. If not, it can't be a keyword.
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
    int c, d, comment(void), getch(void);
    void ungetch(int);
    char *w = word;
 
    while (isspace(c = getch())) //skip spaces
        ;
    if (c != EOF)
        *w++ = c;//gone past last space, set char to first element in word
    if (isalpha(c) || c == '_' || c == '#') { //see alpha, underscore or #
        for ( ; --lim > 0; w++) //walk elements of word
            if (!isalnum(*w = getch()) && *w != '_') { //assign next char to that word element until not an alpha, num or underscore
                ungetch(*w);//went too far, put one back
                break;
        }
    } else if (c == '\'' || c == '"') {// see a quote
        for ( ; --lim > 0; w++) //walk elements of word
            if ((*w = getch()) == '\\') //if see continuation slash
                *++w = getch(); //increment to next word element and set it to the next character retrievedd
            else if (*w == c) { //if see matching end quote, stop loop
                w++;
                break;
            } else if (*w == EOF) //if see end of file, stop loop
                break;
    } else if (c == '/')
        if ((d = getch()) == '*') //saw a /* to start a comment
            c = comment(); //in a comment now, proceed accordingly
        else
            ungetch(d); //didn't see the expected *, so put the / back
    *w = '\0';
    return c;
        

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

int comment(void) {
    int c;

    while ((c = getch()) != EOF) //get characters until end of file
        if(c == '*')
            if ((c = getch()) == '/') //saw the ending */ characters, stop loop
                break;
            else
                ungetch(c); //didn't see expected /, put it back
    return c;
}
