#include <stdarg.h>
#include <stdio.h>

void minprintf(char *, ...);

int main(void) {
    char *test1, *test2, *test3, *str;
    int itest = 101;
    double dtext = 101.01;
    
    test1 = "%d\n";
    test2 = "%f\n";
    test3 = "%s\n";
    str = "Luna";

    minprintf(test1, itest);		
	minprintf(test2, dtext);		
	minprintf(test3, str);		
}

/* minprintf: minimal printf with variable argument list */
void minprintf(char *fmt, ...) {
	va_list ap; /* points to each unamed arg in turn */
	char *p, *sval; 
	int ival;
	double dval;

	va_start(ap, fmt); /* make ap point to the 1st unnamed arg. va_start
						  is a macro that enables the va_list so that it can
						  be used to access the variable argument list.
						  the second argument to va_start is the last parameter in the 
						  function signature before the ... of variable argument list */
	for (p = fmt; *p; p++) { //init pointer p to fmt, as long as pointer p is not
							 //null, increment pointer - do pointer math
		if (*p != '%') {//if the thing p points to is not %, emit the character
			putchar(*p);
			continue;	//go immediately and do the next iteration of the loop
		} 
		switch (*++p) {//if we got to here, then we just saw a %
					   //same operator precedence, right to left, so dereference
					   //p and then increment - means move to the next character
					   //and use that character as input for the switch
		case 'd'://see %d
			ival = va_arg(ap, int);//va_arg retrieves the next argument from
								   //the variable argument list
								   //its second argument is the type to be 
								   //retrieved
			printf("%d", ival);
			break;
		case 'f':
			dval = va_arg(ap, double);
			printf ("%f", dval);
			break;
		case 's':
			for (sval = va_arg(ap, char *); *sval; sval++)
				putchar(*sval);
			break;	
		default:
			putchar(*p);
			break;
		}
	}
	va_end(ap);
}
