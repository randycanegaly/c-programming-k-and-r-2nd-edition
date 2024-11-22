#include <stdlib.h>
#include "syscalls.h"

/* _fillbuf: allocate and fill input buffer */
int _fillbuf(FILE *fp) {
    int bufsize;

    if (fp->flag.isread == 0 || fp->flag.iseof == 1 || fp->flag.iserr == 1)
        return EOF;
    if (fp->flag.isunbuf == 1)
        bufsize = 1;
    else if (fp->flag.isunbuf == 0)
        bufsize = BUFSIZ;
    if (fp->base == NULL) /* no buffer yet */
        if ((fp->base = (char *) malloc(bufsize)) == NULL)
            return EOF;
    fp->ptr = fp->base;
    fp->cnt = read(fp->fd, fp->ptr, bufsize);
    if (--fp->cnt < 0) {
        if (fp->cnt == -1)
            fp->flag.iseof = 1;
        else
            fp->flag.iserr = 1;
        fp->cnt = 0;
        return EOF;
    }
    return (unsigned char) *fp->ptr++;
}

/* What does _fillbuf() do?
 * The concept of a buffer exists, the base pointer in FILE points to the start of the buffer
 * checks for a buffer, if base points to nothing, try to allocate for base
 * If allocation for base fails, return end of file.
 * Set the next character pointer to the start of the buffer
 * read bufsize bytes into base and set the number of bytes read to cnt
 * set flag to EOF or ERR if cnt is zero-ish
 * set cnt to zero and return EOF
 * otherwise all went well, return the value of the first char in buff
 */
