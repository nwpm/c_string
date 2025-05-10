#include "../include/c_string.h"
#include "../tests/libs/unity/src/unity.h"
#include "libs/unity/src/unity_internals.h"
#include <assert.h>
#include <limits.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define KB(x) ((x) * 1024)
#define MB(x) ((x) * 1024 * 1024)

#define TEST_VALID_INPUT_DATA                                                  \
  printf("\n++++++++++TESTS VALID INPUT DATA++++++++++\n")
#define TEST_EDGE_CASES printf("\n++++++++++TESTS EDGE CASES++++++++++\n")
#define NEGATIVE_TESTS printf("\n++++++++++NEGATIVE TESTS++++++++++\n")
#define STRESS_TESTS printf("\n++++++++++STRESS TESTS++++++++++\n")

void setUp(void) {}

void tearDown(void) {}

// ----------c_strlen tests----------

// c_strlen valid input data
void test_c_strlen_empty_string(void) {
  TEST_ASSERT_EQUAL_INT(0, c_strlen(""));
}

void test_c_strlen_short_string(void) {
  TEST_ASSERT_EQUAL_INT(5, c_strlen("hello"));
}

void test_c_strlen_string_with_spaces(void) {
  TEST_ASSERT_EQUAL_INT(11, c_strlen("hello world"));
}

// c_strlen negative tests
void test_c_strlen_null(void) { TEST_ASSERT_EQUAL_INT(-1, c_strlen(NULL)); }

// c_strlen edge cases
void test_c_strlen_string_with_tabs(void) {
  TEST_ASSERT_EQUAL_INT(8, c_strlen("\t\t\thello"));
}

void test_c_strlen_string_with_end_symbol(void) {
  TEST_ASSERT_EQUAL_INT(3, c_strlen("hel\0lo"));
}

// c_strlen stress tests
void test_c_strlen_with_generated_string(size_t size) {
  char *str = malloc(size + 1);

  TEST_ASSERT_NOT_NULL(str);

  memset(str, 'a', size);
  str[size] = '\0';

  TEST_ASSERT_EQUAL_INT((int)size, c_strlen(str));
  free(str);
}

void test_c_strlen_string_size_1b(void) {
  test_c_strlen_with_generated_string(1);
}

void test_c_strlen_string_size_1kb(void) {
  test_c_strlen_with_generated_string(KB(1));
}

void test_c_strlen_string_size_4kb(void) {
  test_c_strlen_with_generated_string(KB(4));
}

void test_c_strlen_string_size_1mb(void) {
  test_c_strlen_with_generated_string(MB(1));
}

void test_c_strlen_string_size_10mb(void) {
  test_c_strlen_with_generated_string(MB(10));
}

void test_c_strlen_string_size_50mb(void) {
  test_c_strlen_with_generated_string(MB(50));
}

// --------------------

// ----------c_strcmp----------

// c_strcmp valid input data
void test_c_strcmp_equal_str(void) {
  TEST_ASSERT_EQUAL_INT(0, c_strcmp("hello", "hello"));
}

void test_c_strcmp_second_greater(void) {
  TEST_ASSERT_EQUAL_INT('a' - 'e', c_strcmp("hallo", "hello"));
}

void test_c_strcmp_first_greater(void) {
  TEST_ASSERT_EQUAL_INT('e' - 'a', c_strcmp("hello", "hallo"));
}

void test_c_strcmp_equal_upper_str(void) {
  TEST_ASSERT_EQUAL_INT(0, c_strcmp("HELLO", "HELLO"));
}

void test_c_strcmp_upper_second_smaller(void) {
  TEST_ASSERT_EQUAL_INT('h' - 'H', c_strcmp("hello", "Hello"));
}

void test_c_strcmp_upper_first_smaller(void) {
  TEST_ASSERT_EQUAL_INT('H' - 'h', c_strcmp("Hello", "hello"));
}

// c_strcmp edge cases
void test_c_strcmp_both_empty(void) {
  TEST_ASSERT_EQUAL_INT(0, c_strcmp("", ""));
}

void test_c_strcmp_first_empty(void) {
  TEST_ASSERT_EQUAL_INT('\0' - 'h', c_strcmp("", "hello"));
}

void test_c_strcmp_second_empty(void) {
  TEST_ASSERT_EQUAL_INT('h' - '\0', c_strcmp("hello", ""));
}

void test_c_strcmp_first_have_punctuation_char(void) {
  TEST_ASSERT_EQUAL_INT('@' - 'e', c_strcmp("h@llo", "hello"));
}

void test_c_strcmp_second_have_punctuation_char(void) {
  TEST_ASSERT_EQUAL_INT('e' - '{', c_strcmp("hello", "h{llo"));
}

