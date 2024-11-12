#include <stdarg.h>
#include <stdio.h>
#include <ctype.h>

#define LOCALFMT 100
#define MAXLINE 100

void minscanf(char *, ...);
int mygetline(char *s, int lim);

int main(void) {
    char line[MAXLINE]; 
    int ival, len;
    //double dval;
    float dval;

    printf("enter an integer\n");
    minscanf("%d\n", &ival, &dval);
    printf("you entered %d\n", ival);
    
    printf("enter another integer\n");
    minscanf("%i\n", &ival, &dval);
    printf("you entered %d\n", ival);
    
    printf("enter a float\n");
    minscanf("%f\n", &ival, &dval);
    printf("you entered %f\n", dval);

}

/* minscanf: minimal scang with variable argument list */
void minscanf(char *fmt, ...) {
	va_list ap; 
	char *p, *sval; 
    char localfmt[LOCALFMT];
	int i, *ival;
	double *qval;
    unsigned *uval;

	va_start(ap, fmt);

	for (p = fmt; *p; p++) { 
		if (*p != '%') {
			putchar(*p);
			continue;
		} 
	    i = 0;
        localfmt[i++] = '%';
        while (*(p+1) && !isalpha(*(p+1)))
            localfmt[i++] = *++p;
        localfmt[i++] = *(p+1);
        localfmt[i] = '\0';
		
        switch (*++p) {
        case 'd':
			ival = va_arg(ap, int *);
			scanf(localfmt, ival);
			break;
        case 'i':
			ival = va_arg(ap, int *);
			scanf(localfmt, ival);
			break;
		case 'f':
			qval = va_arg(ap, double *);
			scanf(localfmt, qval);
			break;
		/*case 's':
			sval = va_arg(ap, char *);
			printf (localfmt, sval);
			break;	
		case 'o':
			uval = va_arg(ap, unsigned);
            printf (localfmt, uval);
			break;*/
		default:
			printf (localfmt);
			break;
		}
	}
	va_end(ap);
}

int mygetline(char *s, int lim) {
    int c;
    char *t = s;

    while (--lim > 0 && (c = getchar()) != EOF && c != '\n')//pull chars from input until EOF or newline
        *s++ = c;//set the thing s points to equal to c, then increment s pointer to the next element
    if (c == '\n')
        *s++ = c;//do the same if input character is a newline
    *s = '\0';//terminate   what happens here if EOF?
    return s - t;
}
