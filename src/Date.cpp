#include "Date.h"

const long long int DAYS_IN_MONTHS = 1151794505154789279;

bool DateValidator::isLeapYear(u16 year)
{
  return ((year % 4 == 0) ? ((year % 100 == 0) ? ((year % 400 == 0) ? true : false) : true) : false);
}

u8 DateValidator::getDaysInMonth(u8 month, u16 year)
{
  return ((DAYS_IN_MONTHS >> (5 * (month - 1)) & 31) + (month == 2 && isLeapYear(year)));
}

bool DateValidator::isValidDate(u16 year, u8 month, u8 day)
{
  if (month < 1 || month > 12)
  {
    return false;
  }
  return day <= getDaysInMonth(month, year);
}