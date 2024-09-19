#include <stdio.h>

int setbits(unsigned x, int p, int n, unsigned y);

/*
Take xxxxxx and 
	 yyyyyy

and move these n's in y yyyynn
into these positions in x xnnxxx

to do that we need to transform x to x00xxx
and tranform y to 0nn000
and bitwise or them together so that the 0s in x get replaced
and the xs in x are preserved

p = 4, n = 2
x00xxx | 0nn000, where the ns are the rightmost 2 values of y

xxxxxx -> x00xxx
xxxxxx & 100111

build 100111
~0 = 111111
~0 << n = 111100
~(~0 << n) = 000011
~(~0 << n) << p + 1 - n 
~(~0 << n) << 3   011000
~(~(~0 << n) << 3)   100111
x & ~(~(~0 << n) << 3)   x00xxx YES!


build 0nn000

~0 = 111111
~0 << n
~0 << 2 = 111100
~(~0 << 2) = 000011
y & ~(~0 << 2) = 0000yy
y & ~(~0 << 2) << p + 1 -n = 0yy000

x00xxx | 0yy000 = xyyxxx YES!
*/

int main() {
	unsigned x = 0362;
	unsigned y = 0777;
	int p = 3;
	int n = 2;

	int result = setbits(x, p, n, y);

	printf("result: %o\n", result);
}

int setbits(unsigned x, int p, int n, unsigned y) {
	int x_cleared = x & ~(~(~0 << n) << (p + 1 - n));
	int y_shifted = (y & ~(~0 << n)) << (p + 1 - n);
	//printf("%o\n", x_cleared);
	//printf("%o\n", y_shifted);
	return x_cleared | y_shifted;
}
