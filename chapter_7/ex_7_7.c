#include <stdio.h>
#include <string.h>

#define MAXLINE 100

/* take input from a set of named files rather than from stdin
 * if no named file cl argument passed, take input from stdin
 * usage should be "prog -x -n pattern [one or more file names]"
*/

int mygetline(char s[], int lim);
/* find: print lines that match pattern from 1st arg */
int main (int argc, char *argv[]) {
    FILE *fp1, *fp2;
    char line[MAXLINE]; 
    long lineno = 0;
    int c, except = 0, number = 0, found = 0;

    while (--argc > 0 && (*++argv)[0] == '-')
        while (c = *++argv[0])
            switch (c) {
            case 'x':
                except = 1;
                break;
            case 'n':
                number = 1;
                break;
            default:
                printf("find: illegal option %c\n", c);
                argc = 0;
                found = -1;
                break;
            } 
//OK to here, just processed any flags



    if (argc < 2)//after skipping program name and processing flags should have 2 args left - pattern and at least one file name
        printf("Usage: find -x -n pattern filenames...\n");
        /* walk the remaining argv elements, they are file names
         * for each, try to open the file
         * do the right output to stderr, etc if file open fails
         * if file open succeeds, then do the stuff below to read each line of the file and check for a match with the pattern
         */
    else {
        if ((fp1 = fopen(*++argv, "r")) == NULL) {
        fprintf(stderr, "can't open %s\n", *argv);
        exit(1);
    } else







        while (mygetline(line, MAXLINE) > 0) {
            lineno++;
            if ((strstr(line, *argv) != NULL) != except) {
                if (number)
                    printf("%ld:", lineno);
                printf("%s", line);
                found++;
            }
        }
    return found;
}

int mygetline(char s[], int lim)  {
    int c, i;

    i = 0;
    while (--lim > 0 && (c = getchar()) != EOF && c != '\n')
        s[i++] = c;
    if (c == '\n')
        s[i++] = c;
    s[i] = '\0';
    return i;
}

