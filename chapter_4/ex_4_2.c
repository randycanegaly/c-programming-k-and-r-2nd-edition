#include <stdio.h>
#include <ctype.h>

//Extend atof to handle scientific notation of the form 123.45e-6

double atof(char s[]);

char s[] = "12.03";
char s_exp_neg[] = "12.03e-2";
char s_exp_pos[] = "12.03e+2";

int main(void) {
    printf("%f\n", atof(s));
    printf("%f\n", atof(s_exp_neg));
    printf("%f\n", atof(s_exp_pos));
}

double atof(char s[]) {
    double val, power, result;
    int i, j, sign, exp_sign, exp, exp_pow;

    for (i = 0; isspace(s[i]); i++)
        ;
    
    sign = (s[i] == '-') ? -1 : 1;
    
    if (s[i] == '+' || s[i] == '-')
        i++;
    
    for (val = 0.0; isdigit(s[i]); i++) {
        val = 10.0 * val + (s[i] - '0');
    }
    
    if (s[i] == '.')
        i++;
    
    for (power = 1.0; isdigit(s[i]); i++) {
        val = 10.0 * val + (s[i] -'0');
        power *= 10.0;
    }

    result = sign * val/power;

    if (s[i++] == 'e') {
        if(s[i] == '-')
            exp_sign = -1;
        else if (s[i] == '+')
            exp_sign = 1;

        ++i;
        //assume only one exponent digit
        exp = s[i] - '0';

        exp_pow = 1;
        for (j = 0; j < exp; j++)
             exp_pow *= 10;

        if (exp_sign == -1)
            result /= exp_pow;
        else
            result *= exp_pow;
    }
    
    return result;
}






