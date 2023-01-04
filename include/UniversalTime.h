

#ifndef UniversalTime_h
#define UniversalTime_h
#include "Arduino.h"

#ifndef unsignedLongOverflow
#define unsignedLongOverflow 2147483648.0
#endif


#if !defined(NOW_MILLIS) && !defined(NOW_ESP32_RTC)
#define NOW_MILLIS 1
// #define NOW_ESP32_RTC
#endif

#ifdef NOW_ESP32_RTC
#include <time.h>
#endif

class UniversalTime
{

public:
    static UniversalTime UniversalTimeNow;
    static UniversalTime Now()
    {
#ifdef NOW_MILLIS
        static unsigned long UniversalTimeMillisTimestemp;
        static unsigned long UniversalTimeMillisOffsetTimestemp;

        if (UniversalTimeMillisTimestemp == UniversalTimeMillisOffsetTimestemp)
        {
            UniversalTimeMillisOffsetTimestemp = unsignedLongOverflow;
        }
        unsigned long mill = millis();
        unsigned long offest = mill + unsignedLongOverflow;
        int diff1 = mill - UniversalTimeMillisTimestemp;
        int diff2 = offest - UniversalTimeMillisOffsetTimestemp;
        UniversalTimeMillisTimestemp = mill;
        UniversalTimeMillisOffsetTimestemp = offest;
        UniversalTimeNow.addMillisecond(max(diff1, diff2));
#endif

#ifdef NOW_ESP32_RTC
        time_t now;
        struct tm timeinfo;
        time(&now);
        localtime_r(&now, &timeinfo);
        UniversalTimeNow.setTime(timeinfo);
#endif

        return UniversalTimeNow;
    }
    static void setNow(UniversalTime time)
    {
        UniversalTime::UniversalTimeNow = time;
    }
    // Get
    int getYear();
    int getMonth();
    int getDay();
    int getHour();
    int getMinute();
    int getSecond();
    int getMillisecond();
    int getMicosecond();
    // Set
    void setYear(int year);
    void setMonth(int month);
    void setDay(int day);
    void setHour(int hour);
    void setMinute(int minute);
    void setSecond(int second);
    void setMillisecond(int millisecond);
    void setMicosecond(int microsecond);
    void setTime(UniversalTime time);
#ifdef NOW_ESP32_RTC
    void setTime(struct tm timeinfo);
#endif
    // Add
    void addYear(int year);
    void addMonth(int month);
    void addDay(int day);
    void addHour(int hour);
    void addMinute(int minute);
    void addSecond(int second);
    void addMillisecond(int millisecond);
    void addMicosecond(int microsecond);

    void addTime(UniversalTime time);
    UniversalTime add(UniversalTime time);
    void subtractTime(UniversalTime time);
    UniversalTime subtract(UniversalTime time);

    double toUniversalTime();
    void fromUnsiversalTime(double time);
    /*
     * Compare times
     * @return 0: times are equal, 1: this.time is greater as time, -1: this.time is smaller as time
     */
    int compare(UniversalTime time);
    /*
     * Compare times
     * @return 0: times are equal, 1: this.time is greater as time, -1: this.time is smaller as time
     */
    int compare(
        UniversalTime time,
        double filterYear,
        double filterMonth,
        double filterDay,
        double filterHour,
        double filterMinute,
        double filterSecond,
        double filterMilisecond,
        double filterMicrosecond);
    void fromISO8601(String text);
    String toISO8601();
    String toString();

    int getWeekday();

    UniversalTime getTime();

    UniversalTime();

private:
    int Year;
    int8_t Month;
    int8_t Day;
    int8_t Hour;
    int8_t Minute;
    int8_t Second;
    int Millisecond;
    int Microsecond;
    bool LeapYear;
};
#ifndef UniversalTimeNow_val
UniversalTime UniversalTime::UniversalTimeNow;
#define UniversalTimeNow_val
#endif
#endif
