#include <stdio.h>

#define LOWER 0
#define UPPER 300
#define STEP 20

float celsius(float fahr);

int main() {
	float fahr;

	fahr = LOWER;
    printf("Fahr    Celsius\n");//this line adds the table header
    while ( fahr <= UPPER) {
        printf("%3.0f    %6.1f\n", fahr, celsius(fahr));
        fahr = fahr + STEP;
    }
}

float celsius(float fahr) {
	return (5.0/9.0) * (fahr - 32.0);

}
