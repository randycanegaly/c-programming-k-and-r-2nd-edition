#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>

#include "syscalls.h"

#define PERMS   0666 /*RW for owner, group, others */

FILE *fopen(char *name, char* mode); 
int fclose(FILE *fp);
int fflush(FILE *fp);

FILE _iob[OPEN_MAX] = {
    { 0, (char *) 0, (char *) 0, _READ, 0 },
    { 0, (char *) 0, (char *) 0, _WRITE, 1 },
    { 0, (char *) 0, (char *) 0, _WRITE | _UNBUF, 2 }
};

int main(void) {
    char c;
    FILE *fp, *fp_out;

    if ((fp = fopen("fone.txt", "r")) == NULL)
        putchar('z');
    else if ((fp_out = fopen("fout.txt", "w")) == NULL)
        putchar('o');
    else
        while ((c = getc(fp)) != EOF)
            //putc(c, stdout);
            putc(c, fp_out);
   
    fclose(fp);
    fclose(fp_out);
    return 0;
}

/* fopen: open file, return file ptr */
FILE *fopen(char *name, char* mode) {
    int fd;
    FILE *fp;

    if (*mode != 'r' && *mode != 'w' && *mode != 'a')
        return NULL;
    for (fp = _iob; fp < _iob + OPEN_MAX; fp++)
        if ((fp->flag & (_READ | _WRITE)) == 0)
            break;  /* found free slot */
    if (fp >= _iob + OPEN_MAX)  /* no free slots */
        return NULL;

    if (*mode == 'w')
        fd = creat(name, PERMS);
    else if (*mode == 'a') {
        if ((fd = open(name, O_WRONLY, 0)) == -1)
            fd = creat(name, PERMS);
        lseek(fd, 0L, 2);
    } else
        fd = open(name, O_RDONLY, 0);
    if (fd == -1)
        return NULL;
    fp->fd = fd;
    fp->cnt = 0;
    fp->base = NULL;
    fp->flag = (*mode == 'r') ? _READ : _WRITE;
    return fp;
}

/* fflush: flush buffer associated with file fp */
int fflush(FILE *fp) {
    int rc = 0;

    if (fp < _iob || fp >= _iob + OPEN_MAX)
        return EOF;
    if (fp->flag & _WRITE)
        rc = _flushbuf(0, fp);
    fp->ptr = fp->base;
    fp->cnt = (fp->flag & _UNBUF) ? 1 : BUFSIZ;
    return rc;
}

/* fclose: close file */
int fclose(FILE *fp) {
    int rc;

    if ((rc = fflush(fp)) != EOF) {
        free(fp->base);
        fp->ptr = NULL;
        fp->cnt = 0;
        fp->base = NULL;
        fp->flag &= ~(_READ | _WRITE);
    }
    return rc;
}
