#include <stdlib.h>
#include <stdio.h>

#define MAXLINE 20
#define TABINC  8
#define YES     1
#define NO      0

/*
 *this is settab but modified to take command line arguments like
 *entab -m + n, so that tabs are set every n columns, starting at column
 */

/*
 * @brief create an array 'tab' holding indicators for tab stops
 *
 * @param argc - same as for the main function
 * @param argv - same as for the main function, an array of pointers to chars,
 *      array of command line parameter strings
 * @param tab - pointer to the first char in an array of chars for tab stop indicators
 *      same as a pointer to that array
 * @return void 
 */
void newsettab(int argc, char *argv[], char *tab) {
    int i, inc, pos;

    if (argc <= 1)  //no command line arguments were passed, use default tab stops
        for (i = 1; i <= MAXLINE; i++) //walk the tabs array, put tab marker at default spots
            if (i % TABINC == 0)
                tab[i] == YES;
            else
                tab[i] == NO;
    else if (argc == 3 && *argv[1] == '-' && *argv[2] == '+') {//see correct command line arguments??
        //printf("the thing argv points to: %s\n", *argv);//the string of the program name, the first element of argv 
        //printf("the thing ++argv points to: %s\n", *++argv);//the string of the first command line argument
        //the second element of argv 
        //printf("the second element of the thing ++argv points to: %c\n", (*++argv)[1]);//the second character of the string of the first command line argument
        //atoi expects a pointer to a null terminated string
        //&(*++argv)[1] .... is the address (a pointer to) of the second element of the thing that argv points to
        //after argv has been advanced one position
        //so &(*++argv)[1] is a pointer to the second element (a char) of the string that the second element of argv points to
        //the second element of argv is the string "-m". the second element of that string is m. so we have a pointer to m
        //which is the start column
        //advance argv again and do the same thing and you have a pointer to n, the number of columns to advance to each tab stop

        pos = atoi(&(*++argv)[1]);
        inc = atoi(&(*++argv)[1]);
        for (i = 1; i <= MAXLINE; i++)
            if(i != pos)
                tab[i] = NO;
            else {
                tab[i] = YES;
                pos += inc;
            }
    }
}
