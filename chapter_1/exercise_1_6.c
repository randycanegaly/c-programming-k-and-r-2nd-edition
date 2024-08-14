#include <stdio.h>

/*show that getchar() != EOF returns 0 or 1
If I write c = getchar() != EOF, then by operator precedence,
this is the same as c = (getchar() != EOF,
which means c can only be 0 or 1*/

int main() {
	int c;

	while(c = getchar() != EOF) {
		printf("%d\n", c);
	}
	printf("At EOF, c is %d\n", c);
}
