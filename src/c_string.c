#include "../include/c_string.h" // better way to include?
#include "internal/_c_common.h"
#include "internal/_str_internal.h"

#define NULL 0

int c_strlen(const char *s) {

  if (s == NULL) {
    return -1;
  }

  int i = 0;
  while (s[i] != '\0') {
    ++i;
  }
  return i;
}

void c_strcpy(char *to, const char *from) {
  int i = 0;
  while ((to[i] = from[i]) != END_SYMBOL) {
    ++i;
  }
}

// Required: "to" string must have size >= to + from
void c_strcat(char *to, char *from) {

  int start_insert_from = c_strlen(to);

  int i = start_insert_from;
  int result_string_size = start_insert_from + c_strlen(from);
  for (int j = 0; i < result_string_size; ++i) {
    to[i] = from[j++];
  }

  to[i] = END_SYMBOL;
}

void c_str_to_lower(char *s) {
  for (int i = 0; s[i] != END_SYMBOL; ++i) {
    s[i] = c_is_upper_letter(s[i]) ? c_letter_to_lower(s[i]) : s[i];
  }
}

void c_str_to_upper(char *s) {
  for (int i = 0; s[i] != END_SYMBOL; ++i) {
    s[i] = c_is_lower_letter(s[i]) ? c_letter_to_upper(s[i]) : s[i];
  }
}

int c_strcmp(const char *first, const char *second) {
  while (*first && (*first == *second)) {
    ++first;
    ++second;
  }
  return *first - *second;
}

qboolean c_is_lower_letter(const char c) {
  return (c >= LOWER_LETTER_START && c <= LOWER_LETTER_END) ? TRUE : FALSE;
}

qboolean c_is_upper_letter(const char c) {
  return (c >= UPPER_LETTER_START && c <= UPPER_LETTER_END) ? TRUE : FALSE;
}

char c_letter_to_lower(char c) { return c += DIFFERENCE_LETTERS_SIZE; }

char c_letter_to_upper(char c) { return c -= DIFFERENCE_LETTERS_SIZE; }

void c_invert_symbols(char *s) {

  for (int i = 0; s[i] != END_SYMBOL; ++i) {
    if (c_is_upper_letter(s[i])) {
      s[i] = c_letter_to_lower(s[i]);
    } else if (c_is_lower_letter(s[i])) {
      s[i] = c_letter_to_upper(s[i]);
    }
  }
}

// Required: The `to` buffer must have enough space for the entire `substr`,
// starting at position insert_from, including the terminating '\0'
void c_insert_str_from(char *to, const char *substr, const int insert_from) {

  int copy_insert_from = insert_from;

  for (int i = 0; substr[i] != END_SYMBOL; ++i) {
    to[copy_insert_from++] = substr[i];
  }
}

void c_delete_spaces(char *s) {

  int j = 0;

  for (int i = 0; s[i] != END_SYMBOL; ++i) {
    if (s[i] != ' ') {
      s[j++] = s[i];
    }
  }

  s[j] = END_SYMBOL;
}

// c_entab remove n spaces and set their to /t
void c_entab(char *s, const int space_for_tab) {
  const int buffer_size = space_for_tab + SIZE_END_SYMBOL;
  char buffer[buffer_size];
  _c_init_char_arr(buffer, END_SYMBOL, buffer_size);

  int buff_i = 0;
  int k = 0;
  for (int i = 0; s[i] != END_SYMBOL; ++i) {
    // Check - is buffer full
    if (buffer[buffer_size - 2] != END_SYMBOL) {
      if (_c_is_string_of_spaces(buffer)) {
        s[k++] = '\t';
      } else {
        _c_insert_str_from(s, buffer, &k);
      }
      // Clear buffer and index
      _c_init_char_arr(buffer, END_SYMBOL, buffer_size);
      buff_i = 0;
    }

    buffer[buff_i++] = s[i];
  }

  if (!c_is_empty_string(buffer)) {
    _c_insert_str_from(s, buffer, &k);
  }

  s[k] = END_SYMBOL;
}