void test_c_strcmp_both_have_punctuation_char(void) {
  TEST_ASSERT_EQUAL_INT('$' - '^', c_strcmp("$ello", "^ello"));
}

void test_c_strcmp_first_have_escape_char(void) {
  TEST_ASSERT_EQUAL_INT('\t' - 'h', c_strcmp("\t", "h"));
}

void test_c_strcmp_second_have_escape_char(void) {
  TEST_ASSERT_EQUAL_INT('h' - '\a', c_strcmp("h", "\a"));
}

// --------------------

// ----------c_remove_digits----------

// c_remove_digits valid input data
void test_c_remove_digits_str_have_1_digit(void) {
  char s[] = "string1";
  TEST_ASSERT_EQUAL_INT(1, c_remove_digits(s));
}

void test_c_remove_digits_str_have_4_digit(void) {
  char s[] = "7t01ng1";
  TEST_ASSERT_EQUAL_INT(4, c_remove_digits(s));
}

void test_c_remove_digits_str_have_all_digit(void) {
  char s[] = "123456";
  TEST_ASSERT_EQUAL_INT(6, c_remove_digits(s));
}

void test_c_remove_digits_str_have_0_digit(void) {
  char s[] = "string";
  TEST_ASSERT_EQUAL_INT(0, c_remove_digits(s));
}

// c_remove_digits edge cases
void test_c_remove_digits_str_empty(void) {
  char s[] = "";
  TEST_ASSERT_EQUAL_INT(0, c_remove_digits(s));
}

void test_c_remove_digits_str_have_end_smbl_in_middle(void) {
  char s[] = "s1r\0ng";
  TEST_ASSERT_EQUAL_INT(1, c_remove_digits(s));
}

// c_remove_digits negative tests
void test_c_remove_digits_str_is_null(void) {
  char *s = NULL;
  TEST_ASSERT_EQUAL_INT(-1, c_remove_digits(s));
}

// c_remove_digits stress tests
void test_c_remove_digits_str_have_all_digits_gen(size_t size) {
  char *str = malloc(size + 1);

  TEST_ASSERT_NOT_NULL(str);

  memset(str, '1', size);
  str[size] = '\0';

  TEST_ASSERT_EQUAL_INT(size, c_remove_digits(str));
  free(str);
}

void test_c_remove_digits_str_have_all_digits_1b(void) {
  test_c_remove_digits_str_have_all_digits_gen(1);
}

void test_c_remove_digits_str_have_all_digits_1kb(void) {
  test_c_remove_digits_str_have_all_digits_gen(KB(1));
}

void test_c_remove_digits_str_have_all_digits_4kb(void) {
  test_c_remove_digits_str_have_all_digits_gen(KB(4));
}

void test_c_remove_digits_str_have_all_digits_1mb(void) {
  test_c_remove_digits_str_have_all_digits_gen(MB(1));
}

void test_c_remove_digits_str_have_all_digits_50mb(void) {
  test_c_remove_digits_str_have_all_digits_gen(MB(50));
}

// --------------------

// ----------c_count_words----------

char *generate_n_word_string(int n, int word_size) {
  const int num_spaces = (n - 1 > 0) ? (n - 1) : 0;
  const int size = n * word_size + num_spaces + 1;
  char *str = malloc(size);

  TEST_ASSERT_NOT_NULL(str);

  int pos = 0;
  int space_counter = 0;
  for (int i = 0; i < n; ++i) {

    for (int j = 0; j < word_size; ++j) {
      str[pos++] = 'a';
    }
    if (space_counter++ < num_spaces) {
      str[pos++] = ' ';
    }
  }

  str[pos] = '\0';
  return str;
}

// c_count_words valid input data
void test_c_count_words_1_word(void) {
  char *str = generate_n_word_string(1, 5);
  TEST_ASSERT_EQUAL_INT(1, c_count_words(str));
  free(str);
}

void test_c_count_words_10_words(void) {
  char *str = generate_n_word_string(10, 5);
  TEST_ASSERT_EQUAL_INT(10, c_count_words(str));
  free(str);
}

// c_count_words edge cases

void test_c_count_words_delim_is_punct_char(void) {
  TEST_ASSERT_EQUAL_INT(2, c_count_words("hello@hello"));
}

void test_c_count_words_empty_string(void) {
  TEST_ASSERT_EQUAL_INT(0, c_count_words(""));
}

void test_c_count_words_only_spaces(void) {
  TEST_ASSERT_EQUAL_INT(0, c_count_words("   "));
}

void test_c_count_words_delim_tab(void) {
  TEST_ASSERT_EQUAL_INT(2, c_count_words("hello\t\tworld"));
}

