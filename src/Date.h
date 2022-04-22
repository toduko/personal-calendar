#ifndef DATE_H_
#define DATE_H_

typedef unsigned char u8;
typedef unsigned short u16;

struct Date
{
  u16 year;
  u8 month;
  u8 day;
};

class DateValidator
{
private:
  DateValidator(){};

public:
  static bool isLeapYear(u16 year);
  static u8 getDaysInMonth(u8 month, u16 year);
  static bool isValidDate(u16 year, u8 month, u8 day);
};

#endif