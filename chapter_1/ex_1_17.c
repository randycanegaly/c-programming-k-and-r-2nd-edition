#include <stdio.h>
#define MAXLINE 1000 //max input line length

int mygetline(char line[], int maxline);

/* print all input lines longer than 80 characters */
int main() {
	int len;				//length of current line
	char line[MAXLINE];
	while ((len = mygetline(line, MAXLINE)) > 0) {
		if (len > 80)
			printf("%s", line);	
	}
	
	return 0;
}

/* read an input line into s, return its length */
int mygetline(char s[], int lim) {
	int c, i;

	for (i=0; i<lim-1 && (c = getchar()) != EOF && c!='\n'; ++i) {
		//printf("i: %d, c: %c\n", i, c);
		s[i] = c; 
	}

	if (c == '\n') {
		//printf("out of for, i: %d, c: %c\n", i, c);
		s[i] = c;
		++i; 
	}
	s[i] = '\0';
	return i; 
}


