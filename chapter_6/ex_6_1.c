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

int in_big_comment = 0;

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
//skip lines that start with // or #

/*
param word: pointer to the first char element in the word array. A "side effect" of this
function is that the word array is populated with the word found
param lim: maximum size of word to be seen
return: first character of the word array

How it works:
- skip spaces
- 
*/
int getword(char *word, int lim) {//the address to the first character in the word array is passed by value - a pointer
    //this allows this function to move that pointer around and assign values to "the thing pointed to" by the pointer
    //this is in effect, "pass by reference". Changes to the word array made inside this function persist outside to the caller
    int c, d, getch(void);
    void ungetch(int);//going to use these two functions in here, have to declare them first
    char *w = word;
    
    


    while (isspace(c = getch()) && c == '#') //skip white space and also skip '#' to handle keywords in preprocessor directives
        ;
    if(c == '/') {
        if((d = getch()) == '/' || d == '*') {
            while((d = getch()) != '\n')
                ;
        in_big_comment = 1;            
        } else
            ungetch(c);
    }
 
    if (c != EOF) //not a space and not end of file
        *w++ = c; //set element at w to c and then advance pointer to next w location
    /*if (c == '_') { //see an underscore. everything after it can't be a keyword, this handles words starting with '_'
        for ( ; --lim > 0; w++)
            if(!isspace(c = getch()))
                ;
            else
                ungetch(c);
    }*/
    if (!isalpha(c) && c != '_') { //if that c is not an alpha, then we can't be looking at a keyword, terminate it and return c
        *w = '\0';
        return c;
    }
    for ( ; --lim > 0; w++) //walk the word up to the point that a non-alpha or non-number character is seen, always setting value at the advancing w pointer to that character
        if (!isalnum(*w = getch()) && *w != '_') { //get the next character, if it's not an alpha, number, or underscore push that too far character back
            //anything not pushed back will be included in the word so '_' included in the word will fail the strcmp against keywords
            ungetch(*w); //at this point, have gone one too far. put it back
            break; //exit the loop, done building the word string
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
