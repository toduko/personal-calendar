#ifndef MEETING_MANAGER_H_
#define MEETING_MANAGER_H_

#include "Meeting.h"
#include "String.h"
#include "Vector.hpp"

class MeetingManager
{
private:
  static const String FILE_EXTENSION;
  Vector<Meeting> meetings;
  String databaseName;

  void init();

public:
  MeetingManager(const String &databaseName);

  void save() const;

  void prettyPrint() const;

  void removeMeeting(const Date &date, const Time &start);

  Vector<Meeting> getMeetingsByDate(const Date &date) const;
  Vector<Meeting> getMeetingsByNameOrComment(const String &name, const String &comment) const;

  void writeWeekdayStaticsticsToFile(const Date &start, const Date &end) const;

  void addMeeting(const Meeting &meeting);
};

#endif