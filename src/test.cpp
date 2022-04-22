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

void test_date_validation(void)
{
  TEST_CHECK(DateValidator::getDaysInMonth(1, 0) == 31);
  TEST_CHECK(DateValidator::getDaysInMonth(3, 0) == 31);
  TEST_CHECK(DateValidator::getDaysInMonth(4, 0) == 30);
  TEST_CHECK(DateValidator::getDaysInMonth(5, 0) == 31);
  TEST_CHECK(DateValidator::getDaysInMonth(6, 0) == 30);
  TEST_CHECK(DateValidator::getDaysInMonth(7, 0) == 31);
  TEST_CHECK(DateValidator::getDaysInMonth(8, 0) == 31);
  TEST_CHECK(DateValidator::getDaysInMonth(9, 0) == 30);
  TEST_CHECK(DateValidator::getDaysInMonth(10, 0) == 31);
  TEST_CHECK(DateValidator::getDaysInMonth(11, 0) == 30);
  TEST_CHECK(DateValidator::getDaysInMonth(12, 0) == 31);

  TEST_CHECK(DateValidator::getDaysInMonth(2, 4) == 29);
  TEST_CHECK(DateValidator::getDaysInMonth(2, 100) == 28);
  TEST_CHECK(DateValidator::getDaysInMonth(2, 400) == 29);

  for (unsigned i = 1; i < 10000; i += 2)
  {
    TEST_CHECK(DateValidator::getDaysInMonth(2, i) == 28);
  }
}

TEST_LIST = {
    {"String", test_string},
    {"DateValidator", test_date_validation},
    {NULL, NULL}};