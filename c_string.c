#include "c_string.h"
#include <stdio.h>

// helping functions

void _c_change_letter_size(char s[], int bottom_border, int upper_border,
                           enum _operation_type operation) {
  for (int i = 0; s[i] != '\0'; ++i) {
    if (((s[i] >= bottom_border) && (s[i] <= upper_border)) &&
        (operation == PLUS)) {
      s[i] += difference_letters_size;
    } else if (((s[i] >= bottom_border) && (s[i] <= upper_border)) &&
               (operation == MINUS)) {
      s[i] -= difference_letters_size;
    }
  }
}

int _c_compare_symbols(const char first[], const char second[],
                       int min_length) {
  for (int i = 0; i < min_length; ++i) {
    // Difference > 0 -> first
    // Difference < 0 -> second
    int difference = first[i] - second[i];
    if (difference > 0 || difference < 0) {
      return difference;
    }
  }
  return 0;
}

//

int c_strlen(const char s[]) {
  int chars = 0;
  for (int i = 0; s[i] != '\0'; ++i) {
    ++chars;
  }
  return chars;
}

void c_strcpy(char to[], const char from[]) {

  int i = 0;
  while ((to[i] = from[i]) != '\0')
    ++i;
}

void c_strcat(char to[], char from[]) {

  int start_insert_from = c_strlen(to) + 1;

  int i = start_insert_from;
  int result_string_size = c_strlen(to) + c_strlen(from) + 1;
  for (int j = 0; i < result_string_size; ++i) {
    to[i] = from[j++];
  }

  to[i] = '\0';
}

void c_to_lower(char s[]) {
  _c_change_letter_size(s, upper_start, upper_end, PLUS);
}

void c_to_upper(char s[]) {
  _c_change_letter_size(s, lower_start, lower_end, MINUS);
}

int c_strcmp(const char first[], const char second[]) {

  const int size_first = (c_strlen(first) + 1);
  const int size_second = (c_strlen(second) + 1);

  if (size_first == size_second) {
    return _c_compare_symbols(first, second, size_first);
  }

  const int shorter_size =
      (size_first >= size_second) ? size_first : size_second;

  return _c_compare_symbols(first, second, shorter_size);
}

void c_invert_symbols(char s[]) {

  for (int i = 0; s[i] != '\0'; ++i) {
    if ((s[i] >= upper_start) && (s[i] <= upper_end)) {
      s[i] += difference_letters_size;
    } else if ((s[i] >= lower_start) && (s[i] <= lower_end)) {
      s[i] -= difference_letters_size;
    }
  }
}

void c_delete_spaces(char s[]) {

  int j = 0;

  for (int i = 0; s[i] != '\0'; ++i) {
    if (s[i] != ' ') {
      s[j++] = s[i];
    }
  }

  s[j] = '\0';
}

int c_count_symbols(const char s[]) {

  const int ascii_symbols_start = 33;
  const int ascii_symbols_end = 126;

  int result = 0;

  for (int i = 0; s[i] != '\0'; ++i) {
    if ((s[i] >= ascii_symbols_start) && (s[i] <= ascii_symbols_end)) {
      ++result;
    }
  }

  return result;
}

void c_delete_punctuation(char s[]) {

  int j = 0;

  for (int i = 0; s[i] != '\0'; ++i) {
    if (s[i] != '!' && s[i] != '?' && s[i] != '.' && s[i] != ',') {
      s[j++] = s[i];
    }
  }

  s[j] = '\0';
}

// Add version without second char array
void c_reverse(char s[]) {

  const int copy_size = c_strlen(s) + 1;

  char copy_string[copy_size];
  int j = 0;

  for (int i = (copy_size - 2); i >= 0; --i) {
    copy_string[j++] = s[i];
  }

  copy_string[j] = '\0';

  for (int j = 0; copy_string[j] != '\0'; ++j) {
    s[j] = copy_string[j];
  }
}

void c_change_symbol_to(char s[], char remove_char, char add_char) {

  for (int i = 0; s[i] != '\0'; ++i) {
    if (s[i] == remove_char) {
      s[i] = add_char;
    }
  }
}

