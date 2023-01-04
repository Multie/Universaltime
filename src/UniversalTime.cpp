#include "Arduino.h"
#include "UniversalTime.h"

UniversalTime::UniversalTime()
{
    Year = 0;
    Month = 0;
    Day = 0;
    Hour = 0;
    Minute = 0;
    Second = 0;
    Millisecond = 0;
    Microsecond = 0;
}

// Get
int UniversalTime::getYear()
{
    return Year;
}
int UniversalTime::getMonth()
{
    return Month;
}
int UniversalTime::getDay()
{
    return Day;
}
int UniversalTime::getHour()
{
    return Hour;
}
int UniversalTime::getMinute()
{
    return Minute;
}
int UniversalTime::getSecond()
{
    return Second;
}
int UniversalTime::getMillisecond()
{
    return Millisecond;
}
int UniversalTime::getMicosecond()
{
    return Microsecond;
}
// Set
void UniversalTime::setYear(int year)
{
    Year = year;
    LeapYear = ((Year % 4 == 0 && Year % 100 != 0) || Year % 400 == 0);
}
void UniversalTime::setMonth(int month)
{
    if (month > 12)
    {
        month = 12;
    }
    else if (month < -12)
    {
        month = -12;
    }
    Month = month;
}
void UniversalTime::setDay(int day)
{
    if (day > 30)
    {
        day = 30;
    }
    else if (day < -30)
    {
        day = -30;
    }
    Day = day;
}
void UniversalTime::setHour(int hour)
{
    if (hour > 24)
    {
        hour = 24;
    }
    else if (hour < -24)
    {
        hour = -24;
    }
    Hour = hour;
}
void UniversalTime::setMinute(int minute)
{
    if (minute > 60)
    {
        minute = 60;
    }
    else if (minute < -60)
    {
        minute = -60;
    }
    Minute = minute;
}
void UniversalTime::setSecond(int second)
{
    if (second > 60)
    {
        second = 60;
    }
    else if (second < -60)
    {
        second = -60;
    }
    Second = second;
}
void UniversalTime::setMillisecond(int millisecond)
{
    if (millisecond > 1000)
    {
        millisecond = 1000;
    }
    else if (millisecond < -1000)
    {
        millisecond = -1000;
    }
    Millisecond = millisecond;
}
void UniversalTime::setMicosecond(int microsecond)
{
    if (microsecond > 1000)
    {
        microsecond = 1000;
    }
    else if (microsecond < -1000)
    {
        microsecond = -1000;
    }
    Microsecond = microsecond;
}
void UniversalTime::setTime(UniversalTime time)
{
    Year = time.getYear();
    Month = time.getMonth();
    Day = time.getDay();
    Hour = time.getHour();
    Minute = time.getMinute();
    Second = time.getSecond();
    Millisecond = time.getMillisecond();
    Microsecond = time.getMicosecond();
}
#ifdef NOW_ESP32_RTC
void UniversalTime::setTime(struct tm timeinfo)
{
    setYear(timeinfo.tm_year);
    setMonth(timeinfo.tm_mon);
    setDay(timeinfo.tm_mday);
    setHour(timeinfo.tm_hour);
    setMinute(timeinfo.tm_min);
    setSecond(timeinfo.tm_sec);
}
#endif
// Add
void UniversalTime::addYear(int year)
{
    Year += year;
    LeapYear = ((Year % 4 == 0 && Year % 100 != 0) || Year % 400 == 0);
}
void UniversalTime::addMonth(int month)
{
    Month += month;
    int count = floor(double(Month) / 12.0);
    Month -= count * 12.0;
    if (count != 0)
    {
        addYear(count);
    }
}
void UniversalTime::addDay(int day)
{
    Day += day;
    while (1)
    {
        if (Month == 2)
        {
            if (LeapYear)
            {
                if (Day > 29)
                {
                    Day -= 29.0;
                    addMonth(1);
                }
                else
                {
                    break;
                }
            }
            else
            {
                if (Day > 28)
                {
                    Day -= 28.0;
                    addMonth(1);
                }
                else
                {
                    break;
                }
            }
        }
        else if (Month == 4 || Month == 6 || Month == 9 || Month == 11)
        {
            if (Day > 30)
            {
                Day -= 30.0;
                addMonth(1);
            }
            else
            {
                break;
            }
        }
        else
        {
            if (Day > 31)
            {
                Day -= 31.0;
                addMonth(1);
            }
            else
            {
                break;
            }
        }
    }
}
void UniversalTime::addHour(int hour)
{
    Hour += hour;
    int count = floor(double(Hour) / 24.0);
    Hour -= count * 24;
    if (count != 0)
    {
        addDay(count);
    }
}
void UniversalTime::addMinute(int minute)
{
    Minute += minute;
    int count = floor(double(Minute) / 60.0);
    Minute -= count * 60.0;
    if (count != 0)
    {
        addHour(count);
    }
}
void UniversalTime::addSecond(int second)
{
    Second += second;
    int count = floor(double(Second) / 60.0);
    Second -= count * 60.0;
    if (count != 0)
    {
        addMinute(count);
    }
}
void UniversalTime::addMillisecond(int millisecond)
{
    Millisecond += millisecond;
    int count = floor(double(Millisecond) / 1000.0);
    Millisecond -= count * 1000.0;
    if (count != 0)
    {
        addSecond(count);
    }
}
void UniversalTime::addMicosecond(int microsecond)
{
    int count = floor(microsecond / 1000.0);
    microsecond -= count * 1000.0;
    if (count != 0)
    {
        addMillisecond(count);
    }
    Microsecond += microsecond;
}
void UniversalTime::addTime(UniversalTime time)
{
    addYear(time.Year);
    addMonth(time.Month);
    addDay(time.Day);
    addHour(time.Hour);
    addMinute(time.Minute);
    addSecond(time.Second);
    addMillisecond(time.Millisecond);
    addMicosecond(time.Microsecond);
}
//
UniversalTime UniversalTime::add(UniversalTime time)
{
    UniversalTime thisTime = *this;
    thisTime.addYear(time.Year);
    thisTime.addMonth(time.Month);
    thisTime.addDay(time.Day);
    thisTime.addHour(time.Hour);
    thisTime.addMinute(time.Minute);
    thisTime.addSecond(time.Second);
    thisTime.addMillisecond(time.Millisecond);
    thisTime.addMicosecond(time.Microsecond);
    return thisTime;
}
void UniversalTime::subtractTime(UniversalTime time)
{
    addYear(-time.getYear());
    addMonth(-time.getMonth());
    addDay(-time.getDay());
    addHour(-time.getHour());
    addMinute(-time.getMinute());
    addSecond(-time.getSecond());
    addMillisecond(-time.getMillisecond());
    addMicosecond(-time.getMicosecond());
}
UniversalTime UniversalTime::subtract(UniversalTime time)
{
    UniversalTime thisTime = *this;
    thisTime.addYear(-time.Year);
    thisTime.addMonth(-time.Month);
    thisTime.addDay(-time.Day);
    thisTime.addHour(-time.Hour);
    thisTime.addMinute(-time.Minute);
    thisTime.addSecond(-time.Second);
    thisTime.addMillisecond(-time.Millisecond);
    thisTime.addMicosecond(-time.Microsecond);
    return thisTime;
}
double UniversalTime::toUniversalTime()
{
    return Year * pow(10.0, 10.0) +
           Month * pow(10.0, 8.0) +
           Day * pow(10.0, 6.0) +
           Hour * pow(10.0, 4.0) +
           Minute * pow(10.0, 2.0) +
           Second * pow(10.0, 0.0) +
           Millisecond * pow(10.0, -3.0) +
           Microsecond * pow(10.0, -6.0);
}
void UniversalTime::fromUnsiversalTime(double time)
{

    Year = round(time / pow(10.0, 10.0));
    int exp = 8.0;
    int width = 2.0;
    Month = round(time / pow(10.0, exp) - floor(time / pow(10.0, exp + width)) * pow(10.0, width));
    exp = 6.0;
    width = 2.0;
    Day = round(time / pow(10.0, exp) - floor(time / pow(10.0, exp + width)) * pow(10.0, width));
    exp = 4.0;
    width = 2.0;
    Hour = round(time / pow(10.0, exp) - floor(time / pow(10.0, exp + width)) * pow(10.0, width));
    exp = 2.0;
    width = 2.0;
    Minute = round(time / pow(10.0, exp) - floor(time / pow(10.0, exp + width)) * pow(10.0, width));
    exp = 0.0;
    width = 2.0;
    Second = round(time / pow(10.0, exp) - floor(time / pow(10.0, exp + width)) * pow(10.0, width));

    long long floor1 = ((long long)(time)) * pow(10, 3);
    long long timemult = (long long)(time * pow(10, 3));
    Millisecond = (timemult - floor1);

    floor1 = ((long long)(time)) * pow(10, 6);
    timemult = (long long)(time * pow(10, 6));
    Microsecond = (timemult - floor1);
}

