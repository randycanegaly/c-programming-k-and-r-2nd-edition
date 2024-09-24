#include <stdio.h>
#include <ctype.h>

double atof(char s[]);

char s[] = "12.03";

int main(void) {
    printf("%f\n", atof(s));
}

double atof(char s[]) {
    double val, power;
    int i, sign;

    for (i = 0; isspace(s[i]); i++)//walk s, doing nothing while we see whitespace
        ;
    
    sign = (s[i] == '-') ? -1 : 1;//if the first real character is a dash, set sign to be -1
    
    if (s[i] == '+' || s[i] == '-')//we already figured out neg or pos, skip those symbols
        i++;
    
    for (val = 0.0; isdigit(s[i]); i++) {//walk s, stop when first not digit seen
        val = 10.0 * val + (s[i] - '0');
        //printf("val: %f\n", val);
        //first time = 10 * 0 + 49 - 48 = 1
        //second time = 10 * 1 + 50 - 48 = 12 
    }
    
    if (s[i] == '.')//see a ., skip it
        i++;
    
    //now should be in fractional part
    for (power = 1.0; isdigit(s[i]); i++) {
        val = 10.0 * val + (s[i] -'0');
        //third ... 10 * 12 + 48 -48 = 120
        //fourth .. 10 * 120 + 51 - 48 = 1203
        power *= 10.0;//counts number of digits to right of decimal
        //first .... power = 1.0 * 10 = 10.0
        //second ... power = 10.0 * 10 = 100.0
    }
    return sign * val/power;//1 * 1203 / 100 = 12.03
}






