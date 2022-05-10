#ifndef TIME_H_
#define TIME_H_

#include "String.h"
#include "typedefs.h"

class Time
{
private:
    u8 hours;
    u8 minutes;
    u8 seconds;
    Time(u8 hours, u8 minutes, u8 seconds);

public:
    u8 getHours() const;
    u8 getMinutes() const;
    u8 getSeconds() const;

    String toString() const;

    static Time create(u8 hours, u8 minutes, u8 seconds);
    static Time create(const String &time);
    static bool isValidTime(u8 hours, u8 minutes, u8 seconds);
    static bool isValidTimeStringFormat(const String &time);
};

bool operator==(const Time &time1, const Time &time2);
bool operator!=(const Time &time1, const Time &time2);
bool operator<(const Time &time1, const Time &time2);
bool operator>(const Time &time1, const Time &time2);
bool operator<=(const Time &time1, const Time &time2);
bool operator>=(const Time &time1, const Time &time2);

#endif