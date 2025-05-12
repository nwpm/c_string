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
char *genarate_one_char_str(size_t size, const char c) {
  char *str = malloc(size + 1);

  TEST_ASSERT_NOT_NULL(str);

  memset(str, c, size);
  str[size] = '\0';

  return str;
}

void test_c_strlen_string_size_1b(void) {
  char *str = genarate_one_char_str(1, 'a');
  TEST_ASSERT_EQUAL_INT(1, c_strlen(str));
  free(str);
}

void test_c_strlen_string_size_1kb(void) {
  char *str = genarate_one_char_str(KB(1), 'a');
  TEST_ASSERT_EQUAL_INT(KB(1), c_strlen(str));
  free(str);
}

void test_c_strlen_string_size_4kb(void) {
  char *str = genarate_one_char_str(KB(4), 'a');
  TEST_ASSERT_EQUAL_INT(KB(4), c_strlen(str));
  free(str);
}

void test_c_strlen_string_size_1mb(void) {
  char *str = genarate_one_char_str(MB(1), 'a');
  TEST_ASSERT_EQUAL_INT(MB(1), c_strlen(str));
  free(str);
}

void test_c_strlen_string_size_10mb(void) {
  char *str = genarate_one_char_str(MB(10), 'a');
  TEST_ASSERT_EQUAL_INT(MB(10), c_strlen(str));
  free(str);
}

