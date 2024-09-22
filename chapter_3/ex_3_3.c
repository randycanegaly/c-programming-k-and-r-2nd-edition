#include <stdio.h>

/*write expand(s1, s2)
 * that expands notations like a-z, etc. in s1 to abc.....xyz in s2
 *
 * if a-z is seen, need to recognize '-' and see what's before and after it
 * if the before character is "less than" the after character, then build a sequence
*/

#define MAX_ARR 10000
void expand(char s1[], char s2[]);

int main(void) {
    char s1[] = "a-za-b-ca-z0-9-a-z";
    //char s1[] = "a-za-b-ca-z0-9";
    //char s1[] = "-a-z";
    char s2[MAX_ARR];

    expand(s1, s2);
    printf("%s\n", s2);

}

void expand(char s1[], char s2[]) {
    char c;//character tracker
    int i, j;
    //a-z

    i = j = 0;
    while ((c = s1[i++]) != '\0')//c = a, s1[i] = dash
        if(s1[i] == '-' && s1[i + 1] >= c) {
            //character after dash is greater than c, we have a sequence
            i++;//now pointing to character after the dash
            while (c < s1[i])//build the sequence into s2 until the value of c hits the character after the dash
                    s2[j++] = c++;
            //put c in j, then increment the s2 index and increment to the next highes ASCII characteri
        } else//either didn't see a dash or we saw a dash but the character after the dash wasn't bigger than 
            //the one before the dash - no sequence then
            s2[j++] = c;//just put the first character seen in s2
    s2[j] = '\0';//terminate s2 properly
}
