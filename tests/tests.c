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

#define TEST_BLOCK_START_HEADER(name)                                          \
  printf("\n========== Running %s Tests ==========\n", name)

#define TEST_BLOCK_END_HEADER(name)                                            \
  printf("========== End %s Tests ==========\n", name)

void setUp(void) {}

void tearDown(void) {}

// ----------c_strlen tests----------

// c_strlen valid input data
void test_c_strlen_when_string_empty(void) {
  TEST_ASSERT_EQUAL_INT(0, c_strlen(""));
}

void test_c_strlen_when_given_single_word(void) {
  TEST_ASSERT_EQUAL_INT(5, c_strlen("hello"));
}

void test_c_strlen_when_string_has_spaces(void) {
  TEST_ASSERT_EQUAL_INT(11, c_strlen("hello world"));
}

// c_strlen negative tests
void test_c_strlen_when_input_null(void) {
  TEST_ASSERT_EQUAL_INT(-1, c_strlen(NULL));
}

// c_strlen edge cases
void test_c_strlen_when_string_has_tabs(void) {
  TEST_ASSERT_EQUAL_INT(8, c_strlen("\t\t\thello"));
}

void test_c_strlen_when_string_has_end_symbol_in_middle(void) {
  TEST_ASSERT_EQUAL_INT(3, c_strlen("hel\0lo"));
}

// --------------------

// ----------c_strcmp----------

// c_strcmp valid input data
void test_c_strcmp_when_strings_equal(void) {
  TEST_ASSERT_EQUAL_INT(0, c_strcmp("hello", "hello"));
}

void test_c_strcmp_when_second_str_greater(void) {
  TEST_ASSERT_EQUAL_INT('a' - 'e', c_strcmp("hallo", "hello"));
}

void test_c_strcmp_when_first_str_greater(void) {
  TEST_ASSERT_EQUAL_INT('e' - 'a', c_strcmp("hello", "hallo"));
}

void test_c_strcmp_when_strs_equal_and_uppercase(void) {
  TEST_ASSERT_EQUAL_INT(0, c_strcmp("HELLO", "HELLO"));
}

void test_c_strcmp_when_second_start_with_uppercase_first_with_lowercase(void) {
  TEST_ASSERT_EQUAL_INT('h' - 'H', c_strcmp("hello", "Hello"));
}

void test_c_strcmp_when_first_start_with_uppercase_second_with_lowercase(void) {
  TEST_ASSERT_EQUAL_INT('H' - 'h', c_strcmp("Hello", "hello"));
}

// c_strcmp edge cases
void test_c_strcmp_when_both_empty(void) {
  TEST_ASSERT_EQUAL_INT(0, c_strcmp("", ""));
}

void test_c_strcmp_when_first_str_empty(void) {
  TEST_ASSERT_EQUAL_INT('\0' - 'h', c_strcmp("", "hello"));
}

void test_c_strcmp_when_second_str_empty(void) {
  TEST_ASSERT_EQUAL_INT('h' - '\0', c_strcmp("hello", ""));
}

void test_c_strcmp_when_first_string_have_non_letter_char(void) {
  TEST_ASSERT_EQUAL_INT('@' - 'e', c_strcmp("h@llo", "hello"));
}

void test_c_strcmp_when_second_string_have_non_letter_char(void) {
  TEST_ASSERT_EQUAL_INT('e' - '{', c_strcmp("hello", "h{llo"));
}

void test_c_strcmp_when_both_have_non_letter_char(void) {
  TEST_ASSERT_EQUAL_INT('$' - '^', c_strcmp("$ello", "^ello"));
}

void test_c_strcmp_when_first_have_escape_char(void) {
  TEST_ASSERT_EQUAL_INT('\t' - 'h', c_strcmp("\t", "h"));
}

void test_c_strcmp_when_second_have_escape_char(void) {
  TEST_ASSERT_EQUAL_INT('h' - '\a', c_strcmp("h", "\a"));
}

// --------------------

// ----------c_remove_digits----------

// c_remove_digits valid input data
void test_c_remove_digits_when_str_have_1_digit(void) {
  char s[] = "string1";
  TEST_ASSERT_EQUAL_INT(1, c_remove_digits(s));
}

void test_c_remove_digits_when_str_have_4_digits(void) {
  char s[] = "7t01ng1";
  TEST_ASSERT_EQUAL_INT(4, c_remove_digits(s));
}

void test_c_remove_digits_when_str_have_all_digits(void) {
  char s[] = "123456";
  TEST_ASSERT_EQUAL_INT(6, c_remove_digits(s));
}

void test_c_remove_digits_when_str_have_no_digits(void) {
  char s[] = "string";
  TEST_ASSERT_EQUAL_INT(0, c_remove_digits(s));
}

// c_remove_digits edge cases
void test_c_remove_digits_when_str_empty(void) {
  char s[] = "";
  TEST_ASSERT_EQUAL_INT(0, c_remove_digits(s));
}

void test_c_remove_digits_when_str_have_end_symbol_in_middle(void) {
  char s[] = "s1r\0ng";
  TEST_ASSERT_EQUAL_INT(1, c_remove_digits(s));
}

