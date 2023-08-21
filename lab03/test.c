#include <stdio.h>

struct DateTime
{
    int day;
    int month;
    int year;
    int hour;
    int min;
    int sec;
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

struct DateTime addDays(struct DateTime date, int days)
{
    while (days > 0)
    {
        int daysInCurrentMonth = daysInMonth(date.month, date.year);
        if (days >= daysInCurrentMonth - date.day + 1)
        {
            days -= daysInCurrentMonth - date.day + 1;
            date.day = 1;
            if (date.month == 12)
            {
                date.month = 1;
                date.year++;
            }
            else
            {
                date.month++;
            }
        }
        else
        {
            date.day += days;
            days = 0;
        }
    }
    return date;
}

int main()
{
    struct DateTime currentDate = {0, 0, 0, 0, 0, 0};
    struct DateTime sunrise, sunset;

    while (scanf("%d/%d/%d %d:%d:%d %d:%d:%d", &currentDate.day, &currentDate.month, &currentDate.year,
                 &sunrise.hour, &sunrise.min, &sunrise.sec,
                 &sunset.hour, &sunset.min, &sunset.sec) == 9)
    {
        if (sunrise.hour != 99 && sunset.hour != 99)
        {
            int daylight_seconds = (sunset.hour - sunrise.hour) * 3600 + (sunset.min - sunrise.min) * 60 + (sunset.sec - sunrise.sec);
            int days_passed = daylight_seconds / (12 * 3600);

            currentDate = addDays(currentDate, days_passed);
        }
    }

    printf("%d/%d/%d\n", currentDate.day, currentDate.month, currentDate.year);

    return 0;
}
