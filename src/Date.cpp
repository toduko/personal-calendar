#include "Date.h"

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

bool Date::isValidDate(u16 year, u8 month, u8 day)
{
  if (month < 1 || month > 12)
  {
    return false;
  }
  return day <= Date::getDaysInMonth(month, year);
}