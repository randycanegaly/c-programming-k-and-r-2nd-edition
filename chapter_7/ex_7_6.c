#include <stdio.h>
#include <stdlib.h>

/* cat: diff two files and print the first line where they differ */
int main(int argc, char *argv[]) {
    FILE *fp1, *fp2;
    char c1, c2; 
    char *prog = argv[0]; //program name

    if (argc != 3) {
       printf("usage: provide 2 file names as arguments\n"); 
       exit(1);
    }
    else {
        if ((fp1 = fopen(*++argv, "r")) == NULL) {
            fprintf(stderr, "%s: can't open %s\n", prog, *argv);
            exit(1);
        }
        if ((fp2 = fopen(*++argv, "r")) == NULL) {
            fprintf(stderr, "%s: can't open %s\n", prog, *argv);
            exit(2);
        }
        while ((c1 = getc(fp1)) != EOF && (c2 = getc(fp2)) != EOF)
            if (c1 != c2) {
                printf("files not equal!\n");
                exit(0);
            }
        printf("file are equal!\n");
        exit(0);
    }
    exit(0);
}
