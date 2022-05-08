#include "Date.h"

Date::Date(const String &date)
{
  *this = Date::fromString(date);
}

bool Date::isValidDateStringFormat(const String &date) // YYYY-MM-DD expected
{
  if (date.getLength() != 10)
  {
    return false;
  }

  for (size_t i = 0; i < date.getLength(); ++i)
  {
    if (((i == 4 || i == 7) && date[i] != '-') || ((i != 4 && i != 7) && !String::isDigit(date[i])))
    {
      return false;
    }
  }

  return true;
}

Date Date::fromString(const String &date)
{
  if (!Date::isValidDateStringFormat(date))
  {
    throw "Invalid date string format";
  }

  u16 year = 0;
  u8 month = 0, day = 0;

  for (size_t i = 0; i <= 3; ++i)
  {
    (year *= 10) += String::toDigit(date[i]);
  }

  for (size_t i = 5; i <= 6; ++i)
  {
    (month *= 10) += String::toDigit(date[i]);
  }

  for (size_t i = 8; i <= 9; ++i)
  {
    (day *= 10) += String::toDigit(date[i]);
  }

  return Date(year, month, day);
}

bool Date::isValidDateString(const String &date)
{
  try
  {
    return Date::isValidDate(Date::fromString(date));
  }
  catch (const char *errorMessage)
  {
    return false;
  }
}

Date::Date(u16 year, u8 month, u8 day) : year(year), month(month), day(day) {}

bool Date::isLeapYear(u16 year)
{
  return ((year % 4 == 0) ? ((year % 100 == 0) ? ((year % 400 == 0) ? true : false) : true) : false);
}

u8 Date::getDaysInMonth(u8 month, u16 year)
{
  const long long int DAYS_IN_MONTHS = 1151794505154789279;
  return ((DAYS_IN_MONTHS >> (5 * (month - 1)) & 31) + (month == 2 && Date::isLeapYear(year)));
}

bool Date::isValidDate(const Date &date)
{
  return Date::isValidDate(date.year, date.month, date.day);
}

bool Date::isValidDate(u16 year, u8 month, u8 day)
{
  if (month < 1 || month > 12 || year < 1970 || year > 2200)
  {
    return false;
  }
  return day <= Date::getDaysInMonth(month, year);
}

String Date::toString() const
{
  if (!Date::isValidDate(*this))
  {
    throw "Cannot convert invalid date to string";
  }

  String result("YYYY-MM-DD");

  result[0] = String::toChar(this->year / 1000);
  result[1] = String::toChar((this->year / 100) % 10);
  result[2] = String::toChar((this->year / 10) % 10);
  result[3] = String::toChar(this->year % 10);

  result[5] = String::toChar(this->month / 10);
  result[6] = String::toChar(this->month % 10);

  result[8] = String::toChar(this->day / 10);
  result[9] = String::toChar(this->day % 10);

  return result;
}