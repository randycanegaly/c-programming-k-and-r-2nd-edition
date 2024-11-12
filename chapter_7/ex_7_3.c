#include <stdarg.h>
#include <stdio.h>
#include <ctype.h>

#define LOCALFMT 100

void minprintf(char *, ...);

int main(void) {
    char *test1, *test2, *test3, *test4, *test5, *str;
    int itest = 101;
    int itest2 = 992;
    double dtest = 101.01;
    unsigned otest = 24;
    
    test1 = "%d\n";
    test2 = "%.4f\n";
    test3 = "%s\n";
    test4 = "%6i\n";
    test5 = "%o\n";
    str = "Luna";

    minprintf(test1, itest);		
	minprintf(test2, dtest);		
	minprintf(test3, str);		
	minprintf(test4, itest2);		
	minprintf(test5, otest);		
}

/* Add the facilities of printf() that are missing */

/* minprintf: minimal printf with variable argument list */
void minprintf(char *fmt, ...) {
	va_list ap; /* points to each unamed arg in turn */
	char *p, *sval; 
    char localfmt[LOCALFMT];
	int i, ival;
	double dval;
    unsigned uval;

	va_start(ap, fmt);

	for (p = fmt; *p; p++) { 
		if (*p != '%') {
			putchar(*p);
			continue;
		} 
	    i = 0;
        localfmt[i++] = '%';
        while (*(p+1) && !isalpha(*(p+1))) //walk the string up to the letter format designator
            localfmt[i++] = *++p; //grabs the next character and puts in local format
        localfmt[i++] = *(p+1);//next one is the format letter, put it in local format
        localfmt[i] = '\0';//terminate the local format string
		switch (*++p) {
        case 'd':
			ival = va_arg(ap, int);
			printf(localfmt, ival);
			break;
        case 'i':
			ival = va_arg(ap, int);
			printf(localfmt, ival);
			break;
		case 'f':
			dval = va_arg(ap, double);
			printf (localfmt, dval);
			break;
		case 's':
			sval = va_arg(ap, char *);
			printf (localfmt, sval);
			break;	
		case 'o':
			uval = va_arg(ap, unsigned);
            printf (localfmt, uval);
			break;
		default:
			printf (localfmt);
			break;
		}
	}
	va_end(ap);
}
