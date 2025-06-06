#include <stdio.h>
#include <string.h>

#define ALLOCSIZE 10000
#define MAXLINE 1000
#define MAXLINES 100

static char allocbuf[ALLOCSIZE]; // the store, the buffer
static char *allocp = allocbuf;  // pointer to next free spot in the buffer
char *lineptrs[MAXLINES];

int mygetline(char s[], int maxlen);
char *alloc(int n);
int readlines(char *lineptrs[], int maxlines);
void sort(void); // TO DO
void writelines(char *lineptrs[], int nlines);

int main(void) {
  int nlines;

  printf("Enter something.\n");
  // readlines returns -1 on a problem
  if ((nlines = readlines(lineptrs, MAXLINES)) >= 0) {
    sort(); // TO DO
    writelines(lineptrs, nlines);
    return 0;
  } else {
    printf("error: too many lines or allocation problem.\n");
    return -1;
  }
}

int readlines(char *lineptrs[], int maxlines) {
  int len;
  int nlines = 0;
  char makeline[MAXLINE];
  char *allocated;

  while ((len = mygetline(makeline, MAXLINE)) > 0) {
    if (nlines > maxlines || (allocated = alloc(len)) == NULL)
      return -1;
    else {
      // don't want newline on every string pointed to
      makeline[len - 1] = '\0';
      strcpy(allocated, makeline);
      lineptrs[nlines++] = allocated;
    }
  }

  return nlines;
}

void sort(void) {} // TO DO

void writelines(char *lineptrs[], int nlines) {
  while (nlines-- > 0)
    printf("%s\n", *lineptrs++);
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
