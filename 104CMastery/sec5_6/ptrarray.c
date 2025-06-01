#include <stdio.h>
#include <string.h>

#define ALLOCSIZE 10000
#define MAXLINE 1000
#define MAXLINES 100

static char allocbuf[ALLOCSIZE]; // the store, the buffer
static char *allocp = allocbuf;  // pointer to next free spot in the buffer
int mygetline(char s[], int maxlen);

char *alloc(int n);
void fun(char *p);
/*
 * At command line ...
 * Enter a string, newline
 * Enter a string, newline
 * Enter a string, newline
 * Sort strings
 * Print out strings
 */

// strings will be held as pointers to pointers to char
// iow, array of pointers char
// while all the strings live in a contiguous array
// when sorting, only the pointers get moved around, not the strings in
// their original array

// Build ...
// skeleton main()
// prompt for one character input
// put that character in a homemade contiguous alloc array

int main(void) {
  int len = 0;
  int nlines = 0;

  char makeline[MAXLINE];
  char *allocated;
  char *lineptrs[MAXLINES];

  printf("enter something\n");

  while ((len = mygetline(makeline, MAXLINE)) > 0) {
    // printf("string: %s length: %d", makeline, len);
    allocated = alloc(len);
    memcpy(allocated, makeline, len);
    // printf("%s", allocated);
    lineptrs[nlines++] = allocated;
  }

  for (int i = 0; i < nlines; i++) {
    printf("%s", lineptrs[i]);
  }
}

// provide storage for n chars
char *alloc(int n) {
  // there is enough room to fit n chars
  if (allocbuf + ALLOCSIZE - allocp >= n) {
    allocp += n;       // move the point to the new next open spot
    return allocp - n; // return pointer to new block allocated
  } else {             // not enough room
    return 0;          // return a NULL pointer
  }
}

// free the storage pointed to by p
// this is restricted to p pointing to the
// start of the last thing stored
// CHALLENGE - change afree to free anywhere along the
// contiguous storage array
void afree(char *p) {
  if (p >= allocbuf && p < allocbuf + ALLOCSIZE)
    allocp = p;
}

int mygetline(char *s, int maxlen) {
  int c;
  char *start = s;

  while (--maxlen > 0 && (c = getchar()) != EOF && c != '\n')
    *s++ = c; // assign c to what s points to then increment pointer
  if (c == '\n')
    *s++ = c; // assign c to what s points to then increment pointer
  *s = '\0';
  return s - start;
}
