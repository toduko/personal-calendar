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

Meeting Meeting::create(const String &meeting)
{
  if (!Meeting::isValidMeetingStringFormat(meeting)) // (String, String, Date, Time, Time)
  {
    throw "Invalid meeting string format";
  }

  Vector<String> props(meeting.removeFirst().removeLast().split(','));
  return Meeting::create(props[0], props[1], Date::create(props[2]), Time::create(props[3]), Time::create(props[4]));
}

bool Meeting::isValidMeetingStringFormat(const String &meeting)
{
  return meeting.getLength() >= 34 && meeting[0] == '(' && meeting[meeting.getLength() - 1] == ')' && meeting.count(',') == 4;
}

void Meeting::prettyPrint() const
{
  std::cout << "Name: \"" << this->name << "\"\n";
  std::cout << "Comment: \"" << this->comment << "\"\n";
  std::cout << "Date: " << this->date << "\n";
  std::cout << "Start Time: " << this->start << "\n";
  std::cout << "End Time: " << this->end << "\n";
}

bool Meeting::intersectsWith(const Meeting &other) const
{
  Time maxStart = this->start > other.start ? this->start : other.start;
  Time minEnd = this->end < other.end ? this->end : other.end;

  return this->date == other.date && maxStart < minEnd;
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

bool Meeting::isNull() const
{
  return (this->name.getLength() + this->comment.getLength()) == 0;
}

bool operator<(const Meeting &meeting1, const Meeting &meeting2)
{
  return meeting1.getDate() < meeting2.getDate() ||
         meeting1.getDate() == meeting2.getDate() && meeting1.getStart() < meeting2.getStart();
}

std::ostream &operator<<(std::ostream &os, const Meeting &meeting)
{
  os << '('
     << meeting.getName() << ","
     << meeting.getComment() << ","
     << meeting.getDate() << ","
     << meeting.getStart() << ","
     << meeting.getEnd()
     << ')';

  return os;
}

std::istream &operator>>(std::istream &is, Meeting &meeting)
{
  String input;
  is >> input;

  if (input != String(""))
  {
    meeting = Meeting::create(input);
  }

  return is;
}