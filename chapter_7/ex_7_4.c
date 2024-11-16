#include <stdarg.h>
#include <stdio.h>
#include <ctype.h>

#define LOCALFMT 100
#define MAXLINE 100

void minscanf(char *, ...);

int main(void) {
    int int1, int2, oct1;
    float float1;
    char string1[MAXLINE];
    
    printf("Enter this string:\n");
    printf("8 12 34.67\n");
    minscanf("%d %d %f\n", &int1, &int2, &float1);
    printf("You entered: %d %d %f\n", int1, int2, float1);
    
    printf("Enter this string:\n");
    printf("377 dog\n");
    minscanf("%o %s\n", &oct1, string1);
    printf("You entered: %o which is %d in decimal, %s\n", oct1, oct1, string1);
}

/* minscanf: minimal scang with variable argument list */
void minscanf(char *fmt, ...) {
	va_list ap; 
	char *p, *sval;
    char localfmt[LOCALFMT];
	int c, i, *ival;
    unsigned int *uval;
    double *dval;
    int *dummy;

	i = 0;
    va_start(ap, fmt);

	for (p = fmt; *p; p++) { 
		if (*p != '%') {
			localfmt[i++] = *p;
			continue;
		} 
        localfmt[i++] = '%';
        while (*(p+1) && !isalpha(*(p+1)))
            localfmt[i++] = *++p;
        localfmt[i++] = *(p+1);
        localfmt[i] = '\0';
		
        switch (*++p) {
        case 'd':
        case 'i':
            ival = va_arg(ap, int *);
			scanf(localfmt, ival);
			break;
		case 'f':
			dval = va_arg(ap, double *);
			scanf(localfmt, dval);
            //printf("%f\n", *dval);
			break;
		case 's':
			sval = va_arg(ap, char *);
			scanf(localfmt, sval);
			break;	
		case 'o':
			uval = va_arg(ap, unsigned int *);
            scanf(localfmt, uval);
			break;
		default:
			scanf(localfmt);
			break;
		}
        i = 0;
	}
	va_end(ap);
}
