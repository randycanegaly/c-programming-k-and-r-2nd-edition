#include <stdio.h>
#define MAXLINE 1000 //max input line length

int mygetline(char line[], int maxline);
void copy(char to[], char from[]);

/* print length of each line along with the line */
int main() {
	int len;				//length of current line
	int max;				//maximum line length seen so far
	char line[MAXLINE]; 	//current input line
	char longest[MAXLINE]; 	//longest line so far is saved here

	max = 0; 				//just starting, have no max yet
	while ((len = mygetline(line, MAXLINE)) > 0) {//need to add braces now as the if is no longer a statement
		//all by itself within the while loop
		printf("%d %s", len, line);	
		if(len > max) {
			max = len;
			copy(longest, line);
		}
	}
	
	if (max > 0) 			//found at least one line
		printf("longest: %s", longest);//print the longest line found 
	
	//return 0;
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
	return i-1; 
}

/*  copy from into to  */
void copy(char to[], char from[]) {
	int i;
	
	i = 0;
	while((to[i] = from[i]) != '0') {
		++i;
	}
}
