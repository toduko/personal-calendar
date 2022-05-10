#include "Time.h"

Time Time::create(u8 hours, u8 minutes, u8 seconds)
{
  if (!Time::isValidTime(hours, minutes, seconds))
  {
    throw "Invalid time";
  }

  return Time(hours, minutes, seconds);
}

Time Time::create(const String &time)
{
  if (!Time::isValidTimeStringFormat(time))
  {
    throw "Invalid time string format";
  }

  u8 hours = 0, minutes = 0, seconds = 0;

  for (size_t i = 0; i <= 1; ++i)
  {
    (hours *= 10) += String::toDigit(time[i]);
  }

  for (size_t i = 3; i <= 4; ++i)
  {
    (minutes *= 10) += String::toDigit(time[i]);
  }

  for (size_t i = 6; i <= 7; ++i)
  {
    (seconds *= 10) += String::toDigit(time[i]);
  }

  return Time::create(hours, minutes, seconds);
}

String Time::toString() const
{
  String result("HH:MM:SS");

  result[0] = String::toChar(this->hours / 10);
  result[1] = String::toChar(this->hours % 10);

  result[3] = String::toChar(this->minutes / 10);
  result[4] = String::toChar(this->minutes % 10);

  result[6] = String::toChar(this->seconds / 10);
  result[7] = String::toChar(this->seconds % 10);

  return result;
}

Time::Time(u8 hours, u8 minutes, u8 seconds) : hours(hours), minutes(minutes), seconds(seconds) {}

bool Time::isValidTime(u8 hours, u8 minutes, u8 seconds)
{
  return hours < 24 && minutes < 60 && seconds < 60;
}

bool Time::isValidTimeStringFormat(const String &time) // HH:MM:SS
{
  if (time.getLength() != 8)
  {
    return false;
  }

  for (size_t i = 0; i < time.getLength(); ++i)
  {
    if (((i == 2 || i == 5) && time[i] != ':') || ((i != 2 && i != 5) && !String::isDigit(time[i])))
    {
      return false;
    }
  }

  return true;
}

u8 Time::getHours() const
{
  return this->hours;
}
u8 Time::getMinutes() const
{
  return this->minutes;
}
u8 Time::getSeconds() const
{
  return this->seconds;
}

bool operator==(const Time &time1, const Time &time2)
{
  return time1.getHours() == time2.getHours() &&
         time1.getMinutes() == time2.getMinutes() &&
         time1.getSeconds() == time2.getSeconds();
}

bool operator!=(const Time &time1, const Time &time2)
{
  return !(time1 == time2);
}

bool operator<(const Time &time1, const Time &time2)
{
  return time1.getHours() < time2.getHours() ||
         time1.getHours() == time2.getHours() && time1.getMinutes() < time2.getMinutes() ||
         time1.getHours() == time2.getHours() && time1.getMinutes() == time2.getMinutes() && time1.getSeconds() < time2.getSeconds();
}

bool operator>=(const Time &time1, const Time &time2)
{
  return !(time1 < time2);
}

bool operator>(const Time &time1, const Time &time2)
{
  return time1 >= time2 && time1 != time2;
}

bool operator<=(const Time &time1, const Time &time2)
{
  return !(time1 > time2);
}