void UniversalTime::fromISO8601(String text)
{
    int index = 0;
    int step = 4;
    if (text.length() >= index + step)
    {
        Year = text.substring(index, index + step).toInt();
    }
    index = index + step + 1;
    step = 2;
    if (text.length() >= index + step)
    {
        Month = text.substring(index, index + step).toInt();
    }
    index = index + step + 1;
    step = 2;
    if (text.length() >= index + step)
    {
        Day = text.substring(index, index + step).toInt();
    }
    index = index + step + 1;
    step = 2;
    if (text.length() >= index + step)
    {
        Hour = text.substring(index, index + step).toInt();
    }
    index = index + step + 1;
    step = 2;
    if (text.length() >= index + step)
    {
        Minute = text.substring(index, index + step).toInt();
    }
    index = index + step + 1;
    step = 2;
    if (text.length() >= index + step)
    {
        Second = text.substring(index, index + step).toInt();
    }
    index = index + step + 1;
    step = 3;
    if (text.length() >= index + step)
    {
        Millisecond = text.substring(index, index + step).toInt();
    }
    Microsecond = 0;
    // 2022-03-08T22:36:00.647+0000
    // 0         1         2         3
    // 0123456789012345678901234567890
}

String UniversalTime::toISO8601()
{
    String result = "";
    String number = String(Year);
    while (number.length() < 4)
    {
        number = "0" + number;
    }
    result += number + "-";
    number = String(Month);
    while (number.length() < 2)
    {
        number = "0" + number;
    }
    result += number + "-";
    number = String(Day);
    while (number.length() < 2)
    {
        number = "0" + number;
    }
    result += number + "T";
    number = String(Hour);
    while (number.length() < 2)
    {
        number = "0" + number;
    }
    result += number + ":";
    number = String(Minute);
    while (number.length() < 2)
    {
        number = "0" + number;
    }
    result += number + ":";
    number = String(Second);
    while (number.length() < 2)
    {
        number = "0" + number;
    }

    result += number + ".";
    number = String((int)round(Millisecond + Microsecond / 1000.00));
    while (number.length() < 3)
    {
        number = "0" + number;
    }
    result += number + "+0000";

    return result;
}

