#include "Meeting.h"

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

bool operator<(const Meeting &meeting1, const Meeting &meeting2)
{
  return meeting1.getDate() < meeting2.getDate() ||
         meeting1.getDate() == meeting2.getDate() && meeting1.getStart() < meeting2.getStart();
}