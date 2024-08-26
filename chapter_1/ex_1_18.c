#include <stdio.h>
#define MAXLINE 1000 //max input line length

int buildline(char line[], int maxline);
int removewhite(char line[]);

/* remove trailing blanks and tabs from each line of input and delete entirely blank lines */

int main() {
	int len;				//length of current line
	int max;				//maximum line length seen so far
	char line[MAXLINE]; 	//current input line
	char longest[MAXLINE]; 	//longest line so far is saved here

	max = 0; 				
	while ((len = buildline(line, MAXLINE)) > 0)
		if (removewhite(line) > 0)
			printf("trimmed:%s", line);
	
	return 0;
}

int buildline(char s[], int lim) {
	int c, i;

	for (i=0; i<lim-1 && (c = getchar()) != EOF && c!='\n'; ++i) {
		s[i] = c; 
	}

	if (c == '\n') {
		s[i] = c;
		++i; 
	}
	s[i] = '\0';
	return i; 
}

int removewhite(char s[]) {

	int i;
	i = 0;
	while (s[i] != '\n') {
		++i;
	}
	
	--i;


	while(i >= 0 && (s[i] == ' ' || s[i] == '\t')) {
		--i;
	}

	if (i >= 0) {
		++i;
		s[i] = '\n';
		++i;
		s[i] = '\0';
		--i;
	}
	
	if (i > 0) {
		printf("len: %d ", i);
	}

	return i;
} 
