#include <unistd.h>

#ifndef NULL
#define NULL        0
#endif
#define EOF         (-1)
#define BUFSIZ      1024
#define OPEN_MAX    20      /* maximum number of files that can be open at one time */

struct {
   unsigned int is_read : 1;
   unsigned int is_write : 1;
   unsigned int is_unbuf : 1;
   unsigned int is_eof : 1;
   unsigned int is_err : 1;
} flags;

typedef struct _iobuf {
    int cnt;    /* characters left */
    char *ptr;  /* next character position */
    char *base; /* location of buffer */
    flags *flag;   /*mode of file access */
    int fd;     /* file descriptor */
} FILE;
extern FILE _iob[OPEN_MAX];

#define stdin   (&_iob[0])
#define stdout  (&_iob[1])
#define stderr  (&_iob[2])

/*enum _flags {
    _READ   = 01,   // file open for reading
    _WRITE  = 02,   // file open for writing
    _UNBUF   = 04,  // file is unbuffered
    _EOF   = 010,   // EOF has occurred on this file
    _ERR   = 020    // error occurred on this file
};*/


int _fillbuf(FILE *);
int _flushbuf(int, FILE *);

#define feof(p)     (((p)->flag & _EOF) != 0)
#define ferror(p)   (((p)->flag & _ERR) != 0)
#define fileno(p)   ((p)->fd)

/* In getc() ....
 * the buffer is full and holds many characters to read
 * cnt says how many characters are left in the buffer that haven't been read yet
 * increment pointer along the buffer, decrementing cnt and returning each character pointed to
 * when all have been read, cnt will be zero
 * so call a function that goes back to the file and reads enough characters to fill
 * the buffer
 * grabbing hunks of the file and buffering them reduces number of read system call
 */
#define getc(p)     (--(p)->cnt >= 0 ? (unsigned char) *(p)->ptr++ : _fillbuf(p))

/* In putc() ....
 * the buffer is for writing. it starts empty
 * cnt says how many empty spaces are available in the buffer, it starts = BUFSIZ
 * every time putc() is called, a character is put in the next open spot in the buffer
 * and cnt is decremented to show one less open spot available.
 * when cnt = 0, then there are no more slots in the buffer
 * flushbuf() is called which will write all the contents of the buffer to the file
 * and reset all aspects of the buffer to represent an empty buffer, ready for loading
 */
#define putc(x,p)   (--(p)->cnt >= 0 ? *(p)->ptr++ = (x) : _flushbuf((x), p))

#define getchar()   getc(stdin)
#define putchar(x)  putc((x), stdout)





