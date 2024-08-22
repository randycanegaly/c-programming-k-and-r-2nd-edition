#include <stdio.h>

#define IN 	1 	//in a word
#define OUT 0	//not in a word

/*
count lines, words and characters as input
*/

int main () {
	int c, nl, nw, nc, state;	
	state = OUT; //initial state
	nl = nw = nc = 0;

	while((c = getchar()) != EOF) {
		++nc; //increment character count
		if (c == '\n')
			++nl;//finished a line, increment line count
		if (c == ' ' || c == '\n' || c == '\t')
			state = OUT;//have gone out of a word
		else if (state == OUT) { //this else is for the if immediately above
			//not in a word
			//see a character that's not a newline, space or tab
			//must be entering a word
			state = IN;//in a word now, change the state
			++nw; //so, increment word count
		}
	}
	printf("lines: %d, words: %d, characters: %d", nl, nw, nc);

}
