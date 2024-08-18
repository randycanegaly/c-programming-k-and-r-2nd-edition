#include <stdio.h>

/*
In output, replace a tab with \t, a backspace with \b and backslash with \\.
*/

int main() {

	int c;

	while((c = getchar()) != EOF ) {
			if (c == '\t') {
				printf("\\t");
			}
			else if (c == '\b' || c == 127) {
				printf("\\b");//this doesn't work. backspace causes no character value to be output
				//I checked this with a simple program that just output any character input
				//and backspace does nothing
			}
			else if (c == '\\') {
				printf("\\\\");
			}
			else
				putchar(c);
		}
	
	return 0;
}
