#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAXLINE     100 //max characters per line
#define MAXLINES    10  //max lines per page
#define NEW_PAGE    20  //number of lines between new pages

/* print a set of files, starting each new one on a new page, with a title and a running page count for each file */
int main (int argc, char *argv[]) {
    FILE *fp;
    char line[MAXLINE]; 
    int i, page_count = 1;

    if (argc < 2) {//has to be at least 2 arguments, the program name and at least one file name
        printf("Usage: progname filenames...\n");
    } else if (argc >= 2){

        while (--argc > 0) {
            if ((fp = fopen(*++argv, "r")) == NULL) {
                fprintf(stderr, "can't open %s\n", *argv);
                exit(1);
            } else {//file opened successfully, have a valid file pointer
                printf("TITLE :%s\n", *argv);
                while (fgets(line, MAXLINE, fp)) {
                        printf("%s", line);
                }
                printf("PAGE %d\n", page_count++);
                for (i = 0; i < NEW_PAGE; i++)
                    printf("\n");
            }
        }
    }
}
