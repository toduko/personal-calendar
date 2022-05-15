#include "../acutest/include/acutest.h"

#include "String.h"
#include "Date.h"
#include "Time.h"
#include "Vector.hpp"

void test_string(void)
{
  String s1("test"), copy(s1), empty("");

  TEST_CHECK((s1 + empty) == s1);
  TEST_CHECK((s1 + empty).getLength() == s1.getLength());
  TEST_CHECK((s1 + copy) != s1);
  TEST_CHECK((s1 + copy).getLength() == s1.getLength() + copy.getLength());

  String ALPHABET("abcdefghijklmnopqrstuvwxyz");
  const size_t ALPHABET_LENGTH = ALPHABET.getLength();

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
  TEST_CHECK(d.toString() == String("2002-11-16"));
}

void test_time(void)
{
  TEST_CHECK(Time::isValidTime(23, 59, 59));
  TEST_CHECK(!Time::isValidTime(24, 0, 0));
  TEST_CHECK(!Time::isValidTime(0, 60, 0));
  TEST_CHECK(!Time::isValidTime(0, 0, 60));

  for (u8 i = 1; i < 23; ++i)
  {
    for (u8 j = 1; j < 59; ++j)
    {
      for (u8 k = 1; k < 59; ++k)
      {
        TEST_CHECK(Time::create(i, j, k) < Time::create(i + 1, j, k));
        TEST_CHECK(Time::create(i, j, k) < Time::create(i, j + 1, k));
        TEST_CHECK(Time::create(i, j, k) < Time::create(i, j, k + 1));

        TEST_CHECK(Time::create(i - 1, j, k) < Time::create(i, j, k));
        TEST_CHECK(Time::create(i, j - 1, k) < Time::create(i, j, k));
        TEST_CHECK(Time::create(i, j, k - 1) < Time::create(i, j, k));

        TEST_CHECK(Time::create(i, j, k) == Time::create(i, j, k));
      }
    }
  }

  Time t(Time::create("01:02:03"));
  TEST_CHECK(t.getHours() == 1 && t.getMinutes() == 2 && t.getSeconds() == 3);
  TEST_CHECK(t.toString() == String("01:02:03"));
}

void test_vector(void)
{
  Vector<int> vec;

  for (int i = 1000; i > 0; --i)
  {
    vec.push(i);
  }

  for (int i = 0; i < vec.getSize() - 1; --i)
  {
    TEST_CHECK(vec[i] == vec[i + 1] + 1);
    TEST_CHECK(vec.has(i + 1));
    TEST_CHECK(vec.find(i + 1) == vec.getSize() - i - 1);
  }

  vec.sort();

  for (int i = 0; i < vec.getSize() - 1; --i)
  {
    TEST_CHECK(vec[i] + 1 == vec[i + 1]);
    TEST_CHECK(vec.has(i + 1));
    TEST_CHECK(vec.find(i + 1) == i);
  }
}

TEST_LIST = {
    {"String", test_string},
    {"Date", test_date},
    {"Time", test_time},
    {"Vector", test_vector},
    {NULL, NULL}};