#include <stdio.h>

static char daytab[2][13] = {
    {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31},
    {0, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}
};

int day_of_year(int year, int month, int day) {
    int i, leap;

    leap = year%4 == 0 && year%100 != 0 || year%400 == 0;

    if(year < 0 || month < 1 || month > 12 || day < 0 || day > daytab[leap][day]) {
        printf("Invalid input.\n");
        return 1;
    } 
    for (i = 1; i < month; i++)
        day += daytab[leap][i];
    return day;
}

void month_day(int year, int yearday, int *pmonth, int *pday) {
    int i, leap;

    leap = year%4 == 0 && year%100 != 0 || year%400 == 0;
    if(year < 0 || yearday < 0 || (leap ? yearday > 366 : yearday > 365))
        printf("Invalid input.\n");
    else {
        for (i = 1; yearday > daytab[leap][i]; i++)
            yearday -= daytab[leap][i];
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
    int month2 = 4;
    int day2 = 31;

    day_of_year(year2, month2, day2);

    int year3 = 2024;
    int yearday3 = 97;
    int month3;
    int day3;

    month_day(year3, yearday3, &month3, &day3);  
    printf("month: %d, day: %d\n", month3, day3);
    
    int year4 = 2024;
    int yearday4 = 367;
    int month4;
    int day4;

    month_day(year4, yearday4, &month4, &day4);  
}


