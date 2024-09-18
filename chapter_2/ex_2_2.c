#include <stdio.h>
#define MAX_LIN 80

/*replicate a for loop without a for loop
for (i=0; i<lim-1 && (c=getchar()) != '\n' && c ! = EOF; ++i)
I'll do it with enums*/

int main() {
	enum loop {OK, BREAK};
	enum loop counter = OK;
	int i = 0;
	char c;

	while (counter != BREAK) {
		c = getchar();
		
		if (i >=  MAX_LIN - 1) {
			counter = BREAK;
		}

		if (c == '\n') {
			counter = BREAK;
		}

		if (c == EOF) {
			counter = BREAK;
		}

		++i;
	}
}
