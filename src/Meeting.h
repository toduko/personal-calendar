#ifndef MEETING_H_
#define MEETING_H_

#include "String.h"
#include "Date.h"
#include "Time.h"

#include <iostream>
#include <fstream>

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
  Meeting();

  void setName(const String &name);
  void setComment(const String &comment);
  void setDate(const Date &date);
  void setStart(const Time &start);
  void setEnd(const Time &end);

  bool intersectsWith(const Meeting &other) const;

  void prettyPrint() const;

  const String &getName() const;
  const String &getComment() const;
  const Date &getDate() const;
  const Time &getStart() const;
  const Time &getEnd() const;

  bool isNull() const;

  static Meeting create(const String &meeting);
  static Meeting create(const String &name, const String &comment, const Date &date, const Time &start, const Time &end);
  static bool isValidMeeting(const String &name, const String &comment, const Date &date, const Time &start, const Time &end);
  static bool isValidMeetingStringFormat(const String &meeting);
};

bool operator<(const Meeting &meeting1, const Meeting &meeting2);

std::istream &operator>>(std::istream &is, Meeting &meeting);
std::ostream &operator<<(std::ostream &os, const Meeting &meeting);

#endif