void test_c_strlen_string_size_50mb(void) {
  char *str = genarate_one_char_str(MB(50), 'a');
  TEST_ASSERT_EQUAL_INT(MB(50), c_strlen(str));
  free(str);
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

// ----------c_strstr----------

// c_strstr valid unput data
void test_c_strstr_valid_data(void) {
  TEST_ASSERT_EQUAL_INT(1, c_strstr("abcdef", "bcd"));
}

void test_c_strstr_valid_data_2(void) {
  TEST_ASSERT_EQUAL_INT(0, c_strstr("Abcdef", "Abc"));
}

void test_c_strstr_valid_data_3(void) {
  TEST_ASSERT_EQUAL_INT(3, c_strstr("Abcd@f", "d@f"));
}

// c_strstr edge cases

void test_c_strstr_find_in_empty_str(void) {
  TEST_ASSERT_EQUAL_INT(-1, c_strstr("", "abc"));
}

void test_c_strstr_find_empty_substr(void) {
  TEST_ASSERT_EQUAL_INT(-1, c_strstr("abc", ""));
}

void test_c_strstr_find_empty_in_empty(void) {
  TEST_ASSERT_EQUAL_INT(-1, c_strstr("", ""));
}

// c_strstr negative tests

void test_c_strstr_str_null(void) {
  TEST_ASSERT_EQUAL_INT(-1, c_strstr(NULL, "abc"));
}

void test_c_strstr_substr_null(void) {
  TEST_ASSERT_EQUAL_INT(-1, c_strstr("abc", NULL));
}

void test_c_strstr_both_null(void) {
  TEST_ASSERT_EQUAL_INT(-1, c_strstr(NULL, NULL));
}

// c_strstr stress tests

void test_c_strstr_str_1b(void) {
  char *str = genarate_one_char_str(1, 'a');
  TEST_ASSERT_EQUAL_INT(0, c_strstr(str, "a"));
  free(str);
}

void test_c_strstr_str_1kb(void) {
  char *str = genarate_one_char_str(KB(1), 'a');
  size_t last_index = KB(1) - 1;
  str[last_index] = 'b';
  TEST_ASSERT_EQUAL_INT(last_index, c_strstr(str, "b"));
  free(str);
}

void test_c_strstr_str_1mb(void) {
  char *str = genarate_one_char_str(MB(1), 'a');
  size_t last_index = MB(1) - 1;
  str[last_index] = 'b';
  TEST_ASSERT_EQUAL_INT(last_index, c_strstr(str, "b"));
  free(str);
}

void test_c_strstr_str_10mb(void) {
  char *str = genarate_one_char_str(MB(10), 'a');
  size_t last_index = MB(10) - 1;
  str[last_index] = 'b';
  TEST_ASSERT_EQUAL_INT(last_index, c_strstr(str, "b"));
  free(str);
}

// ----------------------------

// ----------c_num_substr----------

// c_num_substr valid input data

void test_c_num_substr_valid_data(void) {
  TEST_ASSERT_EQUAL_INT(1, c_num_substr("aaaaaaab", "ab"));
}

void test_c_num_substr_valid_data_2(void) {
  TEST_ASSERT_EQUAL_INT(1, c_num_substr("abc", "abc"));
}

void test_c_num_substr_valid_data_3(void) {
  TEST_ASSERT_EQUAL_INT(0, c_num_substr("abc", "def"));
}

void test_c_num_substr_valid_data_4(void) {
  TEST_ASSERT_EQUAL_INT(2, c_num_substr("aaaabcaaabc", "bc"));
}

// c_num_substr edge cases

void test_c_num_substr_substr_empty(void) {
  TEST_ASSERT_EQUAL_INT(0, c_num_substr("abc", ""));
}

void test_c_num_substr_str_empty(void) {
  TEST_ASSERT_EQUAL_INT(0, c_num_substr("", "abc"));
}

void test_c_num_substr_both_empty(void) {
  TEST_ASSERT_EQUAL_INT(0, c_num_substr("", ""));
}

// c_num_substr negative tests

void test_c_num_substr_str_null(void) {
  TEST_ASSERT_EQUAL_INT(-1, c_num_substr(NULL, "abc"));
}

void test_c_num_substr_substr_null(void) {
  TEST_ASSERT_EQUAL_INT(-1, c_num_substr("abc", NULL));
}

// c_num_substr stress tests

// --------------------------------

// ----------c_atoi----------

// c_atoi valid input data

void test_c_atoi_valid_data(void) {
  TEST_ASSERT_EQUAL_INT(123456, c_atoi("123456"));
}

void test_c_atoi_valid_data_2(void) {
  TEST_ASSERT_EQUAL_INT(-123456, c_atoi("-123456"));
}

void test_c_atoi_valid_data_3(void) {
  TEST_ASSERT_EQUAL_INT(-456, c_atoi("-0000000456"));
}

void test_c_atoi_valid_data_4(void) {
  TEST_ASSERT_EQUAL_INT(123, c_atoi("0000000123"));
}

// c_atoi edge cases

void test_c_atoi_not_digit_in_str(void) {
  TEST_ASSERT_EQUAL_INT(12, c_atoi("12b3456"));
}

void test_c_atoi_not_digit_in_negative_str(void) {
  TEST_ASSERT_EQUAL_INT(-12, c_atoi("-12b3456"));
}

void test_c_atoi_start_with_not_digit(void) {
  TEST_ASSERT_EQUAL_INT(0, c_atoi("m12b3456"));
}

void test_c_atoi_start_with_not_digit_negative(void) {
  TEST_ASSERT_EQUAL_INT(0, c_atoi("-m12b3456"));
}

void test_c_atoi_empty_str(void) { TEST_ASSERT_EQUAL_INT(0, c_atoi("")); }

// c_atoi nefative tests

// --------------------------

// ----------c_is_palindrome----------

// c_is_palindrome valid input data

void test_c_is_palindrome_valid_data(void) {
  TEST_ASSERT_EQUAL_INT(TRUE, c_is_palindrom("aabbaa"));
}

void test_c_is_palindrome_valid_data_2(void) {
  TEST_ASSERT_EQUAL_INT(TRUE, c_is_palindrom("a"));
}

void test_c_is_palindrome_valid_data_3(void) {
  TEST_ASSERT_EQUAL_INT(FALSE, c_is_palindrom("abc"));
}

// c_is_palindrom edge cases

void test_c_is_palindrome_empty_str(void) {
  TEST_ASSERT_EQUAL_INT(FALSE, c_is_palindrom(""));
}

// -----------------------------------

// ----------c_is_string_of_digits----------

// c_is_string_of_digits valid input data

void test_c_is_string_of_digits_valid_data(void) {
  TEST_ASSERT_EQUAL_INT(TRUE, c_is_string_of_digits("123456"));
}

void test_c_is_string_of_digits_valid_data_2(void) {
  TEST_ASSERT_EQUAL_INT(FALSE, c_is_string_of_digits("12b"));
}

void test_c_is_string_of_digits_valid_data_3(void) {
  TEST_ASSERT_EQUAL_INT(FALSE, c_is_string_of_digits("abc"));
}

// c_is_string_of_digits edge cases

void test_c_is_string_of_digits_empty_string(void) {
  TEST_ASSERT_EQUAL_INT(FALSE, c_is_string_of_digits(""));
}

// -----------------------------------------

// ----------c_is_punct_char----------

// c_is_punct_char valid input data

void test_c_is_punct_char_valid_data(void) {
  TEST_ASSERT_EQUAL_INT(TRUE, c_is_punct_char('&'));
}

void test_c_is_punct_char_valid_data_2(void) {
  TEST_ASSERT_EQUAL_INT(FALSE, c_is_punct_char('b'));
}

void test_c_is_punct_char_valid_data_3(void) {
  TEST_ASSERT_EQUAL_INT(FALSE, c_is_punct_char('\0'));
}

void test_c_is_punct_char_valid_data_4(void) {
  TEST_ASSERT_EQUAL_INT(TRUE, c_is_punct_char(33));
}

void test_c_is_punct_char_valid_data_5(void) {
  TEST_ASSERT_EQUAL_INT(FALSE, c_is_punct_char(12));
}

// -----------------------------------

// ----------c_is_letter----------

// c_is_letter valid input data

void test_c_is_letter_valid_data(void) {
  TEST_ASSERT_EQUAL_INT(TRUE, c_is_letter('b'));
}

void test_c_is_letter_valid_data_2(void) {
  TEST_ASSERT_EQUAL_INT(FALSE, c_is_letter('1'));
}

void test_c_is_letter_valid_data_3(void) {
  TEST_ASSERT_EQUAL_INT(FALSE, c_is_letter('@'));
}

void test_c_is_letter_valid_data_4(void) {
  TEST_ASSERT_EQUAL_INT(FALSE, c_is_letter(24));
}

// -------------------------------

// ----------c_is_digit----------

// c_is_digit valid input data

void test_c_is_digit_valid_data(void) {
  TEST_ASSERT_EQUAL_INT(TRUE, c_is_digit('3'));
}

void test_c_is_digit_valid_data_2(void) {
  TEST_ASSERT_EQUAL_INT(FALSE, c_is_digit('a'));
}

void test_c_is_digit_valid_data_3(void) {
  TEST_ASSERT_EQUAL_INT(FALSE, c_is_digit('@'));
}

void test_c_is_digit_valid_data_4(void) {
  TEST_ASSERT_EQUAL_INT(FALSE, c_is_digit(97));
}

// ------------------------------

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

  printf("\n----------C_STRSTR TESTS STARTED----------\n");
  TEST_VALID_INPUT_DATA;
  RUN_TEST(test_c_strstr_valid_data);
  RUN_TEST(test_c_strstr_valid_data_2);
  RUN_TEST(test_c_strstr_valid_data_3);
  TEST_EDGE_CASES;
  RUN_TEST(test_c_strstr_find_in_empty_str);
  RUN_TEST(test_c_strstr_find_empty_substr);
  RUN_TEST(test_c_strstr_find_empty_in_empty);
  NEGATIVE_TESTS;
  RUN_TEST(test_c_strstr_substr_null);
  RUN_TEST(test_c_strstr_str_null);
  RUN_TEST(test_c_strstr_both_null);
  STRESS_TESTS;
  RUN_TEST(test_c_strstr_str_1b);
  RUN_TEST(test_c_strstr_str_1kb);
  RUN_TEST(test_c_strstr_str_1mb);
  RUN_TEST(test_c_strstr_str_10mb);
  printf("----------C_STRSTR TESTS ENDED----------\n");

  printf("\n----------C_NUM_SUBSTR STARTED----------\n");
  TEST_VALID_INPUT_DATA;
  RUN_TEST(test_c_num_substr_valid_data);
  RUN_TEST(test_c_num_substr_valid_data_2);
  RUN_TEST(test_c_num_substr_valid_data_3);
  RUN_TEST(test_c_num_substr_valid_data_4);
  TEST_EDGE_CASES;
  RUN_TEST(test_c_num_substr_str_empty);
  RUN_TEST(test_c_num_substr_substr_empty);
  RUN_TEST(test_c_num_substr_both_empty);
  NEGATIVE_TESTS;
  RUN_TEST(test_c_num_substr_substr_null);
  RUN_TEST(test_c_num_substr_str_null);
  printf("----------C_NUM_SUBSTR ENDED----------\n");

  printf("\n----------C_ATOI STARTED----------\n");
  TEST_VALID_INPUT_DATA;
  RUN_TEST(test_c_atoi_valid_data);
  RUN_TEST(test_c_atoi_valid_data_2);
  RUN_TEST(test_c_atoi_valid_data_3);
  RUN_TEST(test_c_atoi_valid_data_4);
  TEST_EDGE_CASES;
  RUN_TEST(test_c_atoi_not_digit_in_str);
  RUN_TEST(test_c_atoi_not_digit_in_negative_str);
  RUN_TEST(test_c_atoi_start_with_not_digit);
  RUN_TEST(test_c_atoi_start_with_not_digit_negative);
  RUN_TEST(test_c_atoi_empty_str);
  printf("----------C_ATOI ENDED----------\n");

  printf("\n----------C_IS_PALINDROM STARTED----------\n");
  TEST_VALID_INPUT_DATA;
  RUN_TEST(test_c_is_palindrome_valid_data);
  RUN_TEST(test_c_is_palindrome_valid_data_2);
  RUN_TEST(test_c_is_palindrome_valid_data_3);
  TEST_EDGE_CASES;
  RUN_TEST(test_c_is_palindrome_empty_str);
  printf("----------C_IS_PALINDROM ENDED----------\n");

  printf("\n----------C_IS_STRING_OF_DIGITS STARTED----------\n");
  TEST_VALID_INPUT_DATA;
  RUN_TEST(test_c_is_string_of_digits_valid_data);
  RUN_TEST(test_c_is_string_of_digits_valid_data_2);
  RUN_TEST(test_c_is_string_of_digits_valid_data_3);
  TEST_EDGE_CASES;
  RUN_TEST(test_c_is_string_of_digits_empty_string);
  printf("----------C_IS_STRING_OF_DIGITS ENDED----------\n");

  printf("\n----------C_IS_PUNCT_CHAR STARTED----------\n");
  TEST_VALID_INPUT_DATA;
  RUN_TEST(test_c_is_punct_char_valid_data);
  RUN_TEST(test_c_is_punct_char_valid_data_2);
  RUN_TEST(test_c_is_punct_char_valid_data_3);
  RUN_TEST(test_c_is_punct_char_valid_data_4);
  RUN_TEST(test_c_is_punct_char_valid_data_5);
  printf("----------C_IS_PUNCT_CHAR ENDED----------\n");

  printf("\n----------C_IS_LETTER STARTED----------\n");
  TEST_VALID_INPUT_DATA;
  RUN_TEST(test_c_is_letter_valid_data);
  RUN_TEST(test_c_is_letter_valid_data_2);
  RUN_TEST(test_c_is_letter_valid_data_3);
  RUN_TEST(test_c_is_letter_valid_data_4);
  printf("----------C_IS_LETTER ENDED----------\n");

  printf("\n----------C_IS_DIGIT STARTED----------\n");
  TEST_VALID_INPUT_DATA;
  RUN_TEST(test_c_is_digit_valid_data);
  RUN_TEST(test_c_is_digit_valid_data_2);
  RUN_TEST(test_c_is_digit_valid_data_3);
  RUN_TEST(test_c_is_digit_valid_data_4);
  printf("----------C_IS_DIGIT ENDED----------\n");

  return UNITY_END();
}
