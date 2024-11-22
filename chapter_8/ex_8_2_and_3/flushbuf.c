#include <stdlib.h>
#include "syscalls.h"

/* A function to flush the FILE buffer when it is full. 
 * Flush means to write the buffer contents to the file and then 
 * reset the buffer to show as empty, ready for more characters to be loaded into it */
//param: x, the character that is in hand when it is discovered that the output buffer is full
//param: fp, pointer to the FILE structure representing the file
int _flushbuf(int x, FILE *fp) {
    unsigned nc; //# of characters to flush to the file
    int bufsize; //the size of the buffer to allocate

    //check if the pointer points within the array of FILE types
    if (fp < _iob || fp >= _iob + OPEN_MAX)//pointer math
        return EOF;
    //check that the file is open for writing
    if (fp->flags.is_write == 0 || fp->flags.is_err == 1)
        return EOF;
    //determine what buffer size is suppose to be: 1 or 1024
    bufsize = (fp->flags.is_unbuf == 1) ? 1 : BUFSIZ;
    //check if there's a buffer 
    if (fp->base == NULL) {
        //if not, allocate one. if that fails, return EOF
        if ((fp->base = (char *) malloc(bufsize)) == NULL) {
            fp->flags.is_err = 1;
            return EOF;
        }            
    } else {//there's already a buffer
        //if there is, how many characters need to be flushed?
        nc = fp->ptr - fp->base; 
        //write that many characters to the file
        if (write(fp->fd, fp->base, nc) != nc) {//if the number of characters 
                                                //written != number that should've been, return EOF 
            fp->flags.is_err = 1;
            return EOF;
        }
    }
    //the contents of the buffer have now been written to the file
    //reset, as if the buffer is empty: ptr to front of buffer, 
    //cnt to buffer size - 1 for the one character in hand that has to be added to the buffer
    //return the one character in hand
    fp->ptr = fp->base;
    *fp->ptr++ = (char) x; 
    fp->cnt = bufsize - 1;
    return x;
}
