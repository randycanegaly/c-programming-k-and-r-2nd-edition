#include <stdio.h>
#define BREAK 4 //number of tab columns before a line needs to be folded
#define TABLEN 4 //number of spaces in a tab, between tab columns
#define MAXLINE 1000 //max input line length

/*
Write a program to fold lines longer then the nth tab column.
Break lines after the last non-blank character that occurs before the nth tab column.
For clean lines, put the break at the last blank character before the nth column.
*/


//print out a line within boundaries
int mygetline(char line[], int lim);
int breakline(char line[]);
void printline(char line[], int pos);


int main() {
	
	int pos, breakpoint, breakpos;
	char line[MAXLINE];	

	breakpoint = BREAK * TABLEN;	
	
	while((pos = mygetline(line, MAXLINE)) > 0)  {
		if (pos < breakpoint)
			//printf("%s %d\n", line, pos );
			printline(line, pos);
		else {
			//printf("too long, needs folded");
			breakpos = breakline(line);
			printline(line, breakpos);
		}
	}
	
return 0;
}

int mygetline(char s[], int lim) {

	int i, c;
	
	for (i = 0; i<lim-1 && (c = getchar()) != EOF && c != '\n'; ++i)
		s[i] = c;
	if (c == '\n') {
		s[i] = c;
		++i;
	}
	s[i] = '\0';
	//printf("line: %s, len: %d", s, i);
	return i;
}

void printline(char line[], int pos) {
	int j;

	for (j = 0; j < pos; ++j) 
		putchar(line[j]);
	
	//printf("printline");
}

int breakline(char line[]) {
	//return BREAK * TABLEN;
	int b = BREAK * TABLEN;
	while (b > 0 && line[b] != ' ') {
		--b;
	}	
	return b;
}
