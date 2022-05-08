#include <iostream>
#include "String.h"
#include "Date.h"

int main()
{
  try
  {
    std::cout << "Personal calendar\n";
    std::cout << Date::isValidDate(Date::fromString("2002-16-11"));
  }
  catch (const char *msg)
  {
    std::cout << msg << std::endl;
  }

  return 0;
}