#include "../include/c_string.h" // better way to include?
#include "internal/_str_internal.h"

int c_strlen(const char s[]) {
  int i = 0;
  while (s[i] != '\0') {
    ++i;
  }
  return i;
}

void c_strcpy(char to[], const char from[]) {
  int i = 0;
  while ((to[i] = from[i]) != '\0')
    ++i;
}

// to string must have size >= to + from
void c_strcat(char to[], char from[]) {

  int start_insert_from = c_strlen(to);

  int i = start_insert_from;
  int result_string_size = start_insert_from + c_strlen(from);
  for (int j = 0; i < result_string_size; ++i) {
    to[i] = from[j++];
  }

  to[i] = '\0';
}

void c_to_lower(char s[]) {
  _c_change_letter_size(s, UPPER_LETTER_START, UPPER_LETTER_END, PLUS);
}

void c_to_upper(char s[]) {
  _c_change_letter_size(s, LOWER_LETTER_START, LOWER_LETTER_END, MINUS);
}

int c_strcmp(const char first[], const char second[]) {

  const int size_first = (c_strlen(first) + STR_END_SYMBOL);
  const int size_second = (c_strlen(second) + STR_END_SYMBOL);

  if (size_first == size_second) {
    return _c_compare_symbols(first, second, size_first);
  }

  const int shorter_size =
      (size_first >= size_second) ? size_first : size_second;

  return _c_compare_symbols(first, second, shorter_size);
}

