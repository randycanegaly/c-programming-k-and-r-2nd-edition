#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXLINE 100

/* comp: compare two files and print the first line where they differ */
int main(int argc, char *argv[]) {
    FILE *fp1, *fp2;
    void filecomp(FILE *fp1, FILE *fp2);

    if (argc != 3) {
       printf("usage: provide 2 file names as arguments\n"); 
       exit(1);
    }
    else {
        if ((fp1 = fopen(*++argv, "r")) == NULL) {
            fprintf(stderr, "can't open %s\n", *argv);
            exit(1);
        } else if ((fp2 = fopen(*++argv, "r")) == NULL) {
            fprintf(stderr, "can't open %s\n", *argv);
            exit(2);
        } else {
            filecomp(fp1, fp2);
            fclose(fp1);
            fclose(fp2);
            exit(0);
        } 
    }
}
    
/* compare two file, a line at at time */
void filecomp(FILE *fp1, FILE *fp2) {
    char *lp1, *lp2;
    char line1[MAXLINE], line2[MAXLINE];

    do {
        lp1 = fgets(line1, MAXLINE, fp1);
        lp2 = fgets(line2, MAXLINE, fp2);

        if (lp1 == line1 && lp2 == line2) {
            if (strcmp(line1, line2) != 0) {
                printf("first difference found, file1 line: %s\n", line1);
                printf("file2 line: %s\n", line2);
                lp1 = lp2 = NULL;//so upon loop test, the loop exits
            }
        } else if (lp1 != line1 && lp2 == line2) 
            printf("first file ended at \n%s\n", line1);
        else if (lp1 != line1 && lp2 == line2)
            printf("second file ended at \n%s\n", line1);
    } while (lp1 == line1 && lp2 == line2);
}
