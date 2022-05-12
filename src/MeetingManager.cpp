#include "MeetingManager.h"

#include <fstream>

MeetingManager::MeetingManager(const String &databaseName) : databaseName(databaseName)
{
  this->init();
}

void MeetingManager::init()
{
  std::ifstream file(this->databaseName, std::ios::app | std::ios::binary);

  if (!file.is_open())
  {
    throw "Couldn't open database file";
  }

  file.seekg(0);

  while (!file.eof())
  {

    Meeting meeting;
    meeting.readFromFile(file);

    this->meetings.push(meeting);
  }

  file.close();
}

void MeetingManager::save() const
{
  std::ofstream file(this->databaseName, std::ios::binary);

  if (!file.is_open())
  {
    throw "Couldn't open database file";
  }

  file.seekp(0);

  for (size_t i = 0; i < this->meetings.getSize(); ++i)
  {
    this->meetings[i].writeToFile(file);
  }

  file.close();
}

void MeetingManager::addMeeting(const Meeting &meeting)
{
  this->meetings.push(meeting);
}

int MeetingManager::findMeetingBy(const MeetingCriteria &criteria, const Meeting &meeting) const
{
  for (size_t i = 0; i < this->meetings.getSize(); ++i)
  {
    if (this->meetings[i].meetsCriteria(criteria, meeting))
    {
      return i;
    }
  }

  return -1;
}

void MeetingManager::changeMeeting(const MeetingCriteria &criteria, const Meeting &meeting)
{
  int index = this->findMeetingBy(criteria, meeting);

  if (index == -1)
  {
    throw "No such meeting found";
  }

  if (criteria.name)
  {
    this->meetings[index].setName(meeting.getName());
  }

  if (criteria.comment)
  {
    this->meetings[index].setComment(meeting.getComment());
  }

  if (criteria.date)
  {
    this->meetings[index].setDate(meeting.getDate());
  }

  if (criteria.start)
  {
    this->meetings[index].setStart(meeting.getStart());
  }

  if (criteria.end)
  {
    this->meetings[index].setEnd(meeting.getEnd());
  }
}