#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void reverse(char s[], int layer);

int main(void) {
    char str1[] = "hello"; 
    reverse(str1, 0);
    printf("%s\n", str1);
    
    char str2[] = "bump"; 
    reverse(str2, 0);
    printf("%s\n", str2);
    
    char str3[] = "a"; 
    reverse(str3, 0);
    printf("%s\n", str3);
    
    char str4[] = ""; 
    reverse(str4, 0);
    printf("%s\n", str4);
}
/* make a recursive version of reverse */

void reverse(char s[], int layer) {
/* every recursive function has a base case and recursive case
* the base case here is when the left tracker an the right tracker meet
* or, when left is no longer less than right
* the recursive case is when reverse is called again with a new layer value
*/
    int len = strlen(s);
    int left = layer;
    int right = len - 1 - layer;  
    int temp;

    if (left < right) {
        temp = s[left];
        s[left] = s[right];
        s[right] = temp;

        ++layer;

        reverse(s, layer);      
    }
}

