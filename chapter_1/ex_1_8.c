#include <stdio.h>

int main() {
	int c, nb, nt, nl;
	nb = nt = nl = 0;

	while ((c = getchar()) != EOF) {
		if (c == ' ') {
			++nb;
		}
		if (c == '\t') {
			++nt;
		}
		if (c == '\n') {
			++nl;
		}
	}

	printf("blanks: %d tabs: %d lines: %d", nb, nt, nl);
	return 0;
}
