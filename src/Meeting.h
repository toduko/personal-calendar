#ifndef MEETING_H_
#define MEETING_H_

#include "String.h"
#include "Date.h"
#include "Time.h"

#include <fstream>

struct MeetingCriteria
{
  bool nameIncludes = false;
  bool commentIncludes = false;
  bool date = false;
  bool start = false;
  bool end = false;
  bool isBetween = false;
};

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

  bool meetsCriteria(const MeetingCriteria &criteria, const Meeting &meeting);

  void writeToFile(std::ofstream &file);
  void readFromFile(std::ifstream &file);

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