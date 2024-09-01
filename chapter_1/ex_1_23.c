#include <stdio.h>

/*Remove comments from C code text.
I am taking the simplest interpretation of the problem.
Don't show any part of a multiline comment or a single line comment
*/

int single_comment = 0;
int multi_comment = 0;

int in_a_comment(char c);

int main() {
	int c;
	
	while ((c = getchar()) != EOF) {
		in_a_comment(c);
	}
}

int in_a_comment(char c) {
	char prev;
	prev = c;
	if (single_comment == 0 && multi_comment == 0) {
		if (c == '/') {
			if ((c = getchar()) == '/') {
				single_comment = 1;
			} else if (c == '*')
				multi_comment = 1;
			else { 
				putchar(prev);
				putchar(c);
			}
		} else {
			putchar(c);
		}
	} else {
		if (c == '\n' && single_comment == 1) {
			single_comment = 0;
			multi_comment = 0;
		} else if (c == '*' && multi_comment == 1) {
			if ((c = getchar()) == '/')
				single_comment = 0;
				multi_comment = 0;
		}
	}
}