void test_c_count_words_extra_spaces_and_tabs(void) {
  TEST_ASSERT_EQUAL_INT(2, c_count_words("  \thello\t\tworld\t "));
}

// c_count_words negative tests

void test_c_count_words_null(void) {
  TEST_ASSERT_EQUAL_INT(-1, c_count_words(NULL));
}

// c_count_words stress tests

void test_c_count_words_string_size_1b(void) {
  TEST_ASSERT_EQUAL_INT(1, c_count_words("s"));
}

void test_c_count_words_string_size_1kb(void) {
  // 256 words(3 letters and 1 space) in 1024 bites
  char *str = generate_n_word_string(250, 5);
  TEST_ASSERT_EQUAL_INT(250, c_count_words(str));
  free(str);
}

void test_c_count_words_string_size_4kb(void) {
  // 680 words(5 letters and 1 space) in 4096 bites
  char *str = generate_n_word_string(500, 10);
  TEST_ASSERT_EQUAL_INT(670, c_count_words(str));
  free(str);
}

void test_c_count_words_string_size_1mb(void) {
  // 95300 words(10 letters and 1 space) in 1mb
  char *str = generate_n_word_string(95300, 10);
  TEST_ASSERT_EQUAL_INT(1, c_count_words(str));
  free(str);
}

// --------------------

// ----------c_first_unique_char------------

// c_first_unique_char valid input data

void test_c_first_unique_char_normal(void) {
  TEST_ASSERT_EQUAL_INT(0, c_first_unique_char("Hello"));
}

void test_c_first_unique_char_all_duplicates(void) {
  TEST_ASSERT_EQUAL_INT(-2, c_first_unique_char("AAbbcc"));
}

void test_c_first_unique_char_with_punctuations(void) {
  TEST_ASSERT_EQUAL_INT(1, c_first_unique_char("s@s"));
}

// c_first_unique_char edge cases

void test_c_first_unique_char_empty_string(void) {
  TEST_ASSERT_EQUAL_INT(-2, c_first_unique_char(""));
}

void test_c_first_unique_char_one_space(void) {
  TEST_ASSERT_EQUAL_INT(0, c_first_unique_char(" "));
}

void test_c_first_unique_char_all_spaces(void) {
  TEST_ASSERT_EQUAL_INT(-2, c_first_unique_char("   "));
}

void test_c_first_unique_char_escape_sqn(void) {
  TEST_ASSERT_EQUAL_INT(4, c_first_unique_char("aa  \n"));
}

// c_first_unique_char negative tests

void test_c_first_unique_char_null(void) {
  TEST_ASSERT_EQUAL_INT(-1, c_first_unique_char(NULL));
}

// c_first_unique_char stress tests

void test_c_first_unique_char_generate_string(size_t size) {
  char *str = calloc(size + 1, sizeof(char));
  TEST_ASSERT_NOT_NULL(str);

  memset(str, 'a', size - 1);
  str[size - 1] = 'b';
  TEST_ASSERT_EQUAL_INT(size - 1, c_first_unique_char(str));

  free(str);
}

void test_c_first_unique_char_in_the_end_1b(void) {
  test_c_first_unique_char_generate_string(1);
}

void test_c_first_unique_char_in_the_end_1kb(void) {
  test_c_first_unique_char_generate_string(KB(1));
}

void test_c_first_unique_char_in_the_end_4kb(void) {
  test_c_first_unique_char_generate_string(KB(4));
}

void test_c_first_unique_char_in_the_end_1mb(void) {
  test_c_first_unique_char_generate_string(MB(1));
}

void test_c_first_unique_char_in_the_end_10mb(void) {
  test_c_first_unique_char_generate_string(MB(10));
}

//

