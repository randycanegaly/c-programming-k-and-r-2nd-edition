#include <stdio.h>

#define MAXLINE 100 //maximum line size
#define TABINC  8   //default tab increment
#define YES     1
#define NO      0

void settab(int arc, char *argv[], char *tab);
void detab(char *tab);
int tabpos(int pos, char *tab);

int main(int argc, char *argv[]) {
    char tab[MAXLINE];
    
    settab(argc, argv, tab);//initialize tab stops
    detab(tab); //replace tabs with blanks
    return 0;
}

/*
* @brief replace tabs with blanks
*
* @param tab - the array of tabs and not tabs
* @return void 
*/
void detab(char *tab) {
    int c, pos = 1;

    while ((c = getchar()) != EOF)
        if (c == '\t') { //see a tab
            do 
                putchar(' ');
            while (tabpos(pos++, tab) != YES);//emit spaces up to the next tab stop
        } else if (c == '\n') { //see a newline
            putchar(c);
            pos = 1;
        } else { //anything else, emit the character and move the position counter
            putchar(c);
            ++pos;
        }
}

