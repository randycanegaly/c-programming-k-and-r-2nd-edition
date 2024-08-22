#include <stdio.h>

#define IN 	1 	//in a word
#define OUT 0	//not in a word
#define MAX_LENGTH 20 //longest word we'll see
/*
print a histogram of word lengths
*/



int main () {
	int c, i, j, length, state, lengths[MAX_LENGTH + 1];
	state = OUT; //initial state
	length = 0;
	for (i = 0; i <= MAX_LENGTH; ++i)
		lengths[i] = 0; 

	while((c = getchar()) != EOF) {
		if (c == ' ' || c == '\n' || c == '\t' || c == ',' || c == '!') {
			if (state = IN && length <= MAX_LENGTH) {//see a word ending
				++lengths[length];//increment the array for that length word we just fell out of
				length = 0;//reset the length to count the next word found
			} else 
				printf("Went over max length: %d", length);
		} else if (state == OUT) {
			//not in a word now and starting a new word - this character is not a newline, space or tab
			state = IN;//change the state to in a word
			++length;//count the word's starting character in the word length
		} else {//not falling out of a word nor starting a new one, so increment word length
			++length;
		}
	}

	//print the histogram
	printf("Word Length Histogram ...\n");
	for (i=1; i <= MAX_LENGTH; ++i) {
		printf("%2d: ", i);
		for (j = lengths[i]; j > 0; --j)
			printf("*");
		printf("\n");

	}
}
