#include <string.h>
#include <stdio.h>


void myreverse(char *s);
int mystrindex(char *s, char *t);

int main(void) {
    char srev[] = "doggya";
    char target[] = "doggies";
    char source[] = "ggi";
    char source2[] = "ggz";
    
    myreverse(srev);

    printf("reversed: %s\n", srev);
    
    int index = mystrindex(target, source);  
    if (index != -1 )
        printf("source is in target at index %d\n", index);
    else
        printf("source not found in target.\n"); 
    
    index = mystrindex(target, source2);  
    if (index != -1 )
        printf("source2 is in target at index %d\n", index);
    else
        printf("source2 not found in target.\n"); 
}

//reverse: reverse string s in place
void myreverse(char *s) {
    int c;
    char *start = s; 
    char *end = s + strlen(s) - 1; 
    
    while(start < end) { //this works because start and end are pointers, they hold address values
        //start holds increasing address values, end holds decreasing address values:w
        c = *start;
        *start = *end;
        *end = c;
        --end;
        ++start;
    } 
}

int mystrindex(char *s, char *t) {
//walk s, check for if char at s matches first char in t
//if match, remember index in s
//if match, walk both s and t, checking at each position change for a match
//if end of t is reached, return remembered index
//if no match before end of t, set remembered index back to -1

    int tindex = -1;
    int tlen = strlen(t);
    int i = 0;

    while(*s != *t) {
        s++;
        i++;
    }
    tindex = i;
    //printf("*s: %c, i: %d, tindex: %d\n", *s, i, tindex);
    while(*s == *t) {
        s++;
        t++;
    } 

    //printf("*s: %c, i: %d, tindex: %d\n", *s, i, tindex);

    if(*t)
        tindex = -1;

    return tindex;
}
