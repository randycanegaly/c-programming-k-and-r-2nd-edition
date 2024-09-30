#include <string.h>
#include <stdio.h>


void mystrncpy(char *s, char *t, int n);

int main(void) {
    char sshort[] = "dog";
    char sequal[] = "doggy";
    char slong[] = "doggies";
    
    char s[] = "canegaly";
    
    int i = 0;
    int n = 5;

    char *strings[3];
    strings[0] = sshort;
    strings[1] = sequal;
    strings[2] = slong;
    
    for (i = 0; i < 3; i++) {
        mystrncpy(s, strings[i], n);
        printf("%s\n", s); 
    }
}

void mystrncpy(char *s, char *t, int n) {
    int i, len;
    len = strlen(t);

    for (i = 0; i < n; i++)
        if (n > len - 1 && i > len -1)
            *s++ = '0';
        else
            *s++ = *t++;
}