// c_detab remove /t and insert n spaces
// c_detab The main disadvantage is that we work only in the original buffer
// (string) and if its size is not enough to store the converted string, the
// function will not work.
void c_detab(char *s, const int space_for_tab) {

  if (c_is_empty_string(s)) {
    return;
  }

  // Find number of tabs
  int number_of_tabs = _c_count_tabs(s);

  if (number_of_tabs == 0) {
    return;
  }

  // Formula of size new string
  // 1. Find number of chars without tabs
  // 2. Calculate the number of spaces that will replace tabs
  // 3. Result = (1) + (2)
  const int original_string_size = c_strlen(s) + SIZE_END_SYMBOL;
  const int size_new_string = (original_string_size - number_of_tabs) +
                              (number_of_tabs * space_for_tab);

  char string_without_tabs[size_new_string];

  int j = 0;
  for (int i = 0; s[i] != END_SYMBOL; ++i) {
    if (s[i] == '\t') {
      _c_insert_n_spaces(string_without_tabs, space_for_tab, &j);
    } else {
      string_without_tabs[j++] = s[i];
    }
  }

  string_without_tabs[j] = END_SYMBOL;

  c_strcpy(s, string_without_tabs);
}

void c_delete_punctuation(char *s) {

  int j = 0;

  for (int i = 0; s[i] != END_SYMBOL; ++i) {
    if (!c_is_punct_char(s[i])) {
      s[j++] = s[i];
    }
  }

  s[j] = END_SYMBOL;
}

void c_reverse(char *s) {

  int end_index = c_strlen(s) - SIZE_END_SYMBOL;

  for (int start_index = 0; start_index <= end_index;
       ++start_index, --end_index) {
    _c_swap_char(s + start_index, s + end_index);
  }
}

void c_change_char_all(char *s, const char from_char, const char to_char) {

  for (int i = 0; s[i] != END_SYMBOL; ++i) {
    if (s[i] == from_char) {
      s[i] = to_char;
    }
  }
}

int c_remove_digits(char *s) {

  if (s == NULL) {
    return -1;
  }

  int num_digits_removed = 0;

  int k = 0;
  for (int i = 0; s[i] != '\0'; ++i) {
    if (c_is_digit(s[i])) {
      ++num_digits_removed;
    } else {
      s[k++] = s[i];
    }
  }
  s[k] = '\0';

  return num_digits_removed;
}

// use-stdlib-memory Two bottom functions use char [][] instead of char **
int c_count_words(const char *s) {

  if (s == NULL) {
    return -1;
  }

  // TODO: If we want make dynamic array_of_words
  // must include <stdlib.h>
  const int length_string = c_strlen(s);
  char arr_words[length_string][length_string];
  _c_init_char_arr2d('\0', length_string, length_string, arr_words);
  _c_get_arr_of_words(length_string, arr_words, s);

  return _c_get_size_arr2d(length_string, length_string, arr_words);
}

// Info: Don't save order of spaces. Trim string
// and add only 1 space after word.
void c_reverse_word_order(char *s, const char delim) {
  const int length_string = c_strlen(s);
  char arr_words[length_string][length_string];
  _c_init_char_arr2d(END_SYMBOL, length_string, length_string, arr_words);
  _c_get_words_arr_by_delim(length_string, arr_words, s, delim);

  int num_words = _c_get_size_arr2d(length_string, length_string, arr_words);

  int k = 0;
  for (int i = num_words - 1; i >= 0; --i) {
    for (int j = 0; arr_words[i][j] != '\0'; ++j) {
      s[k++] = arr_words[i][j];
    }
    // TODO: Simplify
    // Don't add delim in the end str
    if (i != 0) {
      s[k++] = delim;
    }
  }
  s[k] = '\0';
}

qboolean c_is_empty_string(const char s[]) { return !c_strlen(s); }

qboolean c_is_string_of_digits(const char *s) {

  if (c_is_empty_string(s)) {
    return FALSE;
  }

  while (*s) {
    if (!c_is_digit(*s)) {
      return FALSE;
    }
    ++s;
  }

  return TRUE;
}

qboolean c_is_char_in_string(const char *s, const char chr) {

  while (*s) {
    if (*s == chr) {
      return TRUE;
    }
    ++s;
  }

  return FALSE;
}

void c_delete_duplicates(char *s) {

  const int cleaned_string_size = c_strlen(s) + SIZE_END_SYMBOL;
  char cleaned_string[cleaned_string_size];
  cleaned_string[cleaned_string_size] = END_SYMBOL;

  int j = 0;

  for (int i = 0; s[i] != END_SYMBOL; ++i) {
    if (!c_is_char_in_string(cleaned_string, s[i])) {
      cleaned_string[j++] = s[i];
    }
  }

  cleaned_string[j] = END_SYMBOL;

  c_strcpy(s, cleaned_string);
}

