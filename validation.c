#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include <windows.h>
#include "structs.h"
#include "functions.h"

// Case Handling
int casesensitve(char *str1, char *str2)
{
    while (*str1 && *str2)
    {
        if (tolower((unsigned char)*str1) != tolower((unsigned char)*str2))
        {
            return (tolower((unsigned char)*str1) - tolower((unsigned char)*str2));
        }
        str1++;
        str2++;
    }
    return tolower((unsigned char)*str1) - tolower((unsigned char)*str2);
}

//Fixing the first element problem in most enteries
void clearInputBuffer() 
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

//Helps in validating date
int isValidDate(char *date) 
{
    int day, month, year;
    if (sscanf(date, "%d-%d-%d", &day, &month, &year)!= 3) 
    {
        return 0;
    }
    if (month < 1 || month > 12) {
        return 0;
    }
    //Leap Year
    if (month == 2) 
    {
        if (strlen(date)!=10&&date[2]!='-'&&date[5] != '-')
        return 0;
        int leapYear = (year % 4 == 0 && (year % 100 != 0 || year % 400 == 0));

        if (leapYear) 
        {
            if (day < 1 || day > 29) 
            {
                return 0;
            }
        } 
        else 
        {
            if (day < 1 || day > 28) {
                return 0;
            }
        }
    } else if (month == 4 || month == 6 || month == 9 || month == 11) { // Months with 30 days
        if (day < 1 || day > 30) {
            return 0;
        }
    } else 
    {
        if (day < 1 || day > 31)
        {
            return 0;
        }
    }
    if (year > 2050 || year < 2024) 
    {
        return 0;
    }
    return 1;
}
