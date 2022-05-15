#ifndef DATE_H_
#define DATE_H_

#include "String.h"
#include "typedefs.h"

#include <iostream>

class Date
{
private:
  static const u16 MIN_YEAR = 1970;
  static const u16 MAX_YEAR = 2200;
  u16 year;
  u8 month;
  u8 day;
  Date(u16 year, u8 month, u8 day);

public:
  Date();

  u16 getYear() const;
  u8 getMonth() const;
  u8 getDay() const;

  u8 getWeekday() const;

  String toString() const;

  static u8 getWeekday(u16 year, u8 month, u8 day);
  static Date create(u16 year, u8 month, u8 day);
  static Date create(const String &date);
  static bool isLeapYear(u16 year);
  static u8 getDaysInMonth(u8 month, u16 year);
  static bool isValidDate(u16 year, u8 month, u8 day);
  static bool isValidDateStringFormat(const String &date);
};

bool operator==(const Date &date1, const Date &date2);
bool operator!=(const Date &date1, const Date &date2);
bool operator<(const Date &date1, const Date &date2);
bool operator>(const Date &date1, const Date &date2);
bool operator<=(const Date &date1, const Date &date2);
bool operator>=(const Date &date1, const Date &date2);

std::istream &operator>>(std::istream &is, Date &date);
std::ostream &operator<<(std::ostream &os, const Date &date);

#endif