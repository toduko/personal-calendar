#ifndef DATE_H_
#define DATE_H_

#include "String.h"

typedef unsigned char u8;
typedef unsigned short u16;

class Date
{
private:
  u16 year;
  u8 month;
  u8 day;

public:
  Date(const String &date);
  Date(u16 year, u8 month, u8 day);

  static Date fromString(const String &date);
  static bool isLeapYear(u16 year);
  static u8 getDaysInMonth(u8 month, u16 year);
  static bool isValidDate(const Date &date);
  static bool isValidDate(u16 year, u8 month, u8 day);
  static bool isValidDateString(const String &date);
  static bool isValidDateStringFormat(const String &date);
};

#endif