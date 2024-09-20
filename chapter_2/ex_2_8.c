#include <stdio.h>

/*rotate an integer n bits to the right*/

int wordlength(void);

int main() {
    int x = 043; //100011
    int y = x;
    int n = 34;
    printf("rotating x %d digits to the right\n", n);
    int result, right_bits;

    int num_bits = wordlength();
    printf("number of bits is, or, the length of a word on this machine is: %d\n", num_bits);
    

    //100011
    //001000 <- x shifted right n positions
    //need to or shifted x with the old n rightmost bits shifted all the way to the left
    //001000 | 110000 = 111000
    //build 110000
        //~0 = 111111
        //~0 << n = 111100
        //~(~0 << n) = 000011
        //~(~0 << n) & x = 000011
        //(~(~0 << n)) & x << (numbits - n) = 110000
    n = n % num_bits;

    right_bits = ~(~0 << n) & x; 
    right_bits = right_bits << (num_bits - n);
    //printf("rb: %o\n", right_bits);

    printf("x: %o\n", x);
    x >>= n;//shift x right n bits, 0s will fill in on the left
    //printf("x: %o\n", x);

    result = x | right_bits;
    printf("result: %o\n", result);
}

int wordlength(void) {
    int i;

    unsigned v = (unsigned) ~0;//unsigned word, all 1s

    for(i = 1; (v >>= 1) > 0; i++)
        ;

    return i;
}
