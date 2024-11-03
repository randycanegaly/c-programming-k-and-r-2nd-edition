#include <stdio.h>
#include <ctype.h>

#define MAXLINE     100
#define OCTLEN      6

/* print arbitrary input in a sensible way */
int main() {
    int c, pos;
    int inc(int, int);

    pos = 0;
 
    while((c = getchar()) != EOF)
        if (iscntrl(c) || c == ' ') { /* non-graphic or blank */
            pos = inc(pos, OCTLEN);
            printf(" \\%03o ", c); //lead with a space, then a backslash, 3 space minimum, leading zeroes as needed, in octal form

            if (c == '\n') {
                pos = 0;
                putchar('\n');

            }
        } else { //graphic character
            pos = inc(pos, 1);
            putchar(c);
        }
    return 0;
}

/* inc: increment position counter for output */
int inc(int pos, int n) {
    if (pos + n < MAXLINE)
        return pos + n;
    else {
        putchar('\n');
        return n;
    }
}