void c_invert_symbols(char s[]) {

  for (int i = 0; s[i] != '\0'; ++i) {
    if ((s[i] >= UPPER_LETTER_START) && (s[i] <= UPPER_LETTER_END)) {
      s[i] += DIFFERENCE_LETTERS_SIZE;
    } else if ((s[i] >= LOWER_LETTER_START) && (s[i] <= LOWER_LETTER_END)) {
      s[i] -= DIFFERENCE_LETTERS_SIZE;
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

  const int ASCII_SYMBOLS_START = 33;
  const int ASCII_SYMBOLS_END = 126;

  int result = 0;

  for (int i = 0; s[i] != '\0'; ++i) {
    if ((s[i] >= ASCII_SYMBOLS_START) && (s[i] <= ASCII_SYMBOLS_END)) {
      ++result;
    }
  }

  return result;
}

// TODO:Does not work properly
// void c_entab(char s[], const int space_for_tab) {}

void c_detab(char s[], const int space_for_tab) {

  // Find number of tabs
  int number_of_tabs = _c_count_tabs(s);

  if (number_of_tabs == 0) {
    return;
  }

  const int original_string_size = c_strlen(s) + STR_END_SYMBOL;
  const int size_new_string =
      original_string_size + (number_of_tabs * space_for_tab);

  char string_without_tabs[size_new_string];

  int j = 0;
  for (int i = 0; s[i] != '\0'; ++i) {
    if (s[i] == '\t') {
      _c_insert_n_spaces(string_without_tabs, space_for_tab, &j);
    } else {
      string_without_tabs[j++] = s[i];
    }
  }

  string_without_tabs[j] = '\0';

  c_strcpy(s, string_without_tabs);
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

void c_reverse(char s[]) {

  int j = c_strlen(s) - STR_END_SYMBOL;

  for (int i = 0; i <= j; ++i, --j) {
    _c_swap_char(s + i, s + j);
  }
}

void c_change_char_to(char s[], const char from_char, const char to_char) {

  for (int i = 0; s[i] != '\0'; ++i) {
    if (s[i] == from_char) {
      s[i] = to_char;
    }
  }
}

int c_remove_digits(char s[]) {

  int j = 0;
  int num_digits_removed = 0;
  const int copy_string_size = c_strlen(s) + STR_END_SYMBOL;

  char string_without_nums[copy_string_size];

  for (int i = 0; s[i] != '\0'; ++i) {
    if (!(s[i] >= '0' && s[i] <= '9')) {
      string_without_nums[j++] = s[i];
    } else {
      num_digits_removed++;
    }
  }

  string_without_nums[j] = '\0';

  c_strcpy(s, string_without_nums);

  return num_digits_removed;
}

// Two bottom functions use char [][] instead of char **
int c_count_words(const char s[]) {

  // TODO Make dynamic array_of_words
  const int length_string = c_strlen(s);
  char arr_words[length_string][length_string];
  _c_init_char_arr2d('\0', length_string, length_string, arr_words);

  int result = 0;
  _c_get_arr_of_words(length_string, arr_words, s);

  for (int i = 0; arr_words[i][0] != '\0'; ++i) {
    result++;
  }

  return result;
}

// Don't save order of spaces. Trim string
// and add only 1 space after word.
void c_reverse_word_order(char s[], const char delim) {
  const int length_string = c_strlen(s);
  char arr_words[length_string][length_string];
  _c_init_char_arr2d('\0', length_string, length_string, arr_words);
  //_c_get_arr_of_words(length_string, arr_words, s);
  _c_get_words_arr_by_delim(length_string, arr_words, s, ' ');

  int num_words = _c_get_size_arr2d(length_string, arr_words);

  int k = 0;
  for (int i = num_words - 1; i >= 0; --i) {
    for (int j = 0; arr_words[i][j] != '\0'; ++j) {
      s[k++] = arr_words[i][j];
    }
    s[k++] = delim;
  }
  s[k] = '\0';
}

int c_is_empty_string(const char s[]) { return !c_strcmp(s, ""); }

int c_is_string_of_digits(const char s[]) {

  if (c_is_empty_string(s)) {
    return 0;
  }

  int is_all_digits = TRUE;
  for (int i = 0; s[i] != '\0'; ++i) {
    if (!((s[i] >= '0') && (s[i] <= '9'))) {
      return !is_all_digits;
    }
  }

  return is_all_digits;
}

int c_is_char_in_string(const char s[], const char chr) {

  int char_in_string = TRUE;

  for (int i = 0; s[i] != '\0'; ++i) {
    if (s[i] == chr) {
      return char_in_string;
    }
  }

  return !char_in_string;
}

int c_delete_duplicates(char s[]) {

  const int cleaned_string_size = c_strlen(s) + STR_END_SYMBOL;
  char cleaned_string[cleaned_string_size];
  _c_init_char_arr(cleaned_string, '\0', cleaned_string_size);

  int j = 0;

  for (int i = 0; s[i] != '\0'; ++i) {
    if (!c_is_char_in_string(cleaned_string, s[i])) {
      cleaned_string[j++] = s[i];
    }
  }

  cleaned_string[j] = '\0';

  c_strcpy(s, cleaned_string);

  return 0;
}

int c_is_palindrom(const char s[]) {

  if (c_is_empty_string(s)) {
    return FALSE;
  }

  const int copy_size = c_strlen(s) + STR_END_SYMBOL;
  char copy_string[copy_size];

  c_strcpy(copy_string, s);
  c_reverse(copy_string);

  for (int i = 0; s[i] != '\0'; ++i) {
    if (s[i] != copy_string[i]) {
      return FALSE;
    }
  }
  return TRUE;
}

void c_sort_chars(char s[]) { _c_insert_char_sort(s); }

// TODO:Simplify
int c_first_unique_char(const char s[]) {

  if (c_strlen(s) == 1) {
    return s[0];
  }

  const int end_symbol = c_strlen(s) - 2;

  for (int i = 0; i <= end_symbol; ++i) {
    int j = i + 1;
    int find_duplicate = FALSE;

    for (; s[j] != '\0'; ++j) {
      if (s[j] == s[i]) {
        find_duplicate = TRUE;
        break;
      }
    }
    if (!find_duplicate) {
      return s[i];
    }
  }

  return -1;
}

int c_is_digit(const char c) { return (c >= '0' && c <= '9') ? TRUE : FALSE; }

int c_is_symbol(const char c) { return (c >= '!' && c <= '~') ? TRUE : FALSE; }

int c_is_space(const char c) { return (c == ' ') ? TRUE : FALSE; }

int c_is_tab(const char c) { return (c == '\t') ? TRUE : FALSE; }

int c_is_letter(const char c) {
  return ((c >= LOWER_LETTER_START && c <= LOWER_LETTER_END) ||
          (c >= UPPER_LETTER_START && c <= UPPER_LETTER_END))
             ? TRUE
             : FALSE;
}

void c_trim(char s[]) {

  const int copy_size = c_strlen(s) + STR_END_SYMBOL;
  char trimmed_copy[copy_size];

  int i = 0;
  int j = c_strlen(s) - STR_END_SYMBOL;

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

  c_strcpy(s, trimmed_copy);
}

// Don't work. Use hash table for o(n)
void c_delete_word_duplicate(char s[]) {
  // TODO: 4 bottom lines in one function?
  const int length_string = c_strlen(s);
  char arr_words[length_string][length_string];
  _c_init_char_arr2d('\0', length_string, length_string, arr_words);
  _c_get_arr_of_words(length_string, arr_words, s);

  const int num_words = _c_get_size_arr2d(length_string, arr_words);

  int find_duplicate = FALSE;
  // TODO: replace num literals
  for (int i = 0; i <= num_words - 2; ++i) {
    for (int j = i + 1; j <= num_words - 1; ++j) {
      if (c_strcmp(arr_words[i], arr_words[j]) == 0) {
        find_duplicate = TRUE;
        break;
      }
    }

    // TODO: not effective
    if (!find_duplicate) {
      c_strcpy(s, arr_words[i]);
    }
    find_duplicate = FALSE;
  }
}

/*void c_strtok(char s[], char **result, const char delim) {
  const int length_string = c_strlen(s);
  char arr_words[length_string][length_string];
  _c_init_char_arr2d('\0', length_string, length_string, arr_words);
  _c_get_words_arr_by_delim(length_string, arr_words, s, delim);
  // TODO: return result in char**
}*/
