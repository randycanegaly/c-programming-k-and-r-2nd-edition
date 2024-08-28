#include <stdio.h>
#define MAXLINE 1000 //max input line size

int mygetline(char s[], int lim);

int main() {
	int len;
	char line[MAXLINE];		
	
	while(mygetline(line, MAXLINE) > 0) 
		printf("%s\n", line );
	
	return 0;
}

int mygetline(char s[], int lim) {

	int i, c;
	
	for (i = 0; i<lim-1 && (c = getchar()) != EOF && c != '\n'; ++i)
		s[i] = c;
	if (c == 'n') {
		s[i] = c;
		++i;
	}
	s[i] = '\0';
	//printf("line: %s, len: %d", s, i);
	return i;
}
