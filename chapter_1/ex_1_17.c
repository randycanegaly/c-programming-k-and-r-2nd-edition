#include <stdio.h>
#define MAXLINE 1000 //max input line length
#define LONGLINE 80

int mygetline(char line[], int maxline);
void copy(char to[], char from[]);

/* print all input lines longer than 80 characters*/
int main() {
	int len;
	int max;
	char line[MAXLINE];
	char longest[MAXLINE]; 

	max = 0; 			
	while ((len = mygetline(line, MAXLINE)) > 0) 
		if(len > LONGLINE) {
			max = len;
			copy(longest, line);
		}
	if (max > 0) {	
		printf("longest: %s\n", longest);
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
