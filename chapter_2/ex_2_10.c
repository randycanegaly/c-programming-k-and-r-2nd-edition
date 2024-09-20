#include <stdio.h>

/*rewrite lower to use a conditional expression*/


int lower(int c);

int main() {
    int c = 'Z';

    int result = lower(c);
    printf("result is %c\n", result);
}

int lower(int c) {
   int result = (c >= 'A' && c <= 'Z') ? c + 'a' - 'A' : c;
   return result;
}


/* old lower ....
int lower(int c) {
    if(c >= 'A' && c <= 'Z')
        return c + 'a' - 'A';//upper comes before lower in the ASCII table
        //there is some number difference between an upper character and its lower
        //find that difference, add it to the upper and that number yields the lower
        //case version of the character
    else
        return c;
}*/
