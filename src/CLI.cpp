#include "CLI.h"

#include <iostream>

const Pair<String> CLI::COMMANDS[10]{
    Pair<String>("help", "prints this menu"),
    Pair<String>("schedule", "schedules a meeting"),
    Pair<String>("remove", "removes a meeting which has a specific date and start time"),
    Pair<String>("info", "prints info about specific date"),
    Pair<String>("change", "changes a meeting which has a specific date and start time"),
    Pair<String>("find", "finds a meeting which includes a specific name or comment"),
    Pair<String>("stats", "writes weekday busyness for a specific period to a file"),
    Pair<String>("look", "looks for a meeting window from a starting date to one week after that in 15 minute intervals"),
    Pair<String>("save", "saves the data"),
    Pair<String>("exit", "saves the data end exits"),
};

CLI::CLI()
{
  std::cout << "Welcome to Personal Calendar!\n";
  std::cout << "Type help to see the available commands.\n";
}

void CLI::help() const
{
  std::cout << "Here are the available commands:\n";
  for (size_t i = 0; i < 10; ++i)
  {
    std::cout << CLI::COMMANDS[i].first << " - " << CLI::COMMANDS[i].second << std::endl;
  }
}

bool CLI::shouldContinue() const
{
  return !this->stop;
}

void CLI::schedule()
{
  this->mm.addMeeting(this->enterMeeting());
}

void CLI::remove()
{
  Date date;
  std::cout << "Enter meeting date (format must be YYYY-MM-DD): ";
  std::cin >> date;
  Time start;
  std::cout << "Enter meeting start time (format must be HH:MM:SS): ";
  std::cin >> start;
  this->mm.removeMeeting(date, start);
}

void CLI::info()
{
  Date date;
  std::cout << "Enter date (format must be YYYY-MM-DD): ";
  std::cin >> date;

  Vector<Meeting> meetings = this->mm.getMeetingsByDate(date);

  for (size_t i = 0; i < meetings.getSize(); ++i)
  {
    std::cout << "Meeting " << i + 1 << ":\n";
    meetings[i].prettyPrint();
  }

  if (meetings.getSize() == 0)
  {
    throw "No meetings found for this date";
  }
}

Meeting CLI::enterMeeting() const
{
  String name, comment;
  std::cout << "Enter meeting name (must be non-empty): ";
  std::cin >> name;
  std::cout << "Enter meeting comment (must be non-empty): ";
  std::cin >> comment;

  Date date;
  std::cout << "Enter meeting date (format must be YYYY-MM-DD): ";
  std::cin >> date;

  Time start, end;
  std::cout << "Enter meeting start time (format must be HH:MM:SS): ";
  std::cin >> start;
  std::cout << "Enter meeting end time (format must be HH:MM:SS): ";
  std::cin >> end;

  return Meeting::create(name, comment, date, start, end);
}

void CLI::change()
{
  Date oldDate;
  std::cout << "Enter current meeting date (format must be YYYY-MM-DD): ";
  std::cin >> oldDate;
  Time oldStart;
  std::cout << "Enter current meeting start time (format must be HH:MM:SS): ";
  std::cin >> oldStart;

  std::cout << "New meeting data:\n";
  this->mm.changeMeeting(oldDate, oldStart, this->enterMeeting());
}

void CLI::find()
{
  String search;
  std::cout << "Enter search string: ";
  std::cin >> search;

  Vector<Meeting> meetings = this->mm.getMeetingsByNameOrComment(search);

  for (size_t i = 0; i < meetings.getSize(); ++i)
  {
    std::cout << "Meeting " << i + 1 << ":\n";
    meetings[i].prettyPrint();
  }

  if (meetings.getSize() == 0)
  {
    throw "No meetings found";
  }
}

void CLI::stats()
{
  Date start, end;
  std::cout << "Enter period start (format must be YYYY-MM-DD): ";
  std::cin >> start;
  std::cout << "Enter period end (format must be YYYY-MM-DD): ";
  std::cin >> end;

  this->mm.writeWeekdayStaticsticsToFile(start, end);
}

void CLI::look()
{
  Date start;
  std::cout << "Enter start date (format must be YYYY-MM-DD): ";
  std::cin >> start;

  Time duration;
  std::cout << "Enter current meeting duration (format must be HH:MM:SS): ";
  std::cin >> duration;

  Vector<Pair<Date, Pair<Time, Time>>> meetingWindows = this->mm.getFreeMeetingWindows(start, duration);

  for (size_t i = 0; i < meetingWindows.getSize(); ++i)
  {
    std::cout << "Meeting window on " << meetingWindows[i].first << " from " << meetingWindows[i].second.first << " to " << meetingWindows[i].second.second << "\n";
  }

  if (meetingWindows.getSize() == 0)
  {
    throw "No meeting windows found";
  }
}

void CLI::enter()
{
  String cmd;
  std::cout << "personal-calendar> ";
  std::cin >> cmd;

  this->parse(cmd.toLowercase());
}

void CLI::parse(const String &cmd)
{
  if (cmd == String("help"))
  {
    this->help();
  }
  else if (cmd == String("schedule"))
  {
    this->schedule();
  }
  else if (cmd == String("remove"))
  {
    this->remove();
  }
  else if (cmd == String("info"))
  {
    this->info();
  }
  else if (cmd == String("change"))
  {
    this->change();
  }
  else if (cmd == String("find"))
  {
    this->find();
  }
  else if (cmd == String("stats"))
  {
    this->stats();
  }
  else if (cmd == String("look"))
  {
    this->look();
  }
  else if (cmd == String("save"))
  {
    this->mm.save();
  }
  else if (cmd == String("exit"))
  {
    this->mm.save();
    this->stop = true;
  }
  else
  {
    throw "Uknown command. Type help to see the available commands";
  }
}