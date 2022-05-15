#include <iostream>

#include "String.h"
#include "Date.h"
#include "Time.h"
#include "Meeting.h"
#include "CLI.h"

int main()
{
  CLI cli;
  while (cli.shouldContinue())
  {
    try
    {
      cli.enter();
    }
    catch (const char *msg)
    {
      std::cout << msg << std::endl;
    }
  }

  return 0;
}