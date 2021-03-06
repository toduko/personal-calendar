#include "MeetingManager.h"

#include <fstream>

const String MeetingManager::FILE_EXTENSION(".db");
const String MeetingManager::DATABASE_NAME("meetings");
const Time MeetingManager::WORKDAY_START(Time::create("08:00:00"));
const Time MeetingManager::WORKDAY_END(Time::create("17:00:00"));

MeetingManager::MeetingManager() 
{
  this->init();
}

void MeetingManager::init()
{
  std::ifstream file(MeetingManager::DATABASE_NAME + MeetingManager::FILE_EXTENSION, std::ios::app | std::ios::binary);

  if (!file.is_open())
  {
    throw "Couldn't open database file";
  }

  file.seekg(0);

  while (!file.eof())
  {
    Meeting meeting;
    file >> meeting;

    if (!meeting.isNull())
    {
      this->meetings.push(meeting);
    }
  }

  file.close();
}

void MeetingManager::save() const
{
  std::ofstream file(MeetingManager::DATABASE_NAME + MeetingManager::FILE_EXTENSION, std::ios::binary | std::ios::trunc);

  if (!file.is_open())
  {
    throw "Couldn't open database file";
  }

  file.seekp(0);

  for (size_t i = 0; i < this->meetings.getSize(); ++i)
  {
    file << this->meetings[i] << '\n';
  }

  file.close();
}

void MeetingManager::addMeeting(const Meeting &meeting)
{
  for (size_t i = 0; i < this->meetings.getSize(); ++i)
  {
    if (this->meetings[i].intersectsWith(meeting))
    {
      throw "Cannot add this meeting since it intersects with another one";
    }
  }
  this->meetings.push(meeting);
}

void MeetingManager::prettyPrint() const
{
  for (size_t i = 0; i < this->meetings.getSize(); ++i)
  {
    this->meetings[i].prettyPrint();
  }
}

void MeetingManager::removeMeeting(const Date &date, const Time &start)
{
  int index = this->findMeeting(date, start);

  if (index == -1)
  {
    throw "No such meeting found";
  }

  this->meetings.remove(index);
}

void MeetingManager::changeMeeting(const Date &date, const Time &start, const Meeting &meeting)
{
  int index = this->findMeeting(date, start);

  if (index == -1)
  {
    throw "No such meeting found";
  }

  for (size_t i = 0; i < this->meetings.getSize(); ++i)
  {
    if (i != index && this->meetings[i].intersectsWith(meeting))
    {
      throw "Cannot add this meeting since it intersects with another one";
    }
  }

  this->meetings[index] = meeting;
}

int MeetingManager::findMeeting(const Date &date, const Time &start) const
{
  for (size_t i = 0; i < this->meetings.getSize(); ++i)
  {
    if (this->meetings[i].getDate() == date && this->meetings[i].getStart() == start)
    {
      return i;
    }
  }

  return -1;
}

Vector<Pair<Date, Pair<Time, Time>>> MeetingManager::getFreeMeetingWindows(const Date &startDate, const Time &duration) const
{
  Vector<Pair<Date, Pair<Time, Time>>> results;
  int i = 0;
  for (Date d = startDate; d < startDate.getNextWeek(); d.passDay())
  {
    Vector<Meeting> meetingsDuringDate = this->getMeetingsByDate(d);
    for (Time t = MeetingManager::WORKDAY_START; t < MeetingManager::WORKDAY_END && (t + duration) < MeetingManager::WORKDAY_END; t.passFifteenMinutes())
    {
      Meeting m;
      m.setStart(t);
      m.setEnd(t + duration);

      if (meetingsDuringDate.getSize() == 0)
      {
        results.push(Pair<Date, Pair<Time, Time>>(d, Pair<Time, Time>(t, t + duration)));
      }
      else
      {
        for (size_t i = 0; i < meetingsDuringDate.getSize(); ++i)
        {
          if (!meetingsDuringDate[i].intersectsWith(m))
          {
            results.push(Pair<Date, Pair<Time, Time>>(d, Pair<Time, Time>(t, t + duration)));
          }
        }
      }
    }
  }

  return results;
}

Vector<Meeting> MeetingManager::getMeetingsByDate(const Date &date) const
{
  Vector<Meeting> results;

  for (size_t i = 0; i < this->meetings.getSize(); ++i)
  {
    if (this->meetings[i].getDate() == date)
    {
      results.push(this->meetings[i]);
    }
  }

  return results;
}

Vector<Meeting> MeetingManager::getMeetingsByNameOrComment(const String &search) const
{
  Vector<Meeting> results;

  for (size_t i = 0; i < this->meetings.getSize(); ++i)
  {
    if (this->meetings[i].getName().includes(search) || this->meetings[i].getComment().includes(search))
    {
      results.push(this->meetings[i]);
    }
  }

  return results;
}

void MeetingManager::writeWeekdayStaticsticsToFile(const Date &start, const Date &end) const
{
  const char *WEEKDAY_STRINGS[] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};
  size_t weekdayStats[7] = {0};

  for (size_t i = 0; i < this->meetings.getSize(); ++i)
  {
    if (this->meetings[i].getDate() >= start && this->meetings[i].getDate() <= end)
    {
      ++weekdayStats[this->meetings[i].getDate().getWeekday()];
    }
  }

  std::ofstream statsFile("stats-" + start.toString() + ".txt");

  if (!statsFile.is_open())
  {
    throw "Couldn't open statistics file";
  }

  for (u8 i = 0; i < 7; ++i)
  {
    statsFile << WEEKDAY_STRINGS[i] << " : " << weekdayStats[i] << '\n';
  }

  statsFile.close();
}