String UniversalTime::toString()
{
    return String(Day) + "." +
           String(Month) + "." +
           String(Year) + " " +
           String(Hour) + ":" +
           String(Minute) + ":" +
           String(Second) + "," +
           String(Millisecond) + " " +
           String(Microsecond);
}

/*
 * Compare times
 * @return 0: times are equal, 1: this.time is greater as time, -1: this.time is smaller as time
 */
int UniversalTime::compare(UniversalTime time)
{
    double utime = toUniversalTime();
    utime -= time.toUniversalTime();

    if (utime > 0)
    {
        return -1;
    }
    else if (utime < 0)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

int UniversalTime::compare(
    UniversalTime time,
    double filterYear,
    double filterMonth,
    double filterDay,
    double filterHour,
    double filterMinute,
    double filterSecond,
    double filterMillisecond,
    double filterMicrosecond)
{
    UniversalTime thistime;
    thistime.setYear(filterYear * Year);
    thistime.setMonth(filterMonth * Month);
    thistime.setDay(filterDay * Day);
    thistime.setHour(filterHour * Hour);
    thistime.setMinute(filterMinute * Minute);
    thistime.setSecond(filterSecond * Second);
    thistime.setMillisecond(filterMillisecond * Millisecond);
    thistime.setMicosecond(filterMicrosecond * Microsecond);
    UniversalTime othertime;
    othertime.setYear(filterYear * time.Year);
    othertime.setMonth(filterMonth * time.Month);
    othertime.setDay(filterDay * time.Day);
    othertime.setHour(filterHour * time.Hour);
    othertime.setMinute(filterMinute * time.Minute);
    othertime.setSecond(filterSecond * time.Second);
    othertime.setMillisecond(filterMillisecond * time.Millisecond);
    othertime.setMicosecond(filterMicrosecond * time.Microsecond);

    double utime = thistime.toUniversalTime();
    utime -= othertime.toUniversalTime();

    if (utime > 0)
    {
        return -1;
    }
    else if (utime < 0)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

int UniversalTime::getWeekday()
{
    int d = Day;
    int m = Month;
    int y = Year;
    int weekday = (d += m < 3 ? y-- : y - 2, 23 * m / 9 + d + 4 + y / 4 - y / 100 + y / 400) % 7;
    return weekday;
}

UniversalTime UniversalTime::getTime()
{
    UniversalTime time;
    time.Hour = Hour;
    time.Minute = Minute;
    time.Second = Second;
    time.Microsecond = Microsecond;
    time.Millisecond = Millisecond;
    return time;
}