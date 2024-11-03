#include <stdio.h>
#include <ctype.h>
#include <string.h>

int main(int argc, char *argv[]) {
    int c, up_or_down;
    up_or_down = 1; //upper 

    int (*convert) (int); //declare function pointer matching signature of toupper() and tolower()

    if (strstr(argv[0], "lower") != NULL)
        convert = &tolower;
    else if (strstr(argv[0], "upper") != NULL)
        convert = &toupper;
    else {
        printf("usage: compile to executable object file named either \"lower\" or \"upper\"\n");
        return 1;
    }

    while((c = getchar()) != EOF)
        putchar(convert(c));
    return 0;
}
