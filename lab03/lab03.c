#include <stdio.h>

struct DateTime
{
    short day;
    short month;
    short year;
    short hour;
    short min;
    short sec;
};

int isLeapYear(int year)
{
    return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}

// Returns how many days are in a given month
int daysInMonth(int month, int year)
{
    int days[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    if (month == 2 && isLeapYear(year))
        return 29;
    return days[month - 1];
}

// Adds days to date considering month durations and leap years
struct DateTime addUpDays(struct DateTime date, int numberOfDays)
{
    while (1)
    {
        int daysInCurrentMonth = daysInMonth(date.month, date.year);
        if (date.day + numberOfDays <= daysInCurrentMonth)
        {
            date.day += numberOfDays;
            break;
        }
        else
        {
            numberOfDays -= (daysInCurrentMonth - date.day + 1);
            date.day = 1;
            if (date.month == 12)
            {
                date.month = 1;
                date.year++;
            }
            else
                date.month++;
        }
    }
    return date;
}

long long calculateSeconds(struct DateTime sunrise, struct DateTime sunset)
{
    // Consts useful for the method
    const int secsPerDay = 86400;
    const int secsPerHour = 3600;
    const int secsPerMin = 60;

    // Convert date-times to seconds
    long totalSunriseHours = sunrise.hour * secsPerHour + sunrise.min * secsPerMin + sunrise.sec;
    long totalSunsetHours = sunset.hour * secsPerHour + sunset.min * secsPerMin + sunset.sec;
    // If sunset is before sunrise(in hours) it means it happened on the next day
    if (totalSunsetHours - totalSunriseHours < 0)
    {
        sunset = addUpDays(sunset, 1);
    }
    // Years and days taken into account
    long long totalSunrise = sunrise.year * 365 * secsPerDay + sunrise.day * secsPerDay + totalSunriseHours;
    long long totalSunset = sunset.year * 365 * secsPerDay + sunset.day * secsPerDay + totalSunsetHours;
    // Months(with different durations) taken into account
    for (int m = 1; m < sunrise.month; m++)
        totalSunrise += daysInMonth(m, sunrise.year) * secsPerDay;
    for (int m = 1; m < sunset.month; m++)
        totalSunset += daysInMonth(m, sunset.year) * secsPerDay;
    // Calculate the difference in seconds
    return totalSunset - totalSunrise;
}

int main(void)
{
    // Initialize
    struct DateTime start = {0, 0, 0, 0, 0, 0};
    struct DateTime sunset = {0, 0, 0, 0, 0, 0};
    struct DateTime sunrise = {0, 0, 0, 0, 0, 0};

    short day, month, year, rHour, rMin, rSec, sHour, sMin, sSec = 0;
    long long timePassed = 0;
    short first = 1;
    short isSunset = 1;

    while (scanf("%02hd/%02hd/%04hd %02hd:%02hd:%02hd %02hd:%02hd:%02hd",
                 &day, &month, &year,
                 &rHour, &rMin, &rSec,
                 &sHour, &sMin, &sSec) == 9)
    {
        // First date has to be saved for future counting
        if (first)
        {
            start.day = day;
            start.month = month;
            start.year = year;
            first = 0;
        }
        if (rHour != 99 && isSunset)
        {
            sunrise = (struct DateTime){day, month, year, rHour, rMin, rSec};
            isSunset = 0;
        }
        // Time is only summed up if there was a sunset(closing in the light cycle)
        // Because otherwise it is dark or in continuous light
        if (sHour != 99 && !isSunset)
        {
            sunset = (struct DateTime){day, month, year, sHour, sMin, sSec};
            timePassed += calculateSeconds(sunrise, sunset);
            isSunset = 1;
        }
    }
    // Divide by number of seconds in 12 hours
    struct DateTime finalDate = addUpDays(start, timePassed / 43200);
    printf("%hd/%hd/%hd\n", finalDate.day, finalDate.month, finalDate.year);
    return 0;
}