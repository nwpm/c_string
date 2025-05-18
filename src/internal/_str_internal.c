#include "_str_internal.h"

void _c_swap_char(char *c1, char *c2) {
  char tmp_val = *c1;
  *c1 = *c2;
  *c2 = tmp_val;
}

int _c_count_tabs(const char *s) {

  int number_of_tabs = 0;

  for (int i = 0; s[i] != '\0'; ++i) {
    if (s[i] == '\t') {
      number_of_tabs++;
    }
  }

  return number_of_tabs;
}

int _c_count_spaces(const char *s) {

  int number_of_spaces = 0;

  for (int i = 0; s[i] != '\0'; ++i) {
    if (s[i] == ' ') {
      number_of_spaces++;
    }
  }

  return number_of_spaces;
}

void _c_insert_n_spaces(char *s, const int num_spaces, int *insert_from) {
  for (int k = num_spaces; k != 0; --k) {
    s[(*insert_from)++] = ' ';
  }
}
