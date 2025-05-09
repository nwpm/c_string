#include "../include/c_string.h"
#include "../tests/libs/unity/src/unity.h"
#include <assert.h>

void setUp(void) {}

void tearDown(void) {}

// c_strlen tests
void test_c_strlen_empty_string(void) {
  TEST_ASSERT_EQUAL_INT(0, c_strlen(""));
}

void test_c_strlen_short_string(void) {
  TEST_ASSERT_EQUAL_INT(5, c_strlen("hello"));
}

void test_c_strlen_string_with_spaces(void) {
  TEST_ASSERT_EQUAL_INT(11, c_strlen("hello world"));
}

void test_c_strlen_string_with_tabs(void) {
  TEST_ASSERT_EQUAL_INT(8, c_strlen("\t\t\thello"));
}

void test_c_strlen_string_with_end_symbol(void) {
  TEST_ASSERT_EQUAL_INT(3, c_strlen("hel\0lo"));
}

//

void test_string_equality(void) { TEST_ASSERT_EQUAL_STRING("hello", "hello"); }

int main(void) {

  UNITY_BEGIN();
  RUN_TEST(test_c_strlen_empty_string);
  RUN_TEST(test_c_strlen_short_string);
  RUN_TEST(test_c_strlen_string_with_spaces);
  RUN_TEST(test_c_strlen_string_with_tabs);
  RUN_TEST(test_c_strlen_string_with_end_symbol);
  return UNITY_END();
}
