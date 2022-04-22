#include "../acutest/include/acutest.h"

void test_example(void)
{
  TEST_CHECK(2 + 2 == 4);
}

TEST_LIST = {
    {"example", test_example},
    {NULL, NULL}};