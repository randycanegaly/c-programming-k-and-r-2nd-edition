#include <stdio.h>

/*
count digits, whitespace and others
*/

int main() {
	int c, i, nwhite, nother;
	int ndigit[10];//an array of size 10, for digits 0 through 9

	nwhite = nother = 0;
	for(i =0; i < 10; ++i) {
		ndigit[i] = 0;//initialize array to all zeroes
	}

	while ((c = getchar()) != EOF) {
		if (c >= '0' && c <= '9')
			++ndigit[c-'0'];//See NOTES below //increment the element at the digit's value index
		else if (c == ' ' || c == '\n' || c == '\t')
			++nwhite;//increment count of white space characters
		else
			++nother;//increment the count of other characters
	}

	printf("digits =");
	for (i=0; i < 10; ++i)
		printf(" %d", ndigit[i]);//print the array elements for digit counts in order
	printf(", white space = %d, other = %d\n", nwhite, nother);//print counts for other character types
}



/*
NOTES:
'9' is a char literal, it represents a single character, takes up one byte of memory
If I do --> int ascii_value = '9'; then I am assigning the char to an int
ascii_value is assigned the mapping of the '9' character's numerical value in ASCII encoding
That numeric value is 57
This is all similar for '0', whose ASCII value is 48
The expression --> ascii_value - '0' implicitly converts '0' to an int, 48 and so the value
of the expression is 57 - 48, which is 9, the "numeric value" of '9'

If I type 8 at the keyboard, c = getchar() returns an int, the ASCII value of 8, which is 56
In c >= '0', I'm using '0' like it's an int, so an implicit conversion to an int, its ASCII value happens
So, c >= '0' is really 56 >= 48 which is true, so the condition holds
*/
