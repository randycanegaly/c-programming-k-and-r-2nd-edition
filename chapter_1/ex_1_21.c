#include <stdio.h>
#define TABLEN 4 //length of tab, spaces between tab stops

/* replace strings of blanks with tabs and blanks */
/* I had a hard time with this exercise. My version wouldn't work for all cases. 
I looked at the solution in the "The C Answer Book" for help */

int main() {
	int c, nb, nt, pos; //number of blanks, number of tabs, position in the line

	nb = 0;
	nt = 0;

	for(pos = 1; (c = getchar()) != EOF; ++pos) {
		if (c == ' ') {//see a blank
			if(pos % TABLEN != 0)//between tab stops, increment number spaces needed
				++nb;
			else {
				nb = 0; //at a tab stop, don't need spaces counted
				++nt;   //increment number of tabs needed
			}
		} else {//see a non-blank character, string of blanks done, output needed tabs and blanks
			for ( ; nt > 0; --nt)
				putchar('\t'); 
			if (c == '\t')
				nb = 0;//see a tab at input, that'll jump us to the next tab stop, no blanks needed
			else //it's some other non-blank character, not a tab
				for ( ; nb >0; --nb)//we've already output needed tabs, now output the needed blanks
					putchar(' ');
			putchar(c);//now output the actual non-blank character we just saw in the output
			if (c == '\n')//at a new line, reset position counter
				pos = 0;
			else if (c == '\t')//the non-blank character input is a tab. A tab will jump pos to the 
			//next tab stop. How many positions to that next tab stop??
				pos = pos + (TABLEN - (pos - 1) % TABLEN) - 1;
				/*Example: say pos = 37. previous tab stop was at 36, next one is at 40
					by order of precedence, the calculation is:
						pos - 1 = 36, the position before non-blank character just input
						that % TABLEN = 0
						TABLEN - that = 4
						that - 1 = 3
						3 is the distance from the current positon (37) to the next tab stop (40)
					so, the new pos is at the next tab stop, 40
				*/	
		}

	}
}
