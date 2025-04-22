#include <assert.h>
#include <stdio.h>
#include <string.h>

#include "c_string.h"

void test_c_strlen(char s[]) {
  int input_len = c_strlen(s);
  int expected_len = strlen(s);

  assert(input_len == expected_len);
  printf("string \"%s\" : c_strlen passed\n", s);
}

void test_c_strcpy(char from[], char to[]) {
  c_strcpy(to, from);
  assert(strcmp(to, from) == 0);
  printf("string from : \"%s\" string to : \"%s\" : c_strcpy passed\n", from,
         to);
}

void test_c_strcmp(const char first[], const char second[]) {
  assert(c_strcmp(first, second) == strcmp(first, second));
  printf("string1 : \"%s\" string2 \"%s\" : c_strcmp passed\n", first, second);
}

void test_c_to_lower(char s1[], char s2[]) {
  c_to_lower(s1);
  assert(strcmp(s1, s2) == 0);
  printf("string \"%s\" : c_to_lower passed\n", s1);
}

void test_c_to_upper(char s1[], char s2[]) {
  c_to_upper(s1);
  assert(strcmp(s1, s2) == 0);
  printf("string \"%s\" : c_to_upper passed\n", s1);
}

void test_c_count_symbols(char s[], int res) {
  assert(c_count_symbols(s) == res);
  printf("string : \"%s\" has %d symbols : c_count_symbols passed\n", s, res);
}

void test_c_remove_digits(char s[], int res_num, char res_s[]) {
  assert(c_remove_digits(s) == res_num);
  assert(strcmp(s, res_s) == 0);
  printf("string : \"%s\", remove %d numbers : c_remove_numbers passed\n", s,
         res_num);
}

void test_c_is_string_of_digits(char s[], int res) {
  assert(c_is_string_of_digits(s) == res);
  printf("string : \"%s\" : c_is_string_of_digits passed\n", s);
}

void test_c_delete_duplicates(char s[], char s_res[]) {
  c_delete_duplicates(s);
  assert(strcmp(s, s_res) == 0);
  printf("string : \"%s\" : c_delete_duplicates passed\n", s);
}

void test_c_strcat(char s[], char s_add[], char res[]) {
  c_strcat(s, s_add);
  assert(strcmp(s, res) == 0);
  printf("string : \"%s\" : c_strcpy passed\n", s);
}

void test_c_is_palindrome(char s[], int res) {
  assert(c_is_palindrom(s) == res);
  printf("string : \"%s\" : c_is_palindrom passed\n", s);
}

void test_c_is_symbol(const char c, const int res) {
  assert(c_is_symbol(c) == res);
  printf("char : \"%c\" : c_is_symbol passed\n", c);
}

void test_c_is_letter(const char c, const int res) {
  assert(c_is_letter(c) == res);
  printf("char : \"%c\" : c_is_letter passed\n", c);
}

void test_c_is_digit(const char c, const int res) {
  assert(c_is_digit(c) == res);
  printf("char : \"%c\" : c_is_digit passed\n", c);
}

void test_c_count_words(const char s[], const int res) {
  assert(c_count_words(s) == res);
  printf("string : \"%s\" : c_count_words passed\n", s);
}

void test_c_is_char_in_string(const char s[], const char c, const int res) {
  assert(c_is_char_in_string(s, c) == res);
  printf("string : \"%s\" : c_is_char_in_string passed\n", s);
}

void test_c_first_unique_char(const char s[], const int res) {
  assert(c_first_unique_char(s) == res);
  printf("string : \"%s\" : c_first_unique_char passed\n", s);
}

void test_c_is_space(const char c, const int res) {
  assert(c_is_space(c) == res);
  printf("char : \"%c\" : c_is_space passed\n", c);
}

void test_c_is_tab(const char c, const int res) {
  assert(c_is_tab(c) == res);
  printf("char : \"%c\" : c_is_tab passed\n", c);
}

void test_c_is_empty_string(const char s[], const int res) {
  assert(c_is_empty_string(s) == res);
  printf("string : \"%s\" : c_is_empty_string passed\n", s);
}

void test_c_change_char_to(char s[], const int pos, const char add,
                           const char res[]) {
  c_change_char_to(s, pos, 'a');
  assert(strcmp(s, res) == 0);
  printf("string : \"%s\" : c_change_char_to passed\n", s);
}

void all_tests_c_strlen() {
  test_c_strlen("");
  test_c_strlen("Hello World");
  test_c_strlen("    Hello world     ");
  test_c_strlen("\t#####\b");
}

