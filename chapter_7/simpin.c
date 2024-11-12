#include <stdio.h>

int main(void) {
    int in;

    while ((in = getchar()) != EOF) {
        putchar('*');
        putchar(in);
    }

    return 0;
}
