#include "../acutest/include/acutest.h"

#include "String.h"
#include "Date.h"

void test_string(void)
{
  String s1("test"), copy(s1), empty("");

  TEST_CHECK((s1 + empty) == s1);
  TEST_CHECK((s1 + empty).getLength() == s1.getLength());
  TEST_CHECK((s1 + copy) != s1);
  TEST_CHECK((s1 + copy).getLength() == s1.getLength() + copy.getLength());

  const char *ALPHABET = "abcdefghijklmnopqrstuvwxyz";
  const size_t ALPHABET_LENGTH = strlen(ALPHABET);

  s1 = "";
  s1 += ALPHABET;

  TEST_CHECK(s1 == ALPHABET);
  TEST_CHECK(s1.getLength() == ALPHABET_LENGTH);
  TEST_CHECK(strcmp(s1.getData(), ALPHABET) == 0);
}

void test_date(void)
{
  TEST_CHECK(Date::getDaysInMonth(1, 0) == 31);
  TEST_CHECK(Date::getDaysInMonth(3, 0) == 31);
  TEST_CHECK(Date::getDaysInMonth(4, 0) == 30);
  TEST_CHECK(Date::getDaysInMonth(5, 0) == 31);
  TEST_CHECK(Date::getDaysInMonth(6, 0) == 30);
  TEST_CHECK(Date::getDaysInMonth(7, 0) == 31);
  TEST_CHECK(Date::getDaysInMonth(8, 0) == 31);
  TEST_CHECK(Date::getDaysInMonth(9, 0) == 30);
  TEST_CHECK(Date::getDaysInMonth(10, 0) == 31);
  TEST_CHECK(Date::getDaysInMonth(11, 0) == 30);
  TEST_CHECK(Date::getDaysInMonth(12, 0) == 31);

  TEST_CHECK(Date::getDaysInMonth(2, 4) == 29);
  TEST_CHECK(Date::getDaysInMonth(2, 100) == 28);
  TEST_CHECK(Date::getDaysInMonth(2, 400) == 29);

  for (unsigned i = 1; i < 10000; i += 2)
  {
    TEST_CHECK(Date::getDaysInMonth(2, i) == 28);
  }

  Date d(Date::create("2002-11-16"));
  TEST_CHECK(d.getYear() == 2002 && d.getMonth() == 11 && d.getDay() == 16);
  TEST_CHECK(d.toString() == "2002-11-16");
}

TEST_LIST = {
    {"String", test_string},
    {"Date", test_date},
    {NULL, NULL}};