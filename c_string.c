#include "c_string.h"
// helping functions

void _c_change_letter_size(char s[], int bottom_border, int upper_border,
                           enum _operation_type operation) {
  for (int i = 0; s[i] != '\0'; ++i) {
    if (((s[i] >= bottom_border) && (s[i] <= upper_border)) &&
        (operation == PLUS)) {
      s[i] += DIFFERENCE_LETTERS_SIZE;
    } else if (((s[i] >= bottom_border) && (s[i] <= upper_border)) &&
               (operation == MINUS)) {
      s[i] -= DIFFERENCE_LETTERS_SIZE;
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

// TODO
void c_entab(char s[], const int space_for_tab) {
  int is_space = 0;
  int conter_for_spaces = 0;
  char result_string[c_strlen(s) + 1];

  int k = 0;
  for (int i = 0; s[i] != '\0'; ++i) {
    if (conter_for_spaces == space_for_tab) {
      result_string[k++] = '_';
      is_space = 0;
      conter_for_spaces = 0;
    }

    if (s[i] == ' ' && !is_space) {
      is_space = 1;
      conter_for_spaces++;
    } else if (s[i] == ' ' && is_space) {
      conter_for_spaces++;
    } else {
      result_string[k++] = s[i];
      is_space = 0;
      conter_for_spaces = 0;
    }
  }

  result_string[k] = '\0';
}

void c_detab(char s[], const int space_for_tab) {
  const int original_string_size = c_strlen(s);

  // Find tabs position
  int i = 0;
  int number_of_tabs = 0;
  for (; s[i] != '\0'; ++i) {
    if (s[i] == '\t') {
      number_of_tabs++;
    }
  }

  number_of_tabs = (number_of_tabs == 0) ? 0 : number_of_tabs + 1;
  const int size_new_string =
      original_string_size + (number_of_tabs * space_for_tab);

  char string_without_tabs[size_new_string + SIZE_STRING_END];

  int j = 0;
  for (int i = 0; s[i] != '\0'; ++i) {
    if (s[i] == '\t') {
      for (int k = space_for_tab; k != 0; --k) {
        string_without_tabs[j++] = ' ';
      }
    } else {
      string_without_tabs[j++] = s[i];
    }
  }

  string_without_tabs[j] = '\0';

  j = 0;

  for (int i = 0; string_without_tabs[i] != '\0'; ++i) {
    s[j++] = string_without_tabs[i];
  }

  s[j] = '\0';
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

int c_remove_digits(char s[]) {

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

int c_count_words(char s[]) {

  // TODO Make dynamic array_of_words
  const int length_string = c_strlen(s);
  char array_of_words[length_string][length_string];

  /*
   * 1) Create array for all words in string
   * 2) Make 2 index for current word and char in these word
   * 3) Iterate string and add char in separate words
   * 4) Add '\0' in the end
   * 5) Count all words in for
   *
   */

  int is_word = FALSE;
  int words_index = 0;
  int char_index = 0;
  int result = 0;

  int i = 0;

  for (; s[i] != '\0'; ++i) {
    if (!c_is_letter(s[i]) && is_word) {
      is_word = FALSE;
      array_of_words[words_index][char_index] = '\0';
      words_index++;
      char_index = 0;
    } else if (c_is_letter(s[i]) && !is_word) {
      is_word = TRUE;
      array_of_words[words_index][char_index++] = s[i];
    } else if (c_is_letter(s[i]) && is_word) {
      array_of_words[words_index][char_index++] = s[i];
    }
  }

  if (is_word) {
    array_of_words[words_index][char_index] = '\0';
    array_of_words[words_index + 1][0] = '\0';
  } else {
    array_of_words[words_index][0] = '\0';
  }

  for (int i = 0; array_of_words[i][0] != '\0'; ++i) {
    result++;
  }

  return result;
}

int c_is_empty_string(const char s[]) { return !c_strcmp(s, ""); }

int c_is_string_of_digits(char s[]) {

  if (c_is_empty_string(s)) {
    return 0;
  }

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

  if (c_is_empty_string(s)) {
    return FALSE;
  }

  const int copy_size = c_strlen(s) + 1;
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
