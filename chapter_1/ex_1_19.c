#include <stdio.h>
#define MAXLINE 1000 //max input line size

/* take input from the keyboard and return reversed strings */

int mygetline(char s[], int lim);
void reverse(char in[]);

int main() {
	char line[MAXLINE];		
	
	while(mygetline(line, MAXLINE) > 1) {//use 1, count just a '\n' as a length zero string
		reverse(line);
		printf("%s", line);
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


void reverse(char in[]) {
	int i, j;
	char temp;

	j = 0;

	while (in[j] != '\0')//set j to the end of the string
		++j;

	--j; //back up one to point to '\n'
	if (in[j] == '\n')
		--j;//backed up to point to last real character, leave '\n' at the end
	i = 0;

	while(i < j) {
		temp = in[i];
		in[i] = in[j];
		in[j] = temp;
		++i;
		--j;	
	}
}
