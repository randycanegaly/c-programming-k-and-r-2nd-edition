#include <stdlib.h>

#define MAXLINE 100
#define TABINC  8
#define YES     1
#define NO      0

/*
 * a function to create a representation of tabs to be used
 * it will take the form of an array of NO values with YES values where tabs are to occur
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
void settab(int argc, char *argv[], char *tab) {
   int i, pos;

    if (argc <= 1) //no tabs were passed as command line arguments, use default tab stops
        for (i = 1; i <= MAXLINE; i++) //walk the tabs array, put tab marker at default spots
            if (i % TABINC == 0)
                tab[i] == YES;
            else
                tab[i] == NO;
    else { //there were tabs passed as command line arguments. use them.
        for (i = 1; i <= MAXLINE; i++)
            tab[i] = NO;//first, set to be no tab stops
        while (--argc > 0) { //walk command line arguments and use those values to set tab stops
            pos = atoi(*++argv); //increment the argv pointer. that moves it to point one past the
            //file name string. the * dereferences "*++argv}" means the thing that the next pointer in
            //the array argv points to ... the first tab stop command line argument
            if (pos > 0 && pos <= MAXLINE) //if we got a valid, in bounds value for a tab stop
                tab[pos] = YES;
        }
    }
}
