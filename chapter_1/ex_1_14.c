#include <stdio.h>

#define NUM_ASCII 128 //there are 128 ascii characters
#define TAB_ASCII 9 //a tab has the ascii numeric value of 9
#define SPACE_ASCII 32 //similar
#define DISPLAY_TAB "TAB: "
#define DISPLAY_SPACE "SPACE: "

/*
print a histogram of the frequencies of different characters
*/

int main () {
	int c, i, j, chars[NUM_ASCII];
	
	for (i = 0; i < NUM_ASCII; ++i)
		chars[i] = 0; 

	while((c = getchar()) != EOF)
		++chars[c];				

	//print the histogram
	printf("Character Frequency Histogram\n");
	for (i=0; i < NUM_ASCII; ++i) {
		if (chars[i] > 0 && (i == TAB_ASCII  || i >= SPACE_ASCII)) {//not interested in most ascii characters 
																	//below numeric value 32. 
																	//Except we care about tab
			if(i == TAB_ASCII)
				printf("%8s", DISPLAY_TAB);//get to display TAB instead of 4 or 8 empty spaces - dumb label
			else if(i == SPACE_ASCII)
				printf("%8s", DISPLAY_SPACE);//same logic for a space
			else
				printf("%6c: ", (char)i);//convert int to char to display the char value as a 
										 //label for the histogram row
			
			for (j = 0; j < chars[i]; ++j)
				printf("*");
			printf("\n");
		}
	}
}
