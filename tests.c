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

  printf("\nAll tests passed!\n");
  return 0;
}
