#include "../acutest/include/acutest.h"

#include "String.h"

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

TEST_LIST = {
    {"String", test_string},
    {NULL, NULL}};