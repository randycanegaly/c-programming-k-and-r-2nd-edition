#include <stdio.h>
#define MAXLINE 1000 //max input line length

int mygetline(char line[], int maxline);
void copy(char to[], char from[]);

/* print longest input line */
int main() {
	int len;				//length of current line
	int max;				//maximum line length seen so far
	char line[MAXLINE]; 	//current input line
	char longest[MAXLINE]; 	//longest line so far is saved here

	max = 0; 				//just starting, have no max yet
	while ((len = mygetline(line, MAXLINE)) > 0) 
	//getline() returns the length of the line, run until hit a no-length line
		//printf("len: %d", len);
		if(len > max) {
			max = len;//saw a line longer than max
			copy(longest, line);
		}
	if (max > 0) {			//found at least one line
		printf("longest: %s\n", longest);//print the longest line found 
	}
	return 0;
}

/* read an input line into s, return its length */
int mygetline(char s[], int lim) {
	int c, i;

	for (i=0; i<lim-1 && (c = getchar()) != EOF && c!='\n'; ++i) 
	//stop one shy of max because we have to stick in '0' at the end of the array
	//stop if the character is end of file
	//don't process anything if it's the newline character
		s[i] = c; //stick character in s if not near end, not EOF and not newline
	
	if (c == '\n') {//special case, do the thing with newline that the for loop ignored
		s[i] = c;//stick newline in the array
		++i; 
	}
	s[i] = '0';//always stick '0' to mark end of character array
	return i; //return the length found
}

/*  copy from into to  */
void copy(char to[], char from[]) {
	int i;
	
	i = 0;
	while((to[i] = from[i]) != '0') {
		++i;
	}
}
