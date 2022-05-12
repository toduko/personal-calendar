#ifndef MEETING_MANAGER_H_
#define MEETING_MANAGER_H_

#include "Meeting.h"
#include "String.h"
#include "Vector.hpp"

class MeetingManager
{
private:
  Vector<Meeting> meetings;
  String databaseName;

  void init();

public:
  MeetingManager(const String &databaseName);

  void save() const;

  int findMeetingBy(const MeetingCriteria &criteria, const Meeting &meeting) const;

  void changeMeeting(const MeetingCriteria &criteria, const Meeting &meeting);

  void addMeeting(const Meeting &meeting);
};

#endif