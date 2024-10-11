#define MAXLINE 100 /* maximum line size */
#define YES     1

/*
 * @brief a function to determine if there is a tab stop at a given position in the tab array
 *
 * @param pos - the position to check
 * @param tab - the array of tab stops and not tab stops
 * @return int - indicator of pos tab or not 
 */

int tabpos(int pos, char *tab) {
    if (pos > MAXLINE) //ran out of bounds, it's a tab by default
        return YES;
    else
        return tab[pos];//return the element at that index in tabs - it's either a tab, or not
}



