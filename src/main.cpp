#include <iostream>

#include "String.h"
#include "Date.h"
#include "Time.h"

int main()
{
  try
  {
    std::cout << "Personal calendar\n";
  }
  catch (const char *msg)
  {
    std::cout << msg << std::endl;
  }

  return 0;
}