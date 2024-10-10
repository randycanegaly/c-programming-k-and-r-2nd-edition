#include <stdio.h>

#define MAXLINE 100 //maximum line size
#define TABINC  8   //default tab increment
#define YES     1
#define NO      0

void settab(int arc, char *argv[], char *tab);
void entab(char *tab);
int tabpos(int pos, char *tab);

int main(int argc, char *argv[]) {
    char tab[MAXLINE];
    
    settab(argc, argv, tab);//initialize tab stops
    entab(tab); //replace blanks with tabs and some spaces as needed
    return 0;
}

/*
* @brief replace collections of blanks with tabs and blanks
*
* @param tab - the array of tabs and not tabs
* @return void 
*/
void entab(char *tab) {
    int c, pos;
    int nb = 0; //number of blanks needed
    int nt = 0; //number of blanks needed

    for (pos = 1; (c = getchar()) != EOF; pos++)
        if (c == ' ') {
            if (tabpos(pos, tab) == NO) // not at a tab stop, adjust number of tabs needed
                nb++;
            else {
                nb = 0; //we are at a tab stop, no blanks needed
                nt++;   //increment number of tabs needed
            }
        } else { //not seeing a blank, that's the end of the string of blanks,
            //so emit the number of tabs and blanks required
            for ( ; nt > 0; nt--) //emit tabs
                putchar('\t');
            if (c == '\t') //already at a tab stop
                nb = 0; //reset blank counter, need no blanks right now
            else
                for ( ; nb > 0; nb--)
                    putchar(' '); //emit blanks required
            //the tabs and blanks required have been output, now output that non-blank character
            //that signalled the end of the string of blanks
            putchar(c);
            if (c == '\n') //end of line
                pos = 0; //reset the position counter for start of a new line
            else if (c == '\t') //the input character is a tab so need to jump to next tab stop
                while (tabpos(pos, tab) != YES)//walk positions up to next tab stop
                    ++pos;
        }
}

