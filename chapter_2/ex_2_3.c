#include <stdio.h>

/*
htoi converts a string of hex digits to its equivalent integer value
*/

#define NO 0
#define YES 1

int htoi (char s[]);

int main (int argc, char *argv[]) {
	int result;

	if (argc < 2) 
		printf("You need to input a string of hex digits\n");
	else {
		result = htoi(argv[1]);
		printf("result is %d\n", result);
	}
}

int htoi (char s[]) {
	int i = 0;
	int n = 0;
	int inHex = YES;
	int hexDigit;

	//handle the leading 0x or 0X
	if (s[i] == '0') {
		++i;
		if (s[i] == 'x' || s[i] == 'X')
			++i;
	}	

	for ( ; inHex == YES; ++i) {
		
		if (s[i] >= '0' && s[i] <= '9') 
			hexDigit = s[i] - '0';
		else if (s[i] >= 'a' && s[i] <= 'f') 
			hexDigit = s[i] - 'a' + 10;
		else if (s[i] >= 'A' && s[i] <= 'F') 
			hexDigit = s[i] - 'A' + 10;
		else
			inHex = NO;

		if (inHex == YES) { 
			n = n * 16 + hexDigit;
		}
	}

	return n;
}
