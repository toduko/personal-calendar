#include "Meeting.h"

Meeting::Meeting() {}

Meeting::Meeting(const String &name, const String &comment, const Date &date, const Time &start, const Time &end)
    : name(name), comment(comment), date(date), start(start), end(end) {}

Meeting Meeting::create(const String &name, const String &comment, const Date &date, const Time &start, const Time &end)
{
  if (!Meeting::isValidMeeting(name, comment, date, start, end))
  {
    throw "Invalid meeting";
  }

  return Meeting(name, comment, date, start, end);
}

bool Meeting::isValidMeeting(const String &name, const String &comment, const Date &date, const Time &start, const Time &end)
{
  return !name.isEmpty() && !comment.isEmpty() && start < end;
}

void Meeting::setName(const String &name)
{
  this->name = name;
}

void Meeting::setComment(const String &comment)
{
  this->comment = comment;
}

void Meeting::setDate(const Date &date)
{
  this->date = date;
}

void Meeting::setStart(const Time &start)
{
  this->start = start;
}

void Meeting::setEnd(const Time &end)
{
  this->end = end;
}

const String &Meeting::getName() const
{
  return this->name;
}

const String &Meeting::getComment() const
{
  return this->comment;
}

const Date &Meeting::getDate() const
{
  return this->date;
}

const Time &Meeting::getStart() const
{
  return this->start;
}

const Time &Meeting::getEnd() const
{
  return this->end;
}

bool Meeting::meetsCriteria(const MeetingCriteria &criteria, const Meeting &meeting)
{
  if (criteria.nameIncludes && !this->name.includes(meeting.name) ||
      criteria.commentIncludes && !this->comment.includes(meeting.comment) ||
      criteria.date && this->date != meeting.date ||
      criteria.start && this->start != meeting.start ||
      criteria.end && this->end != meeting.end ||
      criteria.isBetween && !(this->start >= meeting.start && this->end <= meeting.end))
  {
    return false;
  }

  return true;
}

void Meeting::writeToFile(std::ofstream &file)
{
  this->name.writeToFile(file);
  this->comment.writeToFile(file);
  this->date.writeToFile(file);
  this->start.writeToFile(file);
  this->end.writeToFile(file);
}

void Meeting::readFromFile(std::ifstream &file)
{
  this->name.readFromFile(file);
  this->comment.readFromFile(file);
  this->date.readFromFile(file);
  this->start.readFromFile(file);
  this->end.readFromFile(file);
}

bool operator<(const Meeting &meeting1, const Meeting &meeting2)
{
  return meeting1.getDate() < meeting2.getDate() ||
         meeting1.getDate() == meeting2.getDate() && meeting1.getStart() < meeting2.getStart();
}