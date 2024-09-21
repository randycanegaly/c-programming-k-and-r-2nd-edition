#include <stdio.h>

#define MAX_ARR 20
/* write a function escape(s, t) that converts newline and tab characters
 * in string s into their visible representations \n and \s while copying
 * characters from t into s. Use a switch statement. Also, create an unescape()
 * function to do the opposite
 */

int escape(char s[], char t[]);
int unescape(char s[], char t[]);

int main(void) {
    char t1[] = {'a', 'b', 'C', 'D', '1', '9', '\t', '\n', '\0'};
    char s1[MAX_ARR];
    char s2[MAX_ARR];
    char t2[] = "abcd19\t\n";
    
    escape(s1, t1);
    printf("%s\n", s1);
    
    unescape(s2, t2);
    printf("unescaped string is --%s--\n", s2);
}

int escape(char s[], char t[]) {
    //have an array of actual characters
    //walk the array and for each '\n' and '\t'
    //character, create the corresponding individual visual character pieces
    //put each character walked in t into s
    

    int i = 0;
    int j = 0;
    while (t[i] != '\0') {
        switch (t[i]) {
        case '\n':
            s[j++] = '\\';
            s[j++] = 'n';
            break;
        case '\t':
            s[j++] = '\\';
            s[j++] = 't';
            break;
        default:
            s[j++] = t[i];
            break;
        }
        ++i;
    }

    s[j] = '\0';
}

int unescape(char s[], char t[]) {
    //have a string
    //walk the string and for each '\n' and '\t'
    //character, create the corresponding actual char
    //put each string element into s
    

    int i = 0;
    int j = 0;
    while (t[i] != '\0') { 
        if (t[i] != '\\')//character not a backlash just goes into s
            s[j++] = t[i];
        else //see a backslash
            switch (t[++i]) {//look at character after the backslash
            case 'n':
                s[j++] = '\n';
                break;
            case 't':
                s[j++] = '\t';
                break;
            case '\\'://it's a backslash
                s[j++] = '\\';
                break;
            default://seeing a backslash followed by something else, so put that next
                //character in s
                s[j++] = t[i];
            }
        ++i;
    }

    s[i] = '\0';
}

