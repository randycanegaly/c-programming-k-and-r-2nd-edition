#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdarg.h>

#define BUFSIZE 1
#define PERMS   664
void error(char *fmt, ...);

/* cat: concatenate file with error handling */
int main(int argc, char *argv[]) {
    int fd;
    void filecopy(int, int);

    if (argc == 1)
        filecopy(0, 1);//no file name command line argument givn
    else
        while (--argc > 0)
            if ((fd = open(*++argv, O_RDONLY, PERMS)) == -1) {
                error("cat: can't open %s", *argv);
            } else {
                filecopy(fd, 1); 
                close(fd);
            }
    return 0;
}

/*filecopy: copy file ifp to file ofp */
void filecopy(int fd1, int fd2) {
    int n;
    char buf[BUFSIZE];

    while((n = read(fd1, buf, BUFSIZE)) > 0)
        if (write(fd2, buf, n) != n) 
            error("cat: write error");
}

/* error: print an error message and die */
void error(char *fmt, ...) {
    va_list args;

    va_start(args, fmt);
    fprintf(stderr, "error: ");
    vfprintf(stderr, fmt, args);
    fprintf(stderr, "\n");
    va_end(args);
    exit(1);
}