int main(void) {

  UNITY_BEGIN();

  printf("\n----------C_STRLEN TESTS STARTED----------");

  TEST_VALID_INPUT_DATA;
  RUN_TEST(test_c_strlen_empty_string);
  RUN_TEST(test_c_strlen_short_string);
  RUN_TEST(test_c_strlen_string_with_spaces);

  TEST_EDGE_CASES;
  RUN_TEST(test_c_strlen_string_with_tabs);
  RUN_TEST(test_c_strlen_string_with_end_symbol);

  NEGATIVE_TESTS;
  RUN_TEST(test_c_strlen_null);

  STRESS_TESTS;
  RUN_TEST(test_c_strlen_string_size_1b);
  RUN_TEST(test_c_strlen_string_size_1kb);
  RUN_TEST(test_c_strlen_string_size_4kb);
  RUN_TEST(test_c_strlen_string_size_1mb);
  RUN_TEST(test_c_strlen_string_size_50mb);

  printf("----------C_STRLEN TESTS ENDED----------\n");

  printf("\n----------C_STRCMP TESTS STARTED----------");
  TEST_VALID_INPUT_DATA;
  RUN_TEST(test_c_strcmp_equal_str);
  RUN_TEST(test_c_strcmp_second_greater);
  RUN_TEST(test_c_strcmp_first_greater);
  RUN_TEST(test_c_strcmp_equal_upper_str);
  RUN_TEST(test_c_strcmp_upper_second_smaller);
  RUN_TEST(test_c_strcmp_upper_first_smaller);
  TEST_EDGE_CASES;
  RUN_TEST(test_c_strcmp_both_empty);
  RUN_TEST(test_c_strcmp_first_empty);
  RUN_TEST(test_c_strcmp_second_empty);
  RUN_TEST(test_c_strcmp_first_have_punctuation_char);
  RUN_TEST(test_c_strcmp_second_have_punctuation_char);
  RUN_TEST(test_c_strcmp_both_have_punctuation_char);
  RUN_TEST(test_c_strcmp_first_have_escape_char);
  RUN_TEST(test_c_strcmp_second_have_escape_char);
  printf("----------C_STRCMP TESTS ENDED----------\n");

  printf("\n----------C_REMOVE_DIGITS TESTS STARTED----------");
  TEST_VALID_INPUT_DATA;
  RUN_TEST(test_c_remove_digits_str_have_0_digit);
  RUN_TEST(test_c_remove_digits_str_have_1_digit);
  RUN_TEST(test_c_remove_digits_str_have_4_digit);
  RUN_TEST(test_c_remove_digits_str_have_all_digit);
  TEST_EDGE_CASES;
  RUN_TEST(test_c_remove_digits_str_empty);
  RUN_TEST(test_c_remove_digits_str_have_end_smbl_in_middle);
  NEGATIVE_TESTS;
  RUN_TEST(test_c_remove_digits_str_is_null);
  STRESS_TESTS;
  RUN_TEST(test_c_remove_digits_str_have_all_digits_1b);
  RUN_TEST(test_c_remove_digits_str_have_all_digits_1kb);
  RUN_TEST(test_c_remove_digits_str_have_all_digits_4kb);
  RUN_TEST(test_c_remove_digits_str_have_all_digits_1mb);
  RUN_TEST(test_c_remove_digits_str_have_all_digits_50mb);
  printf("----------C_REMOVE_DIGITS TESTS ENDED----------\n");

  printf("\n----------C_COUNT_WORDS TESTS STARTED----------\n");
  TEST_VALID_INPUT_DATA;
  RUN_TEST(test_c_count_words_1_word);
  RUN_TEST(test_c_count_words_10_words);
  TEST_EDGE_CASES;
  RUN_TEST(test_c_count_words_delim_is_punct_char);
  RUN_TEST(test_c_count_words_delim_tab);
  RUN_TEST(test_c_count_words_extra_spaces_and_tabs);
  RUN_TEST(test_c_count_words_only_spaces);
  RUN_TEST(test_c_count_words_empty_string);
  NEGATIVE_TESTS;
  RUN_TEST(test_c_count_words_null);
  STRESS_TESTS;
  RUN_TEST(test_c_count_words_string_size_1b);
  RUN_TEST(test_c_count_words_string_size_1kb);
  // 4kb > stack_overflow - very large local array
  // RUN_TEST(test_c_count_words_string_size_4kb);
  printf("----------C_COUNT_WORDS TESTS ENDED----------\n");

  printf("\n----------C_FIRST_UNIQUE_CHAR TESTS STARTED----------\n");
  TEST_VALID_INPUT_DATA;
  RUN_TEST(test_c_first_unique_char_normal);
  RUN_TEST(test_c_first_unique_char_all_duplicates);
  RUN_TEST(test_c_first_unique_char_with_punctuations);
  TEST_EDGE_CASES;
  RUN_TEST(test_c_first_unique_char_empty_string);
  RUN_TEST(test_c_first_unique_char_one_space);
  RUN_TEST(test_c_first_unique_char_all_spaces);
  RUN_TEST(test_c_first_unique_char_escape_sqn);
  NEGATIVE_TESTS;
  RUN_TEST(test_c_first_unique_char_null);
  STRESS_TESTS;
  RUN_TEST(test_c_first_unique_char_in_the_end_1b);
  RUN_TEST(test_c_first_unique_char_in_the_end_1kb);
  RUN_TEST(test_c_first_unique_char_in_the_end_4kb);
  RUN_TEST(test_c_first_unique_char_in_the_end_1mb);
  RUN_TEST(test_c_first_unique_char_in_the_end_10mb);
  printf("----------C_FIRST_UNIQUE_CHAR TESTS ENDED----------\n");

  return UNITY_END();
}
