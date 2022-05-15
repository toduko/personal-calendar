#ifndef CLI_H_
#define CLI_H_

#include "MeetingManager.h"
#include "Pair.hpp"
#include "String.h"

class CLI
{
private:
  MeetingManager mm;
  static const Pair<String> COMMANDS[];
  bool stop = false;

public:
  CLI();

  void help() const;

  bool shouldContinue() const;

  void schedule();
  void remove();
  void info();
  void change();
  void find();
  void stats();
  void look();
  void exit();

  void enter();

  Meeting enterMeeting() const;

  void parse(const String &cmd);
};

#endif