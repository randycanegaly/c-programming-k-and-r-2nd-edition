#include <stdio.h>
#include <string.h>
#include <stdlib.h>

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
    char *pattern;

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
    //argc now says how many command line args are not yet processed
    if (argc == 0) {//no arguments left, error
        printf("Usage: find -x -n \"pattern\" filenames...\n");
    } else if (argc == 1) {//only one argument left, the pattern, take input from stdin {
        //argv points to the first unprocessed command line argument = the pattern
        while (mygetline(line, MAXLINE) > 0) {
            lineno++;
            if ((strstr(line, *argv) != NULL) != except) {
                if (number)
                    printf("%ld:", lineno);
                printf("%s", line);
                found++;
            }
        }
    } else if (argc > 1){//there are some file names provided as arguments, so walk the corresponding files and process their contents
        pattern = *argv;
        //argv points to the first unprocessed command line argument = the pattern
        /* walk the remaining argv elements, they are file names
         * for each, try to open the file
         * do the right output to stderr, etc if file open fails
         * if file open succeeds, then process the file's contents
         */
        while (--argc > 0) {
            if ((fp1 = fopen(*++argv, "r")) == NULL) { //argv points to the pattern, ++argv advances the pointer to the 
                                                       //next argv array element = pointer to a file name string
                                                       //*++argv is that file name string, this handles the file open failure case 
                fprintf(stderr, "can't open %s\n", *argv);
                exit(1);
            } else {//file opened successfully, have a valid file pointer
                while (fgets(line, MAXLINE, fp1)) {
                    lineno++;
                    if ((strstr(line, pattern) != NULL) != except) {
                        if (number)
                            printf("%ld:", lineno);
                        printf("%s", line);
                        found++;
                    }
                }
            }
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

