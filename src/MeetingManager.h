#ifndef MEETING_MANAGER_H_
#define MEETING_MANAGER_H_

#include "Meeting.h"
#include "String.h"
#include "Pair.hpp"
#include "Vector.hpp"

class MeetingManager
{
private:
  static const String DATABASE_NAME;
  static const String FILE_EXTENSION;
  static const Time WORKDAY_START;
  static const Time WORKDAY_END;
  Vector<Meeting> meetings;

  void init();

public:
  MeetingManager();

  void save() const;

  void prettyPrint() const;

  void removeMeeting(const Date &date, const Time &start);
  void changeMeeting(const Date &date, const Time &start, const Meeting &meeting);
  int findMeeting(const Date &date, const Time &start) const;

  Vector<Pair<Date, Pair<Time, Time>>> getFreeMeetingWindows(const Date &startDate, const Time &duration) const;

  Vector<Meeting> getMeetingsByDate(const Date &date) const;
  Vector<Meeting> getMeetingsByNameOrComment(const String &search) const;

  void writeWeekdayStaticsticsToFile(const Date &start, const Date &end) const;

  void addMeeting(const Meeting &meeting);
};

#endif