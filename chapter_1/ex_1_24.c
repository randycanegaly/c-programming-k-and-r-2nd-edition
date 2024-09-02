#include <stdio.h>

/* Do rudimentary syntax check - unbalanced parentheses brackets and braces.
If in a comment, don't check.
*/

int single_comment = 0;
int multi_comment = 0;

int curlies = 0;
int squares = 0;
int parens = 0;

int in_a_comment(char c);
void check(char c);

int main() {
	char c;
	
	extern int curlies, squares, parens;
	curlies = 0;
	squares = 0;
	parens = 0;

	while ((c = getchar()) != EOF) {
		in_a_comment(c);

		//if we ever see a righthand one with out already having seen a lefthand one - error 
		if (curlies < 0) {
			printf("Unbalanced curly braces!");
			curlies = 0; //reset to be able to catch the same problem again
		}
		if (squares < 0) {
			printf("Unbalanced square braces!");
			squares = 0; //reset to be able to catch the same problem again
		}
		if (parens < 0) {
			printf("Unbalanced parentheses!");
			squares = 0; //reset to be able to catch the same problem again
		}
	}
	//at EOF, if count of any item is more than zero, then we saw more lefthands than righthands - error
	
	if (curlies > 0)
		printf("Unbalanced curly braces!");
	if (squares > 0)
		printf("Unbalanced square braces!");
	if (parens > 0)
		printf("Unbalanced parentheses!");
}

int in_a_comment(char c) {
	char prev;
	prev = c;
	if (single_comment == 0 && multi_comment == 0) { // not in a comment, watch for a character that might start one
		if (c == '/') {
			if ((c = getchar()) == '/') {//saw "//", in a comment, don't check
				single_comment = 1;
			} else if (c == '*')// saw "/*", in a comment, don't check
				multi_comment = 1;
			else { //we weren't in a comment so don't ignore the input character, check for brackets, etc.
				check(c);
			}
		} else {
			check(c); //didn't see a the character that signals start of a comment, so check
		}
	} else { //we are in a comment 
		if (c == '\n' && single_comment == 1) {// we are in a single comment, newline ends it
			single_comment = 0;
			multi_comment = 0;
			//get the next character and check it
			c = getchar();
			check(c);
		} else if (c == '*' && multi_comment == 1) {//we are in a multiline comment
			if ((c = getchar()) == '/') //just saw the two characters that end the multiline comment
				//get the next character and check it
				c = getchar();
				check(c);
		}
	}
}

void check(char c) {
	if (c == '{')
		++curlies;
	if (c == '}')
		--curlies;
	if (c == '[')
		++squares;
	if (c == ']')
		--squares;
	if (c == '(')
		++parens;
	if (c == ')')
		--parens;
}
