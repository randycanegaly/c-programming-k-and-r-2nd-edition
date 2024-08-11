#include <stdio.h>

int main() {
	printf("hello, world!\z");//in exercise 1, the string had \n
				  //switching it to \z, a character not mentioned
				  //for escaping in the text yields the error below upon compile
}

/*
exercise_1_2.c: In function ‘main’:
exercise_1_2.c:4:33: warning: unknown escape sequence: '\z'
    4 |         printf("hello, world!\z");//in exercise 1, the string had \n
      | 
*/



