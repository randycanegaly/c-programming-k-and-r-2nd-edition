#include <stdio.h>

int invert(unsigned x, int p, int n);

/*
Take xxxnnx and 
	 000110

and exlusive-or them together
p = 2
n = 2

build 000110

~0 = 111111
~0 << n 111100
~(~0 << 2) = 000011
~(~0 << 2) << (p + 1 -n) = 000110
*/

int main() {
	unsigned x = 0441;
	int p = 4;
	int n = 3;

	int result = invert(x, p, n);

	printf("result: %o\n", result);
}

int invert(unsigned x, int p, int n) {
	int inverter = ~(~0 << n) << (p + 1 -n);
	//printf("%o\n", x_cleared);
	//printf("%o\n", y_shifted);
	return x ^ inverter; 
}
