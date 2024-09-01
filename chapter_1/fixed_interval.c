#include <stdio.h>
#define FIXEDBREAK 5 //number of tab columns before a line needs to be folded
#define MAXLINE 1000 //max input line length
#define SAFETY 50
/*
Write a program to fold lines at every FIXEDBREAK position
*/


//print out a line within boundaries
int mygetline(char line[], int lim);
/*int breakline(char line[]);
void printline(char line[], int pos);*/
int fold(char tofold[], int start);


int main() {
	
	int lineleft, start, iterations;
	char line[MAXLINE];//the entire input line
	char cutline[MAXLINE];//line before the fold
	char nextline[MAXLINE];//line remaining after the fold - temporary, could get folded again

	start = 0;
	iterations = 0;
	while((lineleft = mygetline(line, MAXLINE)) > 0)  {//one line's been built here
		while (lineleft > 0 && iterations < SAFETY) {//no more of the input line left to fold
			start = fold(line, start);
			printf("B: %d\n", start);
			printf("C: %d\n", lineleft);
			
			lineleft = lineleft - start;
			++iterations;
		}


		/*if (pos < breakpoint)
			//printf("%s %d\n", line, pos );
			printline(line, pos);
		else {
			//printf("too long, needs folded");
			breakpos = breakline(line);
			printline(line, breakpos);
		}*/
	}
	
return 0;
}

int fold(char tofold[], int start) {
	char folded[MAXLINE];
	int i;
	printf("A: %d\n", start + FIXEDBREAK);
	for (i = start; i < start + FIXEDBREAK; ++i) {
		folded[i] = tofold[i];
	}
	printf("str: %s, i: %d\n",folded, i);
	return i;
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

/*void printline(char line[], int pos) {
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
}*/
