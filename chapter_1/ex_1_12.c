#include <stdio.h>

#define IN 	1 	//in a word
#define OUT 0	//not in a word

/*
print the input one word per line
*/

int main () {
	int c, state;	
	state = OUT; //initial state

	while((c = getchar()) != EOF) {
		if (c == ' ' || c == '\n' || c == '\t') {
			if (state = IN) {//we are in a word and have seen a word ending character
				state = OUT;//change the state because we're out of the word now
				putchar('\n');//don't output a space or tab character, just a newline to put the word
				//on its own output line
			}
		} else if (state == OUT) {
			//not in a word now and starting a new word - this character is not a newline, space or tab
			state = IN;//change the state to in a word
			putchar(c);//this is the first character of a new word, output it	
		} else {//not falling out of a word nor starting a new one, so output middle of word character
			putchar(c);
		}
	}
}
