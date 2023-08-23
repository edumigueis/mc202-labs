#include <math.h>
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

int daysInMonth(int month, int year)
{
    int days[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    if (month == 2 && isLeapYear(year))
        return 29;
    return days[month - 1];
}

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

long long calculate_seconds(struct DateTime sunrise, struct DateTime sunset)
{
    const int secsPerDay = 86400;
    const int secsPerHour = 3600;
    const int secsPerMin = 60;

    // Convert date-times to seconds
    long totalSunriseHours = sunrise.hour * secsPerHour + sunrise.min * secsPerMin + sunrise.sec;
    long totalSunsetHours = sunset.hour * secsPerHour + sunset.min * secsPerMin + sunset.sec;
    long hourDiff = totalSunsetHours - totalSunriseHours;
    if(hourDiff < 0){
        sunset = addUpDays(sunset, 1);
    }
    long long totalSunrise = sunrise.year * 365 * secsPerDay + (sunrise.month - 1) * daysInMonth(sunrise.month - 1, sunrise.year) * secsPerDay + (sunrise.day - 1) * secsPerDay + totalSunriseHours;
    long long totalSunset = sunset.year * 365 * secsPerDay + (sunset.month - 1) * daysInMonth(sunset.month - 1, sunset.year) * secsPerDay + (sunset.day - 1) * secsPerDay + totalSunsetHours;

    // Calculate the difference in seconds
    return totalSunset - totalSunrise;
}

int main(void)
{
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
        if (sHour != 99 && !isSunset)
        {
            sunset = (struct DateTime){day, month, year, sHour, sMin, sSec};
            timePassed += calculate_seconds(sunrise, sunset);
            isSunset = 1;
        }
    }
    struct DateTime finalDate = addUpDays(start, timePassed / 43200);
    printf("%lld", timePassed);
    printf("%hd/%hd/%hd\n", finalDate.day, finalDate.month, finalDate.year);
    return 0;
}