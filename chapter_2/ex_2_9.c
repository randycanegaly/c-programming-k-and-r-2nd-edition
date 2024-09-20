#include <stdio.h>

/*explanation ...
 * x =      1010
 * x-1 =    1001
 * & them together and you get 1000, right most bit removed, count one 1-bit
 * repeat
 * x is now 1000
 * x-1 = 0111
 * & them together and you get 0000, right most bit removed, count is now two 1-bits
 */


int bitcount(unsigned x);

int main() {
    int x = 057;//110111

    printf("number of 1-bits in %o is %d\n", x, bitcount(x));
}

int bitcount(unsigned x) {
    int b;

    for (b = 0; x != 0; x &= x - 1)
        b++;
    return b;
}