qboolean c_is_palindrom(const char *s) {

  if (c_is_empty_string(s)) {
    return FALSE;
  }

  int end_index = c_strlen(s) - 1;
  int start_index = 0;

  while (start_index < end_index) {
    if (s[start_index] != s[end_index]) {
      return FALSE;
    } else {
      start_index++;
      end_index--;
    }
  }

  return TRUE;
}

void c_sort_chars(char *s) { _c_sort_str_chars(s); }

int c_first_unique_char(const char *s) {

  if (s == NULL) {
    return -1;
  }

  char count[256] = {0};

  for (int i = 0; s[i] != '\0'; ++i) {
    unsigned char c = (unsigned char)s[i];
    count[c]++;
  }

  for (int i = 0; s[i] != '\0'; ++i) {
    if (count[(unsigned char)s[i]] == 1) {
      return i;
    }
  }

  return -2;
}

qboolean c_is_digit(const char c) {
  return (c >= '0' && c <= '9') ? TRUE : FALSE;
}

qboolean c_is_punct_char(const char c) {
  return ((c >= '!' && c <= '/') || (c >= ':' && c <= '@') ||
          (c >= '[' && c <= '`') || (c >= '{' && c <= '~'))
             ? TRUE
             : FALSE;
}

qboolean c_is_space(const char c) { return (c == ' ') ? TRUE : FALSE; }

qboolean c_is_tab(const char c) { return (c == '\t') ? TRUE : FALSE; }

qboolean c_is_letter(const char c) {
  return ((c >= LOWER_LETTER_START && c <= LOWER_LETTER_END) ||
          (c >= UPPER_LETTER_START && c <= UPPER_LETTER_END))
             ? TRUE
             : FALSE;
}

void c_trim(char *s) {

  if (c_is_empty_string(s)) {
    return;
  }

  // Start index begin with first letter
  // End index start with last letter
  int start_index = 0;
  int end_index = c_strlen(s) - SIZE_END_SYMBOL;

  while (c_is_space(s[start_index]) || c_is_tab(s[start_index])) {
    ++start_index;
  }

  while (c_is_space(s[end_index]) || c_is_tab(s[end_index])) {
    --end_index;
  }

  int k = 0;
  for (; start_index <= end_index; ++start_index) {
    s[k++] = s[start_index];
  }

  s[k] = END_SYMBOL;
}

// TODO:Simplify
void c_delete_word_duplicate(char *s) {
  const int length_string = c_strlen(s);
  char arr_words[length_string][length_string];
  _c_init_char_arr2d('\0', length_string, length_string, arr_words);
  _c_get_arr_of_words(length_string, arr_words, s);
  _c_delete_duplicate_str_arr2d(length_string, length_string, arr_words);

  int k = 0;
  for (int i = 0; i < length_string; ++i) {
    int is_word_deleted = TRUE;
    for (int j = 0; arr_words[i][j] != '\0'; ++j) {
      s[k++] = arr_words[i][j];
      is_word_deleted = FALSE;
    }
    // Bad desition?
    if (i < length_string && !is_word_deleted) {
      s[k++] = ' ';
    }
  }
  s[k] = '\0';
}

// TODO: make with pointers arr
void c_strtok(char *s, const int cols, char (*result)[cols], const char delim) {
  _c_get_words_arr_by_delim(cols, result, s, delim);
}

// TODO: Simplify
void c_sort_words(char *s) {
  const int length_string = c_strlen(s);
  char arr_words[length_string][length_string];
  _c_init_char_arr2d('\0', length_string, length_string, arr_words);
  _c_get_arr_of_words(length_string, arr_words, s);
  int num_words = _c_get_size_arr2d(length_string, length_string, arr_words);
  _sort_words_arr2d(num_words, length_string, arr_words);

  int k = 0;
  for (int i = 0; i < num_words; ++i) {
    for (int j = 0; arr_words[i][j] != '\0'; ++j) {
      s[k++] = arr_words[i][j];
    }
    if (i < length_string) {
      s[k++] = ' ';
    }
  }

  s[k] = '\0';
}

