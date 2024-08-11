#include <stdio.h>

int main() {
	printf("hello, world!\n");
}

/*
If ; is left of line # 4 then this error is seen on compile
exercise_1_1.c: In function ‘main’:
exercise_1_1.c:4:34: error: expected ‘;’ before ‘}’ token
    4 |         printf("hello, world!\n")
      |                                  ^
      |                                  ;
    5 | }
      | ~                             

If a quote is left out in line #4 then this error is seen
exercise_1_1.c: In function ‘main’:
exercise_1_1.c:4:16: warning: missing terminating " character
    4 |         printf("hello, world!\n);
      |                ^
exercise_1_1.c:4:16: error: missing terminating " character
    4 |         printf("hello, world!\n);
      |                ^~~~~~~~~~~~~~~~~~
exercise_1_1.c:5:1: error: expected expression before ‘}’ token
    5 | }
      | ^
exercise_1_1.c:4:16: error: expected ‘;’ before ‘}’ token
    4 |         printf("hello, world!\n);
      |                ^
      |                ;
    5 | }

Leaving off the function return type in line #3 gives this warning
exercise_1_1.c:3:1: warning: return type defaults to ‘int’ [-Wimplicit-int]
    3 | main() {
      | ^~~~ 
*/


