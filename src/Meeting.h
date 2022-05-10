#ifndef MEETING_H_
#define MEETING_H_

#include "String.h"
#include "Date.h"
#include "Time.h"

class Meeting
{
private:
  String name;
  String comment;
  Date date;
  Time start;
  Time end;
  Meeting(const String &name, const String &comment, const Date &date, const Time &start, const Time &end);

public:
  const String &getName() const;
  const String &getComment() const;
  const Date &getDate() const;
  const Time &getStart() const;
  const Time &getEnd() const;

  static Meeting create(const String &name, const String &comment, const Date &date, const Time &start, const Time &end);
  static bool isValidMeeting(const String &name, const String &comment, const Date &date, const Time &start, const Time &end);
};

bool operator<(const Meeting &meeting1, const Meeting &meeting2);

#endif