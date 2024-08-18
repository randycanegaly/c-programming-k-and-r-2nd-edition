#include <stdio.h>

/*
Copy input to output, replacing every string of blanks with one blank
*/

#define NOTABLANK 'a'

int main() {

	int c, last;//last keeps the previous character seen
	last = NOTABLANK;//need to set last to something to get started

	while((c = getchar()) != EOF ) {//get characters from input until EOF seen
		if (c != ' ') {//always output c if it's not a blank
			putchar(c);
		}
		if (c == ' ') {//c is a blank
			if (last != ' ') {//if we just saw a blank, then don't output anymore blanks
				putchar(c);
			}
		}
		last = c;//update last to be c 
	}

	return 0;
}