void all_tests_c_strcpy() {

  char from_1[] = "Hello World";
  char to_1[] = "";
  test_c_strcpy(from_1, to_1);

  char from_2[] = "";
  char to_2[] = "Hello World";
  test_c_strcpy(from_2, to_2);

  char from_3[] = "";
  char to_3[] = "";
  test_c_strcpy(from_3, to_3);

  char from_4[] = "d";
  char to_4[] = " ";
  test_c_strcpy(from_4, to_4);

  char from_5[] = " ";
  char to_5[] = " ";
  test_c_strcpy(from_5, to_5);
}

void all_tests_c_strcmp() {
  test_c_strcmp("Hello World", "Hello World");
  test_c_strcmp("", "");
  test_c_strcmp("\t", "\t");

  test_c_strcmp("adc", "abd");
  test_c_strcmp("abd", "abc");
  test_c_strcmp("abc", "abcde");
  test_c_strcmp("abcde", "abc");
  test_c_strcmp("a", "");
  test_c_strcmp("", "a");
  test_c_strcmp("Apple", "apple");
  test_c_strcmp("adc ", "abc");
  test_c_strcmp(" abc", "abc");
  test_c_strcmp("abc\t", "abc ");
  test_c_strcmp("abc\0def", "abc");
}

void all_tests_c_to_lower() {
  char s1[] = "ABC";
  test_c_to_lower(s1, "abc");

  char s2[] = "AbC";
  test_c_to_lower(s2, "abc");

  char s3[] = "abc";
  test_c_to_lower(s3, "abc");

  char s4[] = "+1 Abc";
  test_c_to_lower(s4, "+1 abc");

  char s5[] = "";
  test_c_to_lower(s5, "");

  char s6[] = "@";
  test_c_to_lower(s6, "@");
}

void all_tests_c_to_upper() {
  char s1[] = "ABC";
  test_c_to_upper(s1, "ABC");

  char s2[] = "AbC";
  test_c_to_upper(s2, "ABC");

  char s3[] = "abc";
  test_c_to_upper(s3, "ABC");

  char s4[] = "+1 Abc";
  test_c_to_upper(s4, "+1 ABC");

  char s5[] = "";
  test_c_to_upper(s5, "");

  char s6[] = "@";
  test_c_to_upper(s6, "@");
}

void all_tests_c_count_symbols() {
  char s1[] = "abc";
  test_c_count_symbols(s1, 3);

  char s2[] = "";
  test_c_count_symbols(s2, 0);

  char s3[] = "abc123";
  test_c_count_symbols(s3, 6);

  char s4[] = "abc  def";
  test_c_count_symbols(s4, 6);

  char s5[] = "\tabc  #// !";
  test_c_count_symbols(s5, 7);
}

void all_tests_c_remove_digits() {
  char s1[] = "12345";
  test_c_remove_digits(s1, 5, "");

  char s2[] = "abc";
  test_c_remove_digits(s2, 0, "abc");

  char s3[] = "abc123";
  test_c_remove_digits(s3, 3, "abc");

  char s4[] = "#####";
  test_c_remove_digits(s4, 0, "#####");
}

void all_tests_c_is_string_of_digits() {
  char s1[] = "12345";
  test_c_is_string_of_digits(s1, 1);

  char s2[] = "abc";
  test_c_is_string_of_digits(s2, 0);

  char s3[] = "";
  test_c_is_string_of_digits(s3, 0);

  char s5[] = "abc123";
  test_c_is_string_of_digits(s5, 0);

  char s6[] = "123a";
  test_c_is_string_of_digits(s6, 0);
}

void all_test_c_delete_duplicates() {
  char s1[] = "abc";
  test_c_delete_duplicates(s1, "abc");

  char s2[] = "";
  test_c_delete_duplicates(s2, "");

  char s3[] = "123";
  test_c_delete_duplicates(s3, "123");

  char s4[] = "aabc";
  test_c_delete_duplicates(s4, "abc");

  char s5[] = "\t\t";
  test_c_delete_duplicates(s5, "\t");

  char s6[] = "   ";
  test_c_delete_duplicates(s6, " ");
}

void all_tests_c_strcat() {
  char s1[] = "abc";
  char s_add1[] = "abc";
  test_c_strcat(s1, s_add1, "abcabc");

  char s2[] = "abc";
  char s_add2[] = "";
  test_c_strcat(s2, s_add2, "abc");

  char s3[] = "";
  char s_add3[] = "abc";
  test_c_strcat(s3, s_add3, "abc");

  char s4[] = "abc";
  char s_add4[] = "1";
  test_c_strcat(s4, s_add4, "abc1");
}

