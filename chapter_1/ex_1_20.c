#include <stdio.h>
#define TABLEN 4

int main() {
	int c, i, spaces, addspaces;
		
	spaces = 0; //track how far along between tab boundaries we are
	
	while((c = getchar()) != EOF) {
		
		if (c != '\t') {
			putchar(c);
			if(c != '\n')
				++spaces;
			else
				spaces = 0; //newline, back to a tab boundary restart the count
		}
		else if (c == '\t') {
			spaces = TABLEN - spaces % TABLEN;//calculate spaces remaining to the next tab boundary
			for(i = 0; i < spaces; ++i)
				putchar(' ');
			spaces = 0;//we've moved to the next tab boundary, restart the count
		}
	}
}