int c_strstr(const char *s, const char *substr) {
  const int SUBSTR_LEN = c_strlen(substr);
  const int STR_LEN = c_strlen(s);
  const int BUFF_SIZE = SUBSTR_LEN + SIZE_END_SYMBOL;
  int k = 0;
  char buff[BUFF_SIZE];
  _c_init_char_arr(buff, '\0', BUFF_SIZE);

  for (int i = 0; i <= STR_LEN - SUBSTR_LEN; ++i) {
    for (int j = i; j < i + SUBSTR_LEN; ++j) {
      buff[k++] = s[j];
    }

    if (c_strcmp(buff, substr) == 0) {
      return i;
    }
    k = 0;
  }

  return -1;
}

int c_num_substr(const char *s, const char *substr) {
  const int SUBSTR_LEN = c_strlen(substr);
  const int STR_LEN = c_strlen(s);
  const int FAIL_RESULT_STR = -1;

  int res = 0;

  for (int i = 0; i <= STR_LEN - SUBSTR_LEN;) {
    if (c_strstr(s + i, substr) != FAIL_RESULT_STR) {
      ++res;
      i += SUBSTR_LEN;
    } else {
      ++i;
    }
  }

  return res;
}

// Size substr_new must be same as substr_old
void c_str_replace_first(char *s, const char *substr_old,
                         const char *substr_new) {
  const int FAIL_RESULT_STR = -1;
  const int STRSTR_RES = c_strstr(s, substr_old);

  if (STRSTR_RES != FAIL_RESULT_STR) {
    c_insert_str_from(s, substr_new, STRSTR_RES);
  }
}

// Size substr_new must be same as substr_old
void c_str_replace_all(char *s, const char *substr_old,
                       const char *substr_new) {
  const int SUBSTR_LEN = c_strlen(substr_old);
  const int STR_LEN = c_strlen(s);

  for (int i = 0; i < STR_LEN; i += SUBSTR_LEN) {
    c_str_replace_first(s + i, substr_old, substr_new);
  }
}

// Size substr_new must be same as substr_old
void c_str_replace_n(char *s, const char *substr_old, const char *substr_new,
                     const int n) {
  const int SUBSTR_LEN = c_strlen(substr_old);
  int k = 0;
  for (int i = 0; i < n; ++i) {
    c_str_replace_first(s + k, substr_old, substr_new);
    k += SUBSTR_LEN;
  }
}

qboolean c_is_anagrams(const char *s1, const char *s2) {
  const int s1_len = c_strlen(s1);
  const int s2_len = c_strlen(s2);
  qboolean is_same_len =
      ((s1_len != s2_len) || (c_is_empty_string(s1) && c_is_empty_string(s2))
           ? FALSE
           : TRUE);

  if (!is_same_len) {
    return FALSE;
  } else {

    // Create copy of strings for
    // a register-independent function
    char s1_copy[s1_len + SIZE_END_SYMBOL];
    char s2_copy[s2_len + SIZE_END_SYMBOL];

    s1_copy[s1_len] = END_SYMBOL;
    s2_copy[s2_len] = END_SYMBOL;

    c_strcpy(s1_copy, s1);
    c_strcpy(s2_copy, s2);

    c_str_to_lower(s1_copy);
    c_str_to_lower(s2_copy);

    for (int i = 0; s1_copy[i] != END_SYMBOL; ++i) {
      if (!c_is_char_in_string(s2_copy, s1_copy[i])) {
        return FALSE;
      }
    }
  }

  return TRUE;
}

int c_atoi(const char *s) {

  // Create copy string
  const int str_size = c_strlen(s);
  char copy_str[str_size + SIZE_END_SYMBOL];
  copy_str[str_size] = END_SYMBOL;
  // Init copy by original string and reverse
  c_strcpy(copy_str, s);
  c_reverse(copy_str);

  int res = 0;
  int exp_ten = 1;

  // Iterate for reverse copy
  // If find digit add  digit * 10^n
  // Take into account minus
  for (int i = 0; copy_str[i] != '\0'; ++i) {
    if (c_is_digit(copy_str[i])) {
      res += (copy_str[i] - '0') * exp_ten;
      exp_ten *= 10;
    } else if (copy_str[i] == '-') {
      res *= -1;
    }
  }

  return res;
}

// Required: s must have enough size for num
void c_itoa(const int num, char *s) {

  int copy_num = num;
  int delim = 10;
  int i = 0;

  do {
    int tmp = copy_num % delim;
    s[i] = tmp + '0';
    ++i;

  } while (copy_num /= delim);

  c_reverse(s);
}