// c_remove_digits negative tests
void test_c_remove_digits_when_str_is_null(void) {
  char *s = NULL;
  TEST_ASSERT_EQUAL_INT(-1, c_remove_digits(s));
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
void test_c_count_words_when_single_word(void) {
  char *str = generate_n_word_string(1, 5);
  TEST_ASSERT_EQUAL_INT(1, c_count_words(str));
  free(str);
}

void test_c_count_words_when_string_has_10_words(void) {
  char *str = generate_n_word_string(10, 5);
  TEST_ASSERT_EQUAL_INT(10, c_count_words(str));
  free(str);
}

// c_count_words edge cases

void test_c_count_words_when_delim_is_punct_char(void) {
  TEST_ASSERT_EQUAL_INT(2, c_count_words("hello@hello"));
}

void test_c_count_words_when_string_empty(void) {
  TEST_ASSERT_EQUAL_INT(0, c_count_words(""));
}

void test_c_count_words_when_str_is_only_spaces(void) {
  TEST_ASSERT_EQUAL_INT(0, c_count_words("   "));
}

void test_c_count_words_when_delim_is_tab(void) {
  TEST_ASSERT_EQUAL_INT(2, c_count_words("hello\t\tworld"));
}

void test_c_count_words_when_string_has_extra_spaces_and_tabs(void) {
  TEST_ASSERT_EQUAL_INT(2, c_count_words("  \thello\t\tworld\t "));
}

// c_count_words negative tests

void test_c_count_words_when_input_null(void) {
  TEST_ASSERT_EQUAL_INT(-1, c_count_words(NULL));
}

// --------------------

// ----------c_first_unique_char------------

// c_first_unique_char valid input data

void test_c_first_unique_char_when_single_word(void) {
  TEST_ASSERT_EQUAL_INT(0, c_first_unique_char("Hello"));
}

void test_c_first_unique_char_when_string_is_paired_letters(void) {
  TEST_ASSERT_EQUAL_INT(-2, c_first_unique_char("AAbbcc"));
}

void test_c_first_unique_char_when_string_has_non_letter(void) {
  TEST_ASSERT_EQUAL_INT(1, c_first_unique_char("s@s"));
}

// c_first_unique_char edge cases

void test_c_first_unique_char_when_string_empty(void) {
  TEST_ASSERT_EQUAL_INT(-2, c_first_unique_char(""));
}

void test_c_first_unique_char_when_string_is_single_space(void) {
  TEST_ASSERT_EQUAL_INT(0, c_first_unique_char(" "));
}

void test_c_first_unique_char_when_string_is_all_spaces(void) {
  TEST_ASSERT_EQUAL_INT(-2, c_first_unique_char("   "));
}

void test_c_first_unique_char_when_string_has_escape_sequence_char(void) {
  TEST_ASSERT_EQUAL_INT(4, c_first_unique_char("aa  \n"));
}

// c_first_unique_char negative tests

void test_c_first_unique_char_when_string_is_null(void) {
  TEST_ASSERT_EQUAL_INT(-1, c_first_unique_char(NULL));
}

//

// ----------c_strstr----------

// c_strstr valid unput data
void test_c_strstr_when_substr_in_str(void) {
  TEST_ASSERT_EQUAL_INT(1, c_strstr("abcdef", "bcd"));
}

void test_c_strstr_when_substr_in_str_both_have_uppercase_letter(void) {
  TEST_ASSERT_EQUAL_INT(0, c_strstr("Abcdef", "Abc"));
}

void test_c_strstr_when_substr_in_str_both_have_non_letter_char(void) {
  TEST_ASSERT_EQUAL_INT(3, c_strstr("Abcd@f", "d@f"));
}

// c_strstr edge cases

void test_c_strstr_when_str_empty_substr_not(void) {
  TEST_ASSERT_EQUAL_INT(-1, c_strstr("", "abc"));
}

void test_c_strstr_when_substr_empty_str_not(void) {
  TEST_ASSERT_EQUAL_INT(-1, c_strstr("abc", ""));
}

void test_c_strstr_when_both_empty(void) {
  TEST_ASSERT_EQUAL_INT(-1, c_strstr("", ""));
}

// c_strstr negative tests

void test_c_strstr_when_str_is_null(void) {
  TEST_ASSERT_EQUAL_INT(-1, c_strstr(NULL, "abc"));
}

void test_c_strstr_when_substr_is_null(void) {
  TEST_ASSERT_EQUAL_INT(-1, c_strstr("abc", NULL));
}

// ----------------------------

// ----------c_num_substr----------

// c_num_substr valid input data

void test_c_num_substr_when_one_substr_in_end_string(void) {
  TEST_ASSERT_EQUAL_INT(1, c_num_substr("aaaaaaab", "ab"));
}

void test_c_num_substr_when_substr_is_string(void) {
  TEST_ASSERT_EQUAL_INT(1, c_num_substr("abc", "abc"));
}

void test_c_num_substr_when_substr_not_in_string(void) {
  TEST_ASSERT_EQUAL_INT(0, c_num_substr("abc", "def"));
}

void test_c_num_substr_when_string_has_two_substr(void) {
  TEST_ASSERT_EQUAL_INT(2, c_num_substr("aaaabcaaabc", "bc"));
}

// c_num_substr edge cases

void test_c_num_substr_when_substr_empty_string_not(void) {
  TEST_ASSERT_EQUAL_INT(0, c_num_substr("abc", ""));
}

void test_c_num_substr_when_string_empty_substr_not(void) {
  TEST_ASSERT_EQUAL_INT(0, c_num_substr("", "abc"));
}

void test_c_num_substr_when_both_empty(void) {
  TEST_ASSERT_EQUAL_INT(0, c_num_substr("", ""));
}

// c_num_substr negative tests

void test_c_num_substr_when_string_is_null(void) {
  TEST_ASSERT_EQUAL_INT(-1, c_num_substr(NULL, "abc"));
}

void test_c_num_substr_when_substr_is_null(void) {
  TEST_ASSERT_EQUAL_INT(-1, c_num_substr("abc", NULL));
}

// --------------------------------

// ----------c_atoi----------

// c_atoi valid input data

void test_c_atoi_when_input_string_is_correct_number(void) {
  TEST_ASSERT_EQUAL_INT(123456, c_atoi("123456"));
}

void test_c_atoi_when_input_string_is_correct_negative_number(void) {
  TEST_ASSERT_EQUAL_INT(-123456, c_atoi("-123456"));
}

void test_c_atoi_when_input_str_is_correct_negative_num_with_leading_zeroes(
    void) {
  TEST_ASSERT_EQUAL_INT(-456, c_atoi("-0000000456"));
}

void test_c_atoi_when_input_str_is_correct_num_with_leading_zeroes(void) {
  TEST_ASSERT_EQUAL_INT(123, c_atoi("0000000123"));
}

// c_atoi edge cases

void test_c_atoi_when_string_has_not_number_char_in_middle(void) {
  TEST_ASSERT_EQUAL_INT(12, c_atoi("12b3456"));
}

void test_c_atoi_when_string_has_not_number_char_in_middle_negative_num(void) {
  TEST_ASSERT_EQUAL_INT(-12, c_atoi("-12b3456"));
}

void test_c_atoi_when_first_char_is_letter(void) {
  TEST_ASSERT_EQUAL_INT(0, c_atoi("m12b3456"));
}

void test_c_atoi_when_first_char_is_minus_second_letter(void) {
  TEST_ASSERT_EQUAL_INT(0, c_atoi("-m12b3456"));
}

/*
void test_c_atoi_when_input_string_empty(void) {
  TEST_ASSERT_EQUAL_INT(0, c_atoi(""));
}

void test_c_atoi_when_input_is_null(void) {
  c_atoi(NULL);
  TEST_PASS();
}
*/

// --------------------------

// ----------c_is_palindrome----------

// c_is_palindrome valid input data

void test_c_is_palindrom_when_input_string_correct_palindrom(void) {
  TEST_ASSERT_EQUAL_INT(TRUE, c_is_palindrom("aabbaa"));
}

void test_c_is_palindrom_when_string_is_single_char(void) {
  TEST_ASSERT_EQUAL_INT(TRUE, c_is_palindrom("a"));
}

void test_c_is_palindrom_when_string_not_palindrom(void) {
  TEST_ASSERT_EQUAL_INT(FALSE, c_is_palindrom("abc"));
}

void test_c_is_palindrom_when_string_has_end_string_char_in_middle(void) {
  TEST_ASSERT_EQUAL_INT(FALSE, c_is_palindrom("ab\0ba"));
}

void test_c_is_palindrom_when_input_string_correct_palindrom_with_punct_chars(
    void) {
  TEST_ASSERT_EQUAL_INT(TRUE, c_is_palindrom("@aa@"));
}

void test_c_is_palindrom_when_input_string_correct_palindrom_with_escape_sqn_char(
    void) {
  TEST_ASSERT_EQUAL_INT(TRUE, c_is_palindrom("\tbb\t"));
}

// c_is_palindrom edge cases

void test_c_is_palindrom_when_string_empty(void) {
  TEST_ASSERT_EQUAL_INT(FALSE, c_is_palindrom(""));
}

// c_is_palindrom negative tests

void test_c_is_palindrom_when_input_null(void) {
  c_is_palindrom(NULL);
  TEST_PASS();
}

// -----------------------------------

// ----------c_is_string_of_digits----------

// c_is_string_of_digits valid input data

void test_c_is_string_of_digits_when_input_string_all_digits(void) {
  TEST_ASSERT_EQUAL_INT(TRUE, c_is_string_of_digits("123456"));
}

void test_c_is_string_of_digits_when_input_string_has_letter_and_digits(void) {
  TEST_ASSERT_EQUAL_INT(FALSE, c_is_string_of_digits("12b"));
}

void test_c_is_string_of_digits_when_string_has_not_digits(void) {
  TEST_ASSERT_EQUAL_INT(FALSE, c_is_string_of_digits("abc"));
}

void test_c_is_string_of_digits_when_input_string_all_digits_and_end_symbol_in_middle(
    void) {
  TEST_ASSERT_EQUAL_INT(TRUE, c_is_string_of_digits("12\0a12"));
}

// c_is_string_of_digits edge cases

void test_c_is_string_of_digits_when_string_empty(void) {
  TEST_ASSERT_EQUAL_INT(FALSE, c_is_string_of_digits(""));
}

// c_is_string_of_digits negative cases

void test_c_is_string_of_digits_when_string_null(void) {
  c_is_string_of_digits(NULL);
  TEST_PASS();
}

// -----------------------------------------

// ----------c_is_punct_char----------

// c_is_punct_char valid input data

void test_c_is_punct_char_when_input_is_punct_char(void) {
  TEST_ASSERT_EQUAL_INT(TRUE, c_is_punct_char('&'));
}

void test_c_is_punct_char_when_input_is_letter(void) {
  TEST_ASSERT_EQUAL_INT(FALSE, c_is_punct_char('b'));
}

void test_c_is_punct_char_when_input_end_symbol(void) {
  TEST_ASSERT_EQUAL_INT(FALSE, c_is_punct_char('\0'));
}

void test_c_is_punct_char_when_input_int_code_of_punct_char(void) {
  TEST_ASSERT_EQUAL_INT(TRUE, c_is_punct_char(33));
}

void test_c_is_punct_char_when_input_int_code_of_not_punct_char(void) {
  TEST_ASSERT_EQUAL_INT(FALSE, c_is_punct_char(12));
}

// -----------------------------------

// ----------c_is_letter----------

// c_is_letter valid input data

void test_c_is_letter_when_input_is_letter(void) {
  TEST_ASSERT_EQUAL_INT(TRUE, c_is_letter('b'));
}

void test_c_is_letter_when_input_is_digit(void) {
  TEST_ASSERT_EQUAL_INT(FALSE, c_is_letter('1'));
}

void test_c_is_letter_when_input_is_punct_char(void) {
  TEST_ASSERT_EQUAL_INT(FALSE, c_is_letter('@'));
}

void test_c_is_letter_when_input_is_int_code_of_punct_char(void) {
  TEST_ASSERT_EQUAL_INT(FALSE, c_is_letter(93));
}

// -------------------------------

// ----------c_is_digit----------

// c_is_digit valid input data

void test_c_is_digit_when_input_is_digit(void) {
  TEST_ASSERT_EQUAL_INT(TRUE, c_is_digit('3'));
}

void test_c_is_digit_when_input_is_letter(void) {
  TEST_ASSERT_EQUAL_INT(FALSE, c_is_digit('a'));
}

void test_c_is_digit_when_input_is_punct_char(void) {
  TEST_ASSERT_EQUAL_INT(FALSE, c_is_digit('.'));
}

void test_c_is_digit_when_input_is_int_code_of_letter(void) {
  TEST_ASSERT_EQUAL_INT(FALSE, c_is_digit(97));
}

// ------------------------------

// ----------c_is_space----------

// c_is_space valid input data

void test_c_is_space_when_input_is_space(void) {
  TEST_ASSERT_EQUAL_INT(TRUE, c_is_space(' '));
}

void test_c_is_space_when_input_is_letter(void) {
  TEST_ASSERT_EQUAL_INT(FALSE, c_is_space('b'));
}

void test_c_is_space_when_input_int_code_letter(void) {
  TEST_ASSERT_EQUAL_INT(FALSE, c_is_space(87));
}

// ------------------------------

// ----------c_is_empty_string----------

// c_is_empty_string valid input data

void test_c_is_empty_string_when_input_is_empty_string(void) {
  TEST_ASSERT_EQUAL_INT(TRUE, c_is_empty_string(""));
}

void test_c_is_empty_string_when_input_is_string(void) {
  TEST_ASSERT_EQUAL_INT(FALSE, c_is_empty_string("string"));
}

void test_c_is_empty_string_when_input_string_with_2_end_symbols(void) {
  TEST_ASSERT_EQUAL_INT(TRUE, c_is_empty_string("\0"));
}

// c_is_empty_string negative tests

void test_c_is_empty_string_when_null(void) {
  TEST_ASSERT_EQUAL_INT(FALSE, c_is_empty_string(NULL));
}

//------------------------------------

// ----------c_is_char_in_string----------

// c_is_char_in_string valid input data

void test_c_index_of_char_when_char_in_string(void) {
  TEST_ASSERT_EQUAL_INT(2, c_index_of_char("abc", 'c'));
}

void test_c_index_of_char_when_char_is_not_in_string(void) {
  TEST_ASSERT_EQUAL_INT(-1, c_index_of_char("string", 'h'));
}

void test_c_index_of_char_when_look_for_end_symbol_in_the_middle(void) {
  TEST_ASSERT_EQUAL_INT(-1, c_index_of_char("ab\0cd", '\0'));
}

void test_c_index_of_char_when_look_end_symbol(void) {
  TEST_ASSERT_EQUAL_INT(-1, c_index_of_char("abc", '\0'));
}

// c_is_empty_string negative tests

void test_c_index_of_char_when_string_is_null(void) {
  TEST_ASSERT_EQUAL_INT(-1, c_index_of_char(NULL, 'o'));
}

//------------------------------------

// ----------c_is_anagrams----------

// c_is_anagrams valid input data

void test_c_is_anagrams_when_input_strings_are_anagrams(void) {
  TEST_ASSERT_EQUAL_INT(TRUE, c_is_anagrams("abc", "cba"));
}

void test_c_is_anagrams_when_input_strings_are_anagrams_with_uppercases(void) {
  TEST_ASSERT_EQUAL_INT(FALSE, c_is_anagrams("AAc", "acc"));
}

void test_c_is_anagrams_when_input_strings_are_single_letter_and_anagrams(
    void) {
  TEST_ASSERT_EQUAL_INT(TRUE, c_is_anagrams("a", "a"));
}

void test_c_is_anagrams_when_input_strs_are_single_letter_and_anagrams_with_uppercase(
    void) {
  TEST_ASSERT_EQUAL_INT(TRUE, c_is_anagrams("A", "a"));
}

// c_is_anagrams edge cases

void test_c_is_anagrams_when_first_string_is_empty(void) {
  TEST_ASSERT_EQUAL_INT(FALSE, c_is_anagrams("", "cBa"));
}

void test_c_is_anagrams_when_second_string_is_empty(void) {
  TEST_ASSERT_EQUAL_INT(FALSE, c_is_anagrams("abv", ""));
}

// c_is_anagrams nagative tests

void test_c_is_anagrams_when_first_string_null(void) {
  TEST_ASSERT_EQUAL_INT(FALSE, c_is_anagrams(NULL, "cBa"));
}

void test_c_is_anagrams_when_second_string_null(void) {
  TEST_ASSERT_EQUAL_INT(FALSE, c_is_anagrams("abv", NULL));
}

// ---------------------------------

// ----------c_is_upper_letter----------

// c_is_upper_letter valid input data

void test_c_is_upper_letter_when_input_is_upper_letter(void) {
  TEST_ASSERT_EQUAL_INT(TRUE, c_is_upper_letter('A'));
}

void test_c_is_upper_letter_when_input_is_lower_letter(void) {
  TEST_ASSERT_EQUAL_INT(FALSE, c_is_upper_letter('a'));
}

void test_c_is_upper_letter_when_input_is_punct_char(void) {
  TEST_ASSERT_EQUAL_INT(FALSE, c_is_upper_letter('@'));
}

// -------------------------------------

// ----------c_is_lower_letter----------

// c_is_lower_letter valid input data

void test_c_is_lower_letter_when_input_is_lower_letter(void) {
  TEST_ASSERT_EQUAL_INT(TRUE, c_is_lower_letter('a'));
}

void test_c_is_lower_letter_when_input_is_upper_letter(void) {
  TEST_ASSERT_EQUAL_INT(FALSE, c_is_lower_letter('A'));
}

void test_c_is_lower_letter_when_input_is_punct_char(void) {
  TEST_ASSERT_EQUAL_INT(FALSE, c_is_lower_letter('@'));
}

// -------------------------------------

// ----------c_letter_to_lower----------

// c_letter_to_lower valid input data

void test_c_letter_to_lower_when_input_is_upper_letter(void) {
  TEST_ASSERT_EQUAL_INT('a', c_letter_to_lower('A'));
}

void test_c_letter_to_lower_when_input_is_lower_letter(void) {
  TEST_ASSERT_EQUAL_INT('b', c_letter_to_lower('b'));
}

void test_c_letter_to_lower_when_input_is_punct_char(void) {
  TEST_ASSERT_EQUAL_INT('!', c_letter_to_lower('!'));
}

// -------------------------------------

// ----------c_letter_to_upper----------

// c_letter_to_upper valid input data

void test_c_letter_to_upper_when_input_is_lower_letter(void) {
  TEST_ASSERT_EQUAL_INT('A', c_letter_to_upper('a'));
}

void test_c_letter_to_upper_when_input_is_upper_letter(void) {
  TEST_ASSERT_EQUAL_INT('A', c_letter_to_upper('A'));
}

void test_c_letter_to_upper_when_input_is_punct_char(void) {
  TEST_ASSERT_EQUAL_INT('#', c_letter_to_upper('#'));
}

// -------------------------------------

// ----------c_str_to_lower----------

// c_str_to_lower valid input data

void test_c_str_to_lower_when_input_string_uppercase(void) {
  char str[] = "ABCD";
  c_str_to_lower(str);
  TEST_ASSERT_EQUAL_STRING("abcd", str);
}

void test_c_str_to_lower_when_input_string_lowercase(void) {
  char str[] = "abcd";
  c_str_to_lower(str);
  TEST_ASSERT_EQUAL_STRING("abcd", str);
}

void test_c_str_to_lower_when_string_has_lowercase_and_uppercase(void) {
  char str[] = "aBcD";
  c_str_to_lower(str);
  TEST_ASSERT_EQUAL_STRING("abcd", str);
}

// c_str_to_lower edge cases

void test_c_str_to_lower_when_string_empty(void) {
  char str[] = "";
  c_str_to_lower(str);
  TEST_ASSERT_EQUAL_STRING("", str);
}

// c_str_to_lower negative tests

void test_c_str_to_lower_when_string_null(void) {
  c_str_to_lower(NULL);
  TEST_PASS();
}

// -------------------------------------

// ----------c_str_to_upper----------

// c_str_to_upper valid input data

void test_c_str_to_upper_when_input_string_lowercase(void) {
  char str[] = "abcd";
  c_str_to_upper(str);
  TEST_ASSERT_EQUAL_STRING("ABCD", str);
}

void test_c_str_to_upper_when_input_string_uppercase(void) {
  char str[] = "ABCD";
  c_str_to_upper(str);
  TEST_ASSERT_EQUAL_STRING("ABCD", str);
}

void test_c_str_to_upper_when_input_string_has_uppercase_and_lowercase(void) {
  char str[] = "aBcD";
  c_str_to_upper(str);
  TEST_ASSERT_EQUAL_STRING("ABCD", str);
}

// c_str_to_upper edge cases

void test_c_str_to_upper_when_string_empty(void) {
  char str[] = "";
  c_str_to_upper(str);
  TEST_ASSERT_EQUAL_STRING("", str);
}

// c_str_to_upper negative tests

void test_c_str_to_upper_when_string_null(void) {
  c_str_to_upper(NULL);
  TEST_PASS();
}

// -------------------------------------

// ----------c_delete_spaces----------

// c_delete_spaces valid input data

void test_c_delete_spaces_when_input_string_has_spaces(void) {
  char s[] = " abc  abc def ";
  TEST_ASSERT_EQUAL_INT(5, c_delete_spaces(s));
}

void test_c_delete_spaces_when_input_string_has_no_spaces(void) {
  char s[] = "abc";
  TEST_ASSERT_EQUAL_INT(0, c_delete_spaces(s));
}

// c_delete_spaces edge cases

void test_c_delete_spaces_when_string_empty(void) {
  char s[] = "";
  TEST_ASSERT_EQUAL_INT(0, c_delete_spaces(s));
}

// c_str_to_lower negative tests

void test_c_delete_spaces_when_string_null(void) {
  TEST_ASSERT_EQUAL_INT(-1, c_delete_spaces(NULL));
}

// -------------------------------------

// ----------c_invert_symbols----------

// c_invert_symbols valid input data

void test_c_invert_symbols_when_string_has_only_lowercase(void) {
  char s[] = "string";
  c_invert_symbols(s);
  TEST_ASSERT_EQUAL_STRING("STRING", s);
}

void test_c_invert_symbols_when_string_has_only_uppercase(void) {
  char s[] = "STRING";
  c_invert_symbols(s);
  TEST_ASSERT_EQUAL_STRING("string", s);
}

void test_c_invert_symbols_when_string_has_upper_and_lowercases(void) {
  char s[] = "StRiNG";
  c_invert_symbols(s);
  TEST_ASSERT_EQUAL_STRING("sTrIng", s);
}

void test_c_invert_symbols_when_string_has_punct_chars(void) {
  char s[] = "String!#";
  c_invert_symbols(s);
  TEST_ASSERT_EQUAL_STRING("sTRING!#", s);
}

// c_delete_spaces edge cases

void test_c_invert_symbols_when_string_empty(void) {
  char s[] = "";
  c_invert_symbols(s);
  TEST_ASSERT_EQUAL_STRING("", s);
}

// c_delete_spaces negative tests

void test_c_invert_symbols_when_string_null(void) {
  c_delete_spaces(NULL);
  TEST_PASS();
}

// -------------------------------------

// ----------c_reverse----------

// c_reverse valid input data

void test_c_reverse_when_string_single_lowercase_word(void) {
  char s[] = "string";
  c_reverse(s);
  TEST_ASSERT_EQUAL_STRING("gnirts", s);
}

void test_c_reverse_when_string_single_uppercase_word(void) {
  char s[] = "STRING";
  c_reverse(s);
  TEST_ASSERT_EQUAL_STRING("GNIRTS", s);
}

void test_c_reverse_when_string_single_lower_and_uppercase_word(void) {
  char s[] = "AbCd";
  c_reverse(s);
  TEST_ASSERT_EQUAL_STRING("dCbA", s);
}

void test_c_reverse_when_string_is_sentence(void) {
  char s[] = "Hello World!";
  c_reverse(s);
  TEST_ASSERT_EQUAL_STRING("!dlroW olleH", s);
}

// c_reverse edge cases

void test_c_reverse_when_string_is_empty(void) {
  char s[] = "";
  c_reverse(s);
  TEST_ASSERT_EQUAL_STRING("", s);
}

// c_reverse negative tests

void test_c_reverse_when_string_null(void) {
  c_reverse(NULL);
  TEST_PASS();
}

// -----------------------------

// ----------c_delete_punctuation----------

void test_c_delete_punctuation_when_string_has_punct_chars(void) {
  char s[] = "ab c!#";
  c_delete_punctuation(s);
  TEST_ASSERT_EQUAL_STRING("ab c", s);
}

void test_c_delete_punctuation_when_string_has_no_punct_chars(void) {
  char s[] = "abc";
  c_delete_punctuation(s);
  TEST_ASSERT_EQUAL_STRING("abc", s);
}

// c_delete_punctuation edge cases

void test_c_delete_punctuation_when_string_empty(void) {
  char s[] = "";
  c_delete_punctuation(s);
  TEST_ASSERT_EQUAL_STRING("", s);
}

// c_delete_punctuation nagative tests

void test_c_delete_punctuation_when_string_null(void) {
  TEST_ASSERT_EQUAL_INT(-1, c_delete_punctuation(NULL));
}

// ----------------------------------------

// ----------c_change_char_all----------

// c_change_char_all valid input data

void test_c_change_char_all_when_change_letter_to_letter(void) {
  char s[] = "baacdefaa";
  c_change_char_all(s, 'a', 'm');
  TEST_ASSERT_EQUAL_STRING("bmmcdefmm", s);
}

void test_c_change_char_all_when_change_punct_char_to_letter(void) {
  char s[] = "__ac_ef__";
  c_change_char_all(s, '_', 'v');
  TEST_ASSERT_EQUAL_STRING("vvacvefvv", s);
}

void test_c_change_char_all_when_from_char_do_not_in_string(void) {
  char s[] = "ae";
  c_change_char_all(s, 'm', 'v');
  TEST_ASSERT_EQUAL_STRING("ae", s);
}

// c_change_char_all edge cases

void test_c_change_char_all_when_string_empty(void) {
  char s[] = "";
  c_change_char_all(s, 'a', 'b');
  TEST_ASSERT_EQUAL_STRING("", s);
}

void test_c_change_char_all_when_from_char_is_end_symbol(void) {
  char s[] = "acrf";
  c_change_char_all(s, '\0', 'm');
  TEST_ASSERT_EQUAL_STRING("acrf", s);
}

// c_change_char_all negative tests

void test_c_change_char_all_when_string_null(void) {
  c_change_char_all(NULL, 'a', 'b');
  TEST_PASS();
}

// -------------------------------------

// ---------c_delete_duplicates--------

// c_delete_duplicates valid input data

void test_c_delete_duplicates_when_string_has_duplicates(void) {
  char s[] = "aabbccdd";
  c_delete_duplicates(s);
  TEST_ASSERT_EQUAL_STRING("abcd", s);
}

void test_c_delete_duplicates_when_string_has_no_duplicates(void) {
  char s[] = "ab cd";
  c_delete_duplicates(s);
  TEST_ASSERT_EQUAL_STRING("ab cd", s);
}

// c_delete_duplicates edge cases

void test_c_delete_duplicates_when_string_empty(void) {
  char s[] = "";
  c_delete_duplicates(s);
  TEST_ASSERT_EQUAL_STRING("", s);
}

// c_delete_duplicates negative test

void test_c_delete_duplicates_when_string_null(void) {
  c_delete_duplicates(NULL);
  TEST_PASS();
}

// ------------------------------------

// ----------c_strcpy----------

void test_c_strcpy_when_copy_from_correct_string(void) {
  char buff[10] = {'\0'};
  TEST_ASSERT_EQUAL_STRING("hello", c_strcpy(buff, "hello"));
}

void test_c_strcpy_when_from_empty_string(void) {
  char buff[1] = {'A'};
  TEST_ASSERT_EQUAL_STRING("", c_strcpy(buff, ""));
}

void test_c_strcpy_when_dest_and_from_equal(void) {
  char buff[] = "string";
  TEST_ASSERT_EQUAL_STRING("string", c_strcpy(buff, "string"));
}

void test_c_strcpy_when_dest_string_null(void) {
  TEST_ASSERT_NULL(c_strcpy(NULL, "string"));
}

void test_c_strcpy_when_from_string_null(void) {
  TEST_ASSERT_EQUAL_STRING("string", c_strcpy("string", NULL));
}

// ----------------------------

// ----------c_sort_chars----------

void test_c_sort_chars_when_letters_in_reverse_alphabetical_order(void) {
  char s[] = "fedcba";
  c_sort_chars(s);
  TEST_ASSERT_EQUAL_STRING("abcdef", s);
}

void test_c_sort_chars_when_letters_already_in_alphabetical_order(void) {
  char s[] = "abcdef";
  c_sort_chars(s);
  TEST_ASSERT_EQUAL_STRING("abcdef", s);
}

void test_c_sort_chars_when_string_empty(void) {
  char s[] = "";
  c_sort_chars(s);
  TEST_ASSERT_EQUAL_STRING("", s);
}

void test_c_sort_chars_when_string_null(void) {
  c_sort_chars(NULL);
  TEST_PASS();
}

// --------------------------------

// ----------c_strcat----------

// c_strcat valid input data

void test_c_strcat_when_dest_size_enough_for_cat(void) {
  char s[9] = {'a', 'b', 'c', '\0'};
  TEST_ASSERT_EQUAL_STRING("abcdef", c_strcat(s, "def", 9));
}

void test_c_strcat_when_from_len_plus_dest_len_equal_dest_size(void) {
  char s[8] = {'a', 'b', 'c', '\0'};
  TEST_ASSERT_EQUAL_STRING("abcdefg", c_strcat(s, "defg", 8));
}

void test_c_strcat_when_from_string_empty(void) {
  char s[] = "abc";
  TEST_ASSERT_EQUAL_STRING("abc", c_strcat(s, "", 4));
}

void test_c_strcat_when_dest_string_empty(void) {
  char s[] = "";
  TEST_ASSERT_EQUAL_STRING("", c_strcat(s, "abc", 1));
}

void test_c_strcat_when_dest_string_null(void) {
  TEST_ASSERT_NULL(c_strcat(NULL, "abc", 5));
}

void test_c_strcat_when_from_string_null(void) {
  char s[] = "abc";
  TEST_ASSERT_NULL(c_strcat(s, NULL, 4));
}

// ----------------------------

// ----------c_trim----------

void test_c_trim_when_string_has_start_and_end_spaces(void) {
  char s[] = "   abc   ";
  TEST_ASSERT_EQUAL_STRING("abc", c_trim(s));
}

void test_c_trim_when_string_has_start_and_end_tabs(void) {
  char s[] = "\tabc\t\t";
  TEST_ASSERT_EQUAL_STRING("abc", c_trim(s));
}

void test_c_trim_when_string_has_start_end_and_middle_space(void) {
  char s[] = "  a bc   ";
  TEST_ASSERT_EQUAL_STRING("a bc", c_trim(s));
}

void test_c_trim_when_string_has_start_end_and_middle_tabs(void) {
  char s[] = "\tab\tc\t\t";
  TEST_ASSERT_EQUAL_STRING("ab\tc", c_trim(s));
}

void test_c_trim_when_string_empty(void) {
  char s[] = "";
  TEST_ASSERT_EQUAL_STRING("", c_trim(s));
}

void test_c_trim_when_string_null(void) {
  char s[] = "\tabc\t\t";
  TEST_ASSERT_EQUAL_STRING("abc", c_trim(s));
}

// --------------------------

// ----------c_detab----------

// c_detab valid input data

void test_c_detab_when_string_has_tabs_and_size_enough_for_spaces(void) {
  char s[10] = {'\t', 'a', 'b', '\t', '\0'};
  TEST_ASSERT_EQUAL_STRING("  ab  ", c_detab(s, 2, 10));
}

void test_c_detab_when_string_size_not_enough(void) {
  char s[10] = {'\t', 'a', 'a', '\t', '\0'};
  TEST_ASSERT_EQUAL_STRING(s, c_detab(s, 5, 10));
}

void test_c_detab_when_detab_string_len_equal_buff_size(void) {
  char s[10] = {'\t', 'a', 'a', '\t', '\0'};
  TEST_ASSERT_EQUAL_STRING(s, c_detab(s, 4, 10));
}

void test_c_detab_when_detab_string_size_equal_buff_size(void) {
  char s[11] = {'\t', 'a', 'a', '\t', '\0'};
  TEST_ASSERT_EQUAL_STRING("    aa    ", c_detab(s, 4, 11));
}

void test_c_detab_when_string_empty(void) {
  char s[] = "";
  TEST_ASSERT_EQUAL_STRING("", c_detab(s, 5, 1));
}

void test_c_detab_when_string_null(void) {
  TEST_ASSERT_NULL(c_detab(NULL, 5, 10));
}

// ---------------------------

// ----------c_entab----------

void test_c_entab_when_set_two_tabs(void) {
  char s[] = "    a    ";
  TEST_ASSERT_EQUAL_STRING("\ta\t", c_entab(s, 4, 10));
}

void test_c_entab_when_set_one_tab_in_begin(void) {
  char s[] = "    a";
  TEST_ASSERT_EQUAL_STRING("\ta", c_entab(s, 4, 6));
}

void test_c_entab_when_set_one_tab_in_end(void) {
  char s[] = "a    ";
  TEST_ASSERT_EQUAL_STRING("a\t", c_entab(s, 4, 6));
}

void test_c_entab_when_not_enough_spaces(void) {
  char s[] = "a  ";
  TEST_ASSERT_EQUAL_STRING("a  ", c_entab(s, 4, 4));
}

void test_c_entab_when_string_empty(void) {
  char s[] = "";
  TEST_ASSERT_EQUAL_STRING("", c_entab(s, 4, 10));
}

void test_c_entab_when_string_null(void) {
  TEST_ASSERT_NULL(c_entab(NULL, 5, 5));
}

// ---------------------------

// ----------c_overwrite_from-----------

void test_c_overwrite_from_when_string_has_enough_space_for_substr(void) {
  char s[] = "string";
  TEST_ASSERT_EQUAL_STRING("swwwwg", c_overwrite_from(s, "wwww", 1, 7));
}

void test_c_overwrite_from_when_string_has_no_space_for_substr(void) {
  char s[] = "string";
  TEST_ASSERT_EQUAL_STRING("string", c_overwrite_from(s, "oooong", 3, 7));
}

void test_c_overwrite_from_when_insert_substr_in_end_of_str(void) {
  char s[] = "string";
  TEST_ASSERT_EQUAL_STRING("strivv", c_overwrite_from(s, "vv", 4, 7));
}

void test_c_overwrite_from_when_substr_empty(void) {
  char s[] = "string";
  TEST_ASSERT_EQUAL_STRING("string", c_overwrite_from(s, "", 0, 7));
}

void test_c_overwrite_from_when_string_empty(void) {
  char s[] = "";
  TEST_ASSERT_EQUAL_STRING("", c_overwrite_from(s, "aaa", 0, 7));
}

void test_c_overwrite_from_when_substr_null(void) {
  char s[] = "string";
  TEST_ASSERT_EQUAL_STRING("string", c_overwrite_from(s, NULL, 1, 10));
}

void test_c_overwrite_from_when_string_null(void) {
  TEST_ASSERT_NULL(c_overwrite_from(NULL, "str", 1, 10));
}

// -------------------------------------

int main(void) {

  UnityBegin("c_string.c");

  TEST_BLOCK_START_HEADER("c_strlen");
  RUN_TEST(test_c_strlen_when_given_single_word);
  RUN_TEST(test_c_strlen_when_string_has_spaces);
  RUN_TEST(test_c_strlen_when_string_has_end_symbol_in_middle);
  RUN_TEST(test_c_strlen_when_string_has_tabs);
  RUN_TEST(test_c_strlen_when_input_null);
  RUN_TEST(test_c_strlen_when_string_empty);
  TEST_BLOCK_END_HEADER("c_strlen");

  TEST_BLOCK_START_HEADER("c_strcmp");
  RUN_TEST(test_c_strcmp_when_strings_equal);
  RUN_TEST(test_c_strcmp_when_second_str_greater);
  RUN_TEST(test_c_strcmp_when_first_str_greater);
  RUN_TEST(test_c_strcmp_when_strs_equal_and_uppercase);
  RUN_TEST(test_c_strcmp_when_second_start_with_uppercase_first_with_lowercase);
  RUN_TEST(test_c_strcmp_when_first_start_with_uppercase_second_with_lowercase);
  RUN_TEST(test_c_strcmp_when_both_empty);
  RUN_TEST(test_c_strcmp_when_first_str_empty);
  RUN_TEST(test_c_strcmp_when_second_str_empty);
  RUN_TEST(test_c_strcmp_when_first_string_have_non_letter_char);
  RUN_TEST(test_c_strcmp_when_second_string_have_non_letter_char);
  RUN_TEST(test_c_strcmp_when_both_have_non_letter_char);
  RUN_TEST(test_c_strcmp_when_first_have_escape_char);
  RUN_TEST(test_c_strcmp_when_second_have_escape_char);
  TEST_BLOCK_END_HEADER("c_strcmp");

  TEST_BLOCK_START_HEADER("c_remove_digits");
  RUN_TEST(test_c_remove_digits_when_str_have_1_digit);
  RUN_TEST(test_c_remove_digits_when_str_have_4_digits);
  RUN_TEST(test_c_remove_digits_when_str_have_all_digits);
  RUN_TEST(test_c_remove_digits_when_str_have_no_digits);
  RUN_TEST(test_c_remove_digits_when_str_empty);
  RUN_TEST(test_c_remove_digits_when_str_have_end_symbol_in_middle);
  RUN_TEST(test_c_remove_digits_when_str_is_null);
  TEST_BLOCK_END_HEADER("c_remove_digits");

  TEST_BLOCK_START_HEADER("c_count_words");
  RUN_TEST(test_c_count_words_when_single_word);
  RUN_TEST(test_c_count_words_when_string_has_10_words);
  RUN_TEST(test_c_count_words_when_delim_is_punct_char);
  RUN_TEST(test_c_count_words_when_string_empty);
  RUN_TEST(test_c_count_words_when_str_is_only_spaces);
  RUN_TEST(test_c_count_words_when_delim_is_tab);
  RUN_TEST(test_c_count_words_when_string_has_extra_spaces_and_tabs);
  RUN_TEST(test_c_count_words_when_input_null);
  TEST_BLOCK_END_HEADER("c_count_words");

  TEST_BLOCK_START_HEADER("c_first_unique_char");
  RUN_TEST(test_c_first_unique_char_when_single_word);
  RUN_TEST(test_c_first_unique_char_when_string_is_paired_letters);
  RUN_TEST(test_c_first_unique_char_when_string_has_non_letter);
  RUN_TEST(test_c_first_unique_char_when_string_empty);
  RUN_TEST(test_c_first_unique_char_when_string_is_single_space);
  RUN_TEST(test_c_first_unique_char_when_string_is_all_spaces);
  RUN_TEST(test_c_first_unique_char_when_string_has_escape_sequence_char);
  RUN_TEST(test_c_first_unique_char_when_string_is_null);
  TEST_BLOCK_END_HEADER("c_first_unique_char");

  TEST_BLOCK_START_HEADER("c_strstr");
  RUN_TEST(test_c_strstr_when_substr_in_str);
  RUN_TEST(test_c_strstr_when_substr_in_str_both_have_uppercase_letter);
  RUN_TEST(test_c_strstr_when_substr_in_str_both_have_non_letter_char);
  RUN_TEST(test_c_strstr_when_str_empty_substr_not);
  RUN_TEST(test_c_strstr_when_substr_empty_str_not);
  RUN_TEST(test_c_strstr_when_both_empty);
  RUN_TEST(test_c_strstr_when_str_is_null);
  RUN_TEST(test_c_strstr_when_substr_is_null);
  TEST_BLOCK_END_HEADER("c_strstr");

  TEST_BLOCK_START_HEADER("c_num_substr");
  RUN_TEST(test_c_num_substr_when_one_substr_in_end_string);
  RUN_TEST(test_c_num_substr_when_substr_is_string);
  RUN_TEST(test_c_num_substr_when_substr_not_in_string);
  RUN_TEST(test_c_num_substr_when_string_has_two_substr);
  RUN_TEST(test_c_num_substr_when_substr_empty_string_not);
  RUN_TEST(test_c_num_substr_when_string_empty_substr_not);
  RUN_TEST(test_c_num_substr_when_both_empty);
  RUN_TEST(test_c_num_substr_when_string_is_null);
  RUN_TEST(test_c_num_substr_when_substr_is_null);
  TEST_BLOCK_END_HEADER("c_num_substr");

  TEST_BLOCK_START_HEADER("c_atoi");
  RUN_TEST(test_c_atoi_when_input_string_is_correct_number);
  RUN_TEST(test_c_atoi_when_input_string_is_correct_negative_number);
  RUN_TEST(
      test_c_atoi_when_input_str_is_correct_negative_num_with_leading_zeroes);
  RUN_TEST(test_c_atoi_when_input_str_is_correct_num_with_leading_zeroes);
  RUN_TEST(test_c_atoi_when_string_has_not_number_char_in_middle);
  RUN_TEST(test_c_atoi_when_string_has_not_number_char_in_middle_negative_num);
  RUN_TEST(test_c_atoi_when_first_char_is_letter);
  RUN_TEST(test_c_atoi_when_first_char_is_minus_second_letter);
  // RUN_TEST(test_c_atoi_when_input_string_empty);
  // RUN_TEST(test_c_atoi_when_input_is_null);
  TEST_BLOCK_END_HEADER("c_atoi");

  TEST_BLOCK_START_HEADER("c_is_palindrom");
  RUN_TEST(test_c_is_palindrom_when_input_string_correct_palindrom);
  RUN_TEST(test_c_is_palindrom_when_string_is_single_char);
  RUN_TEST(test_c_is_palindrom_when_string_not_palindrom);
  RUN_TEST(test_c_is_palindrom_when_string_has_end_string_char_in_middle);
  RUN_TEST(
      test_c_is_palindrom_when_input_string_correct_palindrom_with_punct_chars);
  RUN_TEST(
      test_c_is_palindrom_when_input_string_correct_palindrom_with_escape_sqn_char);
  RUN_TEST(test_c_is_palindrom_when_string_empty);
  RUN_TEST(test_c_is_palindrom_when_input_null);
  TEST_BLOCK_END_HEADER("c_is_palindrom");

  TEST_BLOCK_START_HEADER("c_is_string_of_digits");
  RUN_TEST(test_c_is_string_of_digits_when_input_string_all_digits);
  RUN_TEST(test_c_is_string_of_digits_when_input_string_has_letter_and_digits);
  RUN_TEST(test_c_is_string_of_digits_when_string_has_not_digits);
  RUN_TEST(
      test_c_is_string_of_digits_when_input_string_all_digits_and_end_symbol_in_middle);
  RUN_TEST(test_c_is_string_of_digits_when_string_empty);
  RUN_TEST(test_c_is_string_of_digits_when_string_null);
  TEST_BLOCK_END_HEADER("c_is_string_of_digits");

  TEST_BLOCK_START_HEADER("c_is_punct_char");
  RUN_TEST(test_c_is_punct_char_when_input_is_punct_char);
  RUN_TEST(test_c_is_punct_char_when_input_is_letter);
  RUN_TEST(test_c_is_punct_char_when_input_end_symbol);
  RUN_TEST(test_c_is_punct_char_when_input_int_code_of_punct_char);
  RUN_TEST(test_c_is_punct_char_when_input_int_code_of_not_punct_char);
  TEST_BLOCK_END_HEADER("c_is_punct_char");

  TEST_BLOCK_START_HEADER("c_is_letter");
  RUN_TEST(test_c_is_letter_when_input_is_letter);
  RUN_TEST(test_c_is_letter_when_input_is_digit);
  RUN_TEST(test_c_is_letter_when_input_is_punct_char);
  RUN_TEST(test_c_is_letter_when_input_is_int_code_of_punct_char);
  TEST_BLOCK_END_HEADER("c_is_letter");

  TEST_BLOCK_START_HEADER("c_is_digit");
  RUN_TEST(test_c_is_digit_when_input_is_digit);
  RUN_TEST(test_c_is_digit_when_input_is_letter);
  RUN_TEST(test_c_is_digit_when_input_is_punct_char);
  RUN_TEST(test_c_is_digit_when_input_is_int_code_of_letter);
  TEST_BLOCK_END_HEADER("c_is_digit");

  TEST_BLOCK_START_HEADER("c_is_space");
  RUN_TEST(test_c_is_space_when_input_is_space);
  RUN_TEST(test_c_is_space_when_input_is_letter);
  RUN_TEST(test_c_is_space_when_input_int_code_letter);
  TEST_BLOCK_END_HEADER("c_is_space");

  TEST_BLOCK_START_HEADER("c_is_empty_string");
  RUN_TEST(test_c_is_empty_string_when_input_is_empty_string);
  RUN_TEST(test_c_is_empty_string_when_input_is_string);
  RUN_TEST(test_c_is_empty_string_when_input_string_with_2_end_symbols);
  RUN_TEST(test_c_is_empty_string_when_null);
  TEST_BLOCK_END_HEADER("c_is_empty_string");

  TEST_BLOCK_START_HEADER("c_index_of_char");
  RUN_TEST(test_c_index_of_char_when_char_in_string);
  RUN_TEST(test_c_index_of_char_when_char_is_not_in_string);
  RUN_TEST(test_c_index_of_char_when_look_for_end_symbol_in_the_middle);
  RUN_TEST(test_c_index_of_char_when_look_end_symbol);
  RUN_TEST(test_c_index_of_char_when_string_is_null);
  TEST_BLOCK_END_HEADER("c_index_of_char");

  TEST_BLOCK_START_HEADER("c_is_anagrams");
  RUN_TEST(test_c_is_anagrams_when_input_strings_are_anagrams);
  RUN_TEST(test_c_is_anagrams_when_input_strings_are_anagrams_with_uppercases);
  RUN_TEST(
      test_c_is_anagrams_when_input_strings_are_single_letter_and_anagrams);
  RUN_TEST(
      test_c_is_anagrams_when_input_strs_are_single_letter_and_anagrams_with_uppercase);
  RUN_TEST(test_c_is_anagrams_when_first_string_is_empty);
  RUN_TEST(test_c_is_anagrams_when_second_string_is_empty);
  RUN_TEST(test_c_is_anagrams_when_first_string_null);
  RUN_TEST(test_c_is_anagrams_when_second_string_null);
  TEST_BLOCK_END_HEADER("c_is_anagrams");

  TEST_BLOCK_START_HEADER("c_is_upper_letter");
  RUN_TEST(test_c_is_upper_letter_when_input_is_upper_letter);
  RUN_TEST(test_c_is_upper_letter_when_input_is_lower_letter);
  RUN_TEST(test_c_is_upper_letter_when_input_is_punct_char);
  TEST_BLOCK_END_HEADER("c_is_upper_letter");

  TEST_BLOCK_START_HEADER("c_is_lower_letter");
  RUN_TEST(test_c_is_lower_letter_when_input_is_lower_letter);
  RUN_TEST(test_c_is_lower_letter_when_input_is_upper_letter);
  RUN_TEST(test_c_is_lower_letter_when_input_is_punct_char);
  TEST_BLOCK_END_HEADER("c_is_lower_letter");

  TEST_BLOCK_START_HEADER("c_letter_to_lower");
  RUN_TEST(test_c_letter_to_lower_when_input_is_upper_letter);
  RUN_TEST(test_c_letter_to_lower_when_input_is_lower_letter);
  RUN_TEST(test_c_letter_to_lower_when_input_is_punct_char);
  TEST_BLOCK_END_HEADER("c_letter_to_lower");

  TEST_BLOCK_START_HEADER("c_letter_to_upper");
  RUN_TEST(test_c_letter_to_upper_when_input_is_upper_letter);
  RUN_TEST(test_c_letter_to_upper_when_input_is_lower_letter);
  RUN_TEST(test_c_letter_to_upper_when_input_is_punct_char);
  TEST_BLOCK_END_HEADER("c_lette_to_upper");

  TEST_BLOCK_START_HEADER("c_delete_spaces");
  RUN_TEST(test_c_delete_spaces_when_input_string_has_spaces);
  RUN_TEST(test_c_delete_spaces_when_input_string_has_no_spaces);
  RUN_TEST(test_c_delete_spaces_when_string_empty);
  RUN_TEST(test_c_delete_spaces_when_string_null);
  TEST_BLOCK_END_HEADER("c_delete_spaces");

  TEST_BLOCK_START_HEADER("c_str_to_lower");
  RUN_TEST(test_c_str_to_lower_when_input_string_uppercase);
  RUN_TEST(test_c_str_to_lower_when_input_string_lowercase);
  RUN_TEST(test_c_str_to_lower_when_string_has_lowercase_and_uppercase);
  RUN_TEST(test_c_str_to_lower_when_string_empty);
  RUN_TEST(test_c_str_to_lower_when_string_null);
  TEST_BLOCK_END_HEADER("c_str_to_lower");

  TEST_BLOCK_START_HEADER("c_str_to_upper");
  RUN_TEST(test_c_str_to_upper_when_input_string_uppercase);
  RUN_TEST(test_c_str_to_upper_when_input_string_lowercase);
  RUN_TEST(test_c_str_to_upper_when_input_string_has_uppercase_and_lowercase);
  RUN_TEST(test_c_str_to_upper_when_string_empty);
  RUN_TEST(test_c_str_to_upper_when_string_null);
  TEST_BLOCK_END_HEADER("c_str_to_upper");

  TEST_BLOCK_START_HEADER("c_invert_symbols");
  RUN_TEST(test_c_invert_symbols_when_string_has_only_lowercase);
  RUN_TEST(test_c_invert_symbols_when_string_has_only_uppercase);
  RUN_TEST(test_c_str_to_upper_when_input_string_has_uppercase_and_lowercase);
  RUN_TEST(test_c_invert_symbols_when_string_has_punct_chars);
  RUN_TEST(test_c_invert_symbols_when_string_empty);
  RUN_TEST(test_c_invert_symbols_when_string_null);
  TEST_BLOCK_END_HEADER("c_invert_symbols");

  TEST_BLOCK_START_HEADER("c_reverse");
  RUN_TEST(test_c_reverse_when_string_single_lowercase_word);
  RUN_TEST(test_c_reverse_when_string_single_uppercase_word);
  RUN_TEST(test_c_reverse_when_string_single_lower_and_uppercase_word);
  RUN_TEST(test_c_reverse_when_string_is_sentence);
  RUN_TEST(test_c_reverse_when_string_is_empty);
  RUN_TEST(test_c_reverse_when_string_null);
  TEST_BLOCK_END_HEADER("c_reverse");

  TEST_BLOCK_START_HEADER("c_delete_punctuation");
  RUN_TEST(test_c_delete_punctuation_when_string_has_punct_chars);
  RUN_TEST(test_c_delete_punctuation_when_string_has_no_punct_chars);
  RUN_TEST(test_c_delete_punctuation_when_string_empty);
  RUN_TEST(test_c_delete_punctuation_when_string_null);
  TEST_BLOCK_END_HEADER("c_delete_punctuation");

  TEST_BLOCK_START_HEADER("c_change_char_all");
  RUN_TEST(test_c_change_char_all_when_change_letter_to_letter);
  RUN_TEST(test_c_change_char_all_when_change_punct_char_to_letter);
  RUN_TEST(test_c_change_char_all_when_from_char_do_not_in_string);
  RUN_TEST(test_c_change_char_all_when_from_char_is_end_symbol);
  RUN_TEST(test_c_change_char_all_when_string_empty);
  RUN_TEST(test_c_change_char_all_when_string_null);
  TEST_BLOCK_END_HEADER("c_change_char_all");

  TEST_BLOCK_START_HEADER("c_delete_duplicates");
  RUN_TEST(test_c_delete_duplicates_when_string_has_duplicates);
  RUN_TEST(test_c_delete_duplicates_when_string_has_no_duplicates);
  RUN_TEST(test_c_delete_duplicates_when_string_empty);
  RUN_TEST(test_c_delete_duplicates_when_string_null);
  TEST_BLOCK_END_HEADER("c_delete_duplicates");

  TEST_BLOCK_START_HEADER("c_strcpy");
  RUN_TEST(test_c_strcpy_when_copy_from_correct_string);
  RUN_TEST(test_c_strcpy_when_dest_and_from_equal);
  RUN_TEST(test_c_strcpy_when_from_empty_string);
  RUN_TEST(test_c_strcpy_when_dest_string_null);
  RUN_TEST(test_c_strcpy_when_from_string_null);
  TEST_BLOCK_END_HEADER("c_strcpy");

  TEST_BLOCK_START_HEADER("c_sort_chars");
  RUN_TEST(test_c_sort_chars_when_letters_in_reverse_alphabetical_order);
  RUN_TEST(test_c_sort_chars_when_letters_already_in_alphabetical_order);
  RUN_TEST(test_c_sort_chars_when_string_empty);
  RUN_TEST(test_c_sort_chars_when_string_null);
  TEST_BLOCK_END_HEADER("c_sort_chars");

  TEST_BLOCK_START_HEADER("c_strcat");
  RUN_TEST(test_c_strcat_when_dest_size_enough_for_cat);
  RUN_TEST(test_c_strcat_when_from_len_plus_dest_len_equal_dest_size);
  RUN_TEST(test_c_strcat_when_from_string_empty);
  RUN_TEST(test_c_strcat_when_dest_string_empty);
  RUN_TEST(test_c_strcat_when_from_string_null);
  RUN_TEST(test_c_strcat_when_dest_string_null);
  TEST_BLOCK_END_HEADER("c_strcat");

  TEST_BLOCK_START_HEADER("c_trim");
  RUN_TEST(test_c_trim_when_string_has_start_and_end_spaces);
  RUN_TEST(test_c_trim_when_string_has_start_and_end_tabs);
  RUN_TEST(test_c_trim_when_string_has_start_end_and_middle_space);
  RUN_TEST(test_c_trim_when_string_has_start_end_and_middle_tabs);
  RUN_TEST(test_c_trim_when_string_empty);
  RUN_TEST(test_c_trim_when_string_null);
  TEST_BLOCK_END_HEADER("c_trim");

  TEST_BLOCK_START_HEADER("c_detab");
  RUN_TEST(test_c_detab_when_string_has_tabs_and_size_enough_for_spaces);
  RUN_TEST(test_c_detab_when_string_size_not_enough);
  RUN_TEST(test_c_detab_when_detab_string_len_equal_buff_size);
  RUN_TEST(test_c_detab_when_detab_string_size_equal_buff_size);
  RUN_TEST(test_c_detab_when_string_empty);
  RUN_TEST(test_c_detab_when_string_null);
  TEST_BLOCK_END_HEADER("c_detab");

  TEST_BLOCK_START_HEADER("c_entab");
  RUN_TEST(test_c_entab_when_set_two_tabs);
  RUN_TEST(test_c_entab_when_set_one_tab_in_begin);
  RUN_TEST(test_c_entab_when_set_one_tab_in_end);
  RUN_TEST(test_c_entab_when_string_empty);
  RUN_TEST(test_c_entab_when_string_null);
  TEST_BLOCK_END_HEADER("c_entab");

  TEST_BLOCK_START_HEADER("c_overwrite_from");
  RUN_TEST(test_c_overwrite_from_when_string_has_enough_space_for_substr);
  RUN_TEST(test_c_overwrite_from_when_string_has_no_space_for_substr);
  RUN_TEST(test_c_overwrite_from_when_insert_substr_in_end_of_str);
  RUN_TEST(test_c_overwrite_from_when_substr_empty);
  RUN_TEST(test_c_overwrite_from_when_string_empty);
  RUN_TEST(test_c_overwrite_from_when_string_null);
  RUN_TEST(test_c_overwrite_from_when_substr_null);
  TEST_BLOCK_END_HEADER("c_overwrite_from");

  UnityEnd();

  return 0;
}