void all_tests_c_is_palindrom() {
  char s1[] = "abc";
  test_c_is_palindrome(s1, 0);

  char s2[] = "";
  test_c_is_palindrome(s2, 0);

  char s3[] = "tat";
  test_c_is_palindrome(s3, 1);

  char s4[] = "a";
  test_c_is_palindrome(s4, 1);
}

void all_tests_c_is_symbol() {
  test_c_is_symbol('a', TRUE);
  test_c_is_symbol('!', TRUE);
  test_c_is_symbol(' ', FALSE);
  test_c_is_symbol('\t', FALSE);
  test_c_is_symbol('\n', FALSE);
}

void all_tests_c_is_letter() {
  test_c_is_letter('a', TRUE);
  test_c_is_letter('!', FALSE);
  test_c_is_letter('1', FALSE);
  test_c_is_letter(' ', FALSE);
}

void all_tests_c_is_digit() {
  test_c_is_digit('a', FALSE);
  test_c_is_digit('1', TRUE);
  test_c_is_digit(' ', FALSE);
  test_c_is_digit('!', FALSE);
}

void all_tests_c_count_words() {
  test_c_count_words("Hello World", 2);
  test_c_count_words("Hello", 1);
  test_c_count_words(" Hello ", 1);
  test_c_count_words(" ", 0);
}

void all_tests_c_is_char_in_string() {
  test_c_is_char_in_string("abc", 'a', TRUE);
  test_c_is_char_in_string("abc", 'f', FALSE);
  test_c_is_char_in_string("abc ", ' ', TRUE);
  test_c_is_char_in_string("", 'a', FALSE);
}

void all_tests_c_first_unique_char() {
  test_c_first_unique_char("aaa", -1);
  test_c_first_unique_char("  a", 32);
  test_c_first_unique_char("abc", 97);
  test_c_first_unique_char("a", 97);
}

void all_tests_c_is_space() {
  test_c_is_space(' ', TRUE);
  test_c_is_space('a', FALSE);
}

void all_tests_c_is_tab() {
  test_c_is_tab(' ', FALSE);
  test_c_is_tab('\t', TRUE);
}

void all_tests_c_is_empty_string() {
  test_c_is_empty_string("", TRUE);
  test_c_is_empty_string(" ", FALSE);
  test_c_is_empty_string("abc", FALSE);
}

void all_tests_c_change_char_to() {}

int main(void) {
  printf("\nc_strlen tests started!\n");
  all_tests_c_strlen();

  printf("\nc_strcpy tests started!\n");
  all_tests_c_strcpy();

  printf("\nc_strcmp tests started!\n");
  all_tests_c_strcmp();

  printf("\nc_to_lower tests started!\n");
  all_tests_c_to_lower();

  printf("\nc_to_upper tests started!\n");
  all_tests_c_to_upper();

  printf("\nc_count_symbols tests started!\n");
  all_tests_c_count_symbols();

  printf("\nc_remove_digits tests started!\n");
  all_tests_c_remove_digits();

  printf("\nc_is_string_of_digits tests started!\n");
  all_tests_c_is_string_of_digits();

  printf("\nc_delete_duplicates tests started!\n");
  all_test_c_delete_duplicates();

  printf("\nc_strcat tests started!\n");
  all_tests_c_strcat();

  printf("\nc_is_palindrome tests started!\n");
  all_tests_c_is_palindrom();

  printf("\nc_is_symbols tests started!\n");
  all_tests_c_is_symbol();

  printf("\nc_is_letter tests started!\n");
  all_tests_c_is_letter();

  printf("\nc_is_digit tests started!\n");
  all_tests_c_is_digit();

  printf("\nc_count_words tests started!\n");
  all_tests_c_count_words();

  printf("\nc_is_char_in_string tests started!\n");
  all_tests_c_is_char_in_string();

  printf("\nc_first_unique_char tests started!\n");
  all_tests_c_first_unique_char();

  printf("\nc_is_space tests started!\n");
  all_tests_c_is_space();

  printf("\nc_is_tab tests started!\n");
  all_tests_c_is_tab();

  printf("\nc_is_empty_string tests started!\n");
  all_tests_c_is_empty_string();

  printf("\nAll tests passed!\n");

  return 0;
}
