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

int main(void) {
  printf("\nc_strlen tests started!\n");
  all_tests_c_strlen();

  printf("\nc_strcpy tests started!\n");
  all_tests_c_strcpy();

  printf("\nc_strcmp tests started!\n");
  all_tests_c_strcmp();

  printf("\nAll tests passed!\n");
  return 0;
}
