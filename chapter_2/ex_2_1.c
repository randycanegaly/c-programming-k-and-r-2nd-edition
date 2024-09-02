#include <limits.h>
#include <stdio.h>

/* Print min and max values for: 
	- signed char
	- signed short
	- signed int
	- signed long
	- unsigned char
	unsigned short
	- unsigned int
	- unsigned long
*/

int main() {
	printf("min signed char: %d\n", SCHAR_MIN); 
	printf("max signed char: %d\n", SCHAR_MAX); 
	printf("max unsigned char: %u\n", UCHAR_MAX); 
	printf("min signed short: %d\n", SHRT_MIN );
	printf("max signed short: %d\n", SHRT_MAX);
	printf("max unsigned short: %u\n", USHRT_MAX);
	printf("min signed int: %d\n", INT_MIN );
	printf("max signed int: %d\n", INT_MAX);
	printf("max unsigned int: %u\n", UINT_MAX);
	printf("min signed long: %ld\n", LONG_MIN );
	printf("max signed long: %ld\n", LONG_MAX);
	printf("max unsigned long: %lu\n", ULONG_MAX);
}