int c_remove_numbers(char s[]) {

  int j = 0;
  int num_digits_removed = 0;
  const int copy_string_size = c_strlen(s) + 1;

  char string_without_nums[copy_string_size];

  for (int i = 0; s[i] != '\0'; ++i) {
    if (!(s[i] >= '0' && s[i] <= '9')) {
      string_without_nums[j++] = s[i];
    } else {
      num_digits_removed++;
    }
  }

  string_without_nums[j] = '\0';

  int k = 0;

  for (int i = 0; string_without_nums[i] != '\0'; ++i) {
    s[k++] = string_without_nums[i];
  }

  s[k] = '\0';

  return num_digits_removed;
}

// int c_count_words(char s[]) { return 0; }

int c_is_string_of_digits(char s[]) {
  int is_all_digits = 1;
  for (int i = 0; s[i] != '\0'; ++i) {
    if (!((s[i] >= '0') && (s[i] <= '9'))) {
      return !is_all_digits;
    }
  }

  return is_all_digits;
}

int c_is_symbol_in_string(char s[], char chr) {

  int char_in_string = 1;

  for (int i = 0; s[i] != '\0'; ++i) {
    if (s[i] == chr) {
      return char_in_string;
    }
  }

  return !char_in_string;
}

int c_delete_duplicates(char s[]) {

  const int cleaned_string_size = c_strlen(s) + 1;
  char cleaned_string[cleaned_string_size];

  int j = 0;

  for (int i = 0; s[i] != '\0'; ++i) {
    if (!c_is_symbol_in_string(cleaned_string, s[i])) {
      cleaned_string[j++] = s[i];
    }
  }

  cleaned_string[j] = '\0';
  j = 0;

  for (int i = 0; cleaned_string[i] != '\0'; ++i) {
    s[j++] = cleaned_string[i];
  }

  s[j] = '\0';

  return 0;
}

int c_is_palindrom(char s[]) {
  const int copy_size = c_strlen(s) + 1;
  char copy_string[copy_size];

  c_strcpy(copy_string, s);
  c_reverse(copy_string);

  for (int i = 0; s[i] != '\0'; ++i) {
    if (s[i] != copy_string[i]) {
      return 0;
    }
  }
  return 1;
}

int c_first_unique_symbol(char s[]) {

  const int end_symbol = c_strlen(s) - 2;

  for (int i = 0; i <= end_symbol; ++i) {
    int j = i + 1;
    int find_duplicate = 0;

    for (; s[j] != '\0'; ++j) {
      if (s[j] == s[i]) {
        find_duplicate = 1;
        break;
      }
    }
    if (!find_duplicate) {
      return s[i];
    }
  }

  return -1;
}

int c_is_digit(char c) { return (c >= '0' && c <= '9') ? 1 : 0; }

int c_is_symbol(char c) { return (!c_is_digit(c)) ? 1 : 0; }

int c_is_space(char c) { return (c == ' ') ? 1 : 0; }

int c_is_tab(char c) { return (c == '\t') ? 1 : 0; }

void c_trim(char s[]) {

  const int copy_size = c_strlen(s) + 1;
  char trimmed_copy[copy_size];

  int i = 0;
  int j = c_strlen(s) - 1;

  while (c_is_space(s[i]) || c_is_tab(s[i])) {
    ++i;
  }

  while (c_is_space(s[j]) || c_is_tab(s[j])) {
    --j;
  }

  int k = 0;

  for (; i < j; ++i) {
    trimmed_copy[k++] = s[i];
  }

  trimmed_copy[k] = '\0';

  int l = 0;
  for (; trimmed_copy[l] != '\0'; ++l) {
    s[l] = trimmed_copy[l];
  }

  s[l] = '\0';
}

/////////////////////////////

int get_line(char s[], int s_length) {
  int c = 0;
  int i;

  for (i = 0; (i < (s_length - 1)) && ((c = getchar()) != EOF) && (c != '\n');
       ++i) {
    s[i] = c;
  }
  s[i] = '\0';
  return i;
}

void correct_string(char s[], int length) {

  char cp_s[length];

  int i = 0;
  int j = 0;

  int start_space = 0;

  while (s[i] != '\0') {
    if (start_space && ((s[i] == ' ') || (s[i] == '\t'))) {
      ;
    } else if (s[i] == '\t') {
      start_space = 1;
      cp_s[j] = ' ';
      ++j;
    } else if (s[i] == ' ') {
      start_space = 1;
      cp_s[j] = ' ';
      ++j;
    } else {
      start_space = 0;
      cp_s[j] = s[i];
      ++j;
    }
    ++i;
  }

  for (int k = 0; k < j; ++k) {
    s[k] = cp_s[k];
  }
  s[j] = '\0';
}
