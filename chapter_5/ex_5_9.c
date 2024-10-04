#include <stdio.h>

static char daytab[2][13] = {
    {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31},
    {0, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}
};

int day_of_year(int year, int month, int day) {
    int leap;
    char *p;

    leap = year%4 == 0 && year%100 != 0 || year%400 == 0;

    if(year < 0 || month < 1 || month > 12 || day < 0 || day > daytab[leap][day]) {
        printf("Invalid input.\n");
        return 1;
    } 
    
    p = daytab[leap];

    while (month--)
        day += *p++;
    
    return day;
}

void month_day(int year, int yearday, int *pmonth, int *pday) {
    int i, leap;
    char *p;

    i = 0;

    leap = year%4 == 0 && year%100 != 0 || year%400 == 0;
    if(year < 0 || yearday < 0 || (leap ? yearday > 366 : yearday > 365))
        printf("Invalid input.\n");
    else {
        p = daytab[leap];

        while(yearday > *p) {
            yearday -= *p++;
            i++;      
        }

        *pmonth = i;
        *pday = yearday; 
    }
}

int main(void) {
    int year = 2024;
    int month = 4;
    int day = 5;

    printf("year day: %d\n", day_of_year(year, month, day));
    
    int year2 = 2024;
    int yearday2 = 97;
    int month2;
    int day2;

    month_day(year2, yearday2, &month2, &day2);  
    printf("month: %d, day: %d\n", month2, day2);
}


