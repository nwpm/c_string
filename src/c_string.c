#include "../include/c_string.h" // better way to include?
#include "internal/_c_common.h"
#include "internal/_str_internal.h"

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

// TODO: add safe version
char *c_strcpy(char *dest, const char *from) {

  if (dest == NULL || from == NULL || dest == from) {
    return dest;
  }

  int i = 0;
  while ((dest[i] = from[i]) != '\0') {
    ++i;
  }

  return dest;
}

// Required: "to" string must have size >= to + from
char *c_strcat(char *dest, const char *from, const int dest_buff_size) {

  if (dest == NULL || from == NULL) {
    return NULL;
  }

  const int from_len = c_strlen(from);
  const int dest_len = c_strlen(dest);

  if (from_len + dest_len >= dest_buff_size) {
    return dest;
  }

  int start_index = dest_len;
  int end_index = start_index + from_len;
  for (int j = 0; start_index < end_index; ++start_index) {
    dest[start_index] = from[j++];
  }

  dest[start_index] = '\0';

  return dest;
}

char *c_str_to_lower(char *s) {

  if (s == NULL) {
    return s;
  }

  for (int i = 0; s[i] != '\0'; ++i) {
    s[i] = c_is_upper_letter(s[i]) ? c_letter_to_lower(s[i]) : s[i];
  }

  return s;
}

char *c_str_to_upper(char *s) {

  if (s == NULL) {
    return s;
  }

  for (int i = 0; s[i] != '\0'; ++i) {
    s[i] = c_is_lower_letter(s[i]) ? c_letter_to_upper(s[i]) : s[i];
  }

  return s;
}

int c_strcmp(const char *first, const char *second) {
  while (*first && (*first == *second)) {
    ++first;
    ++second;
  }
  return *first - *second;
}

qboolean c_is_lower_letter(const unsigned char c) {
  return (c >= LOWER_LETTER_START && c <= LOWER_LETTER_END) ? TRUE : FALSE;
}

qboolean c_is_upper_letter(const unsigned char c) {
  return (c >= UPPER_LETTER_START && c <= UPPER_LETTER_END) ? TRUE : FALSE;
}

char c_letter_to_lower(unsigned char c) {
  if (c_is_upper_letter(c)) {
    return c += DIFFERENCE_LETTERS_SIZE;
  }
  return c;
}

char c_letter_to_upper(unsigned char c) {
  if (c_is_lower_letter(c)) {
    return c -= DIFFERENCE_LETTERS_SIZE;
  }
  return c;
}

char *c_invert_symbols(char *s) {

  if (s == NULL) {
    return s;
  }

  for (int i = 0; s[i] != '\0'; ++i) {

    unsigned char c = s[i];

    if (c_is_upper_letter(c)) {
      s[i] = c_letter_to_lower(c);
    } else if (c_is_lower_letter(c)) {
      s[i] = c_letter_to_upper(c);
    }
  }

  return s;
}

// Required: The `to` buffer must have enough space for the entire `substr`,
// starting at position insert_from, including the terminating '\0'
char *c_overwrite_from(char *dest, const char *substr, const int insert_from,
                       const int buff_size) {

  if (dest == NULL || substr == NULL || c_is_empty_string(dest) ||
      c_is_empty_string(substr)) {
    return dest;
  }

  const int substr_len = c_strlen(substr);

  if (insert_from + substr_len >= buff_size) {
    return dest;
  }

  int insert_index = insert_from;

  for (int i = 0; substr[i] != '\0'; ++i) {
    dest[insert_index++] = substr[i];
  }

  return dest;
}

int c_delete_spaces(char *s) {

  if (s == NULL) {
    return -1;
  }

  int removed = 0;
  int write_pos = 0;

  for (int i = 0; s[i] != '\0'; ++i) {
    if (!c_is_space(s[i])) {
      s[write_pos++] = s[i];
    } else {
      removed++;
    }
  }

  s[write_pos] = '\0';

  return removed;
}

// c_entab remove n spaces and set their to /t
char *c_entab(char *s, const int space_for_tab, const int buff_size) {

  if (s == NULL || c_is_empty_string(s)) {
    return s;
  }

  // TODO: remove VLA on stack make alloc array
  char result_string[buff_size];

  const int str_len = c_strlen(s);
  int write_index = 0;

  for (int i = 0; s[i] != '\0';) {
    qboolean is_space_block = TRUE;
    for (int j = 0; j < space_for_tab && j + i < str_len; ++j) {
      if (s[i + j] != ' ') {
        is_space_block = FALSE;
        break;
      }
    }

    if (is_space_block) {
      result_string[write_index++] = '\t';
      i += space_for_tab;
    } else {
      result_string[write_index++] = s[i++];
    }
  }

  result_string[write_index] = '\0';

  c_strcpy(s, result_string);

  return s;
}

// c_detab remove /t and insert n spaces
// c_detab The main disadvantage is that we work only in the original buffer
// (string) and if its size is not enough to store the converted string, the
// function will not work.
char *c_detab(char *s, const int space_for_tab, const int buff_size) {

  if (s == NULL || c_is_empty_string(s)) {
    return s;
  }

  // Find number of tabs
  int number_of_tabs = _c_count_tabs(s);

  if (number_of_tabs == 0) {
    return s;
  }

  // Formula of size new string
  // 1. Find number of chars without tabs
  // 2. Calculate the number of spaces that will replace tabs
  // 3. Result = (1) + (2)
  const int str_len = c_strlen(s);
  const int len_new_string =
      (str_len - number_of_tabs) + (number_of_tabs * space_for_tab);

  if (len_new_string >= buff_size) {
    return s;
  }

  // TODO: remove VLA on stack
  char string_without_tabs[len_new_string + 1];

  int write_index = 0;
  for (int i = 0; s[i] != '\0'; ++i) {
    if (s[i] == '\t') {
      _c_insert_n_spaces(string_without_tabs, space_for_tab, &write_index);
    } else {
      string_without_tabs[write_index++] = s[i];
    }
  }

  string_without_tabs[write_index] = '\0';

  c_strcpy(s, string_without_tabs);

  return s;
}

int c_delete_punctuation(char *s) {

  if (s == NULL) {
    return -1;
  }

  int removed = 0;
  int write_pos = 0;

  for (int i = 0; s[i] != '\0'; ++i) {
    if (!c_is_punct_char(s[i])) {
      s[write_pos++] = s[i];
    } else {
      removed++;
    }
  }

  s[write_pos] = '\0';
  return removed;
}

char *c_reverse(char *s) {

  if (s == NULL) {
    return s;
  }

  int end_index = c_strlen(s) - 1;

  for (int start_index = 0; start_index <= end_index;
       ++start_index, --end_index) {
    _c_swap_char(s + start_index, s + end_index);
  }

  return s;
}

char *c_change_char_all(char *s, const unsigned char from_char,
                        const unsigned char to_char) {

  if (s == NULL) {
    return s;
  }

  for (int i = 0; s[i] != '\0'; ++i) {
    if (s[i] == from_char) {
      s[i] = to_char;
    }
  }

  return s;
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

qboolean c_is_empty_string(const char *s) {

  if (s == NULL) {
    return FALSE;
  }

  return !c_strlen(s);
}

qboolean c_is_string_of_digits(const char *s) {

  if (s == NULL || c_is_empty_string(s)) {
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

int c_index_of_char(const char *s, const unsigned char c) {

  if (s == NULL || c == '\0') {
    return -1;
  }

  for (int i = 0; s[i] != '\0'; ++i) {
    if (s[i] == c) {
      return i;
    }
  }

  return -1;
}

char *c_delete_duplicates(char *s) {

  if (s == NULL) {
    return s;
  }

  int count[ASCII_SIZE] = {0};

  for (int i = 0; s[i] != '\0'; ++i) {
    count[(unsigned char)s[i]]++;
  }

  int pos = 0;
  for (int i = 0; s[i] != '\0'; ++i) {
    if (count[(unsigned char)s[i]] > 0) {
      s[pos++] = s[i];
      count[(unsigned char)s[i]] = 0;
    }
  }

  s[pos] = '\0';

  return s;
}

qboolean c_is_palindrom(const char *s) {

  if (s == NULL || c_is_empty_string(s)) {
    return FALSE;
  }

  const int len_str = c_strlen(s);

  if (len_str == 1) {
    return TRUE;
  }

  int end_index = len_str - 1;
  int start_index = 0;

  while (start_index < end_index) {
    if (c_letter_to_lower(s[start_index]) != c_letter_to_lower(s[end_index])) {
      return FALSE;
    }
    start_index++;
    end_index--;
  }

  return TRUE;
}

char *c_sort_chars(char *s) { return _c_sort_str_chars(s); }

int c_first_unique_char(const char *s) {

  if (s == NULL) {
    return -1;
  }

  char count[ASCII_SIZE] = {0};

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

qboolean c_is_digit(const unsigned char c) { return (c >= '0' && c <= '9'); }

qboolean c_is_punct_char(const unsigned char c) {
  return ((c >= '!' && c <= '/') || (c >= ':' && c <= '@') ||
          (c >= '[' && c <= '`') || (c >= '{' && c <= '~'));
}

qboolean c_is_space(const unsigned char c) {
  return c == ' ' || c == '\t' || c == '\n' || c == '\r' || c == '\v' ||
         c == '\f';
}

qboolean c_is_letter(const unsigned char c) {
  return ((c >= LOWER_LETTER_START && c <= LOWER_LETTER_END) ||
          (c >= UPPER_LETTER_START && c <= UPPER_LETTER_END))
             ? TRUE
             : FALSE;
}

char *c_trim(char *s) {

  if (s == NULL || c_is_empty_string(s)) {
    return s;
  }

  // Start index begin with first not space char
  // End index start with last not space char
  int start_index = 0;
  int end_index = c_strlen(s) - 1;

  while (c_is_space(s[start_index])) {
    ++start_index;
  }

  while (end_index >= start_index && c_is_space(s[end_index])) {
    --end_index;
  }

  if (start_index > end_index) {
    s[0] = '\0';
    return s;
  }

  int write_index = 0;
  for (; start_index <= end_index; ++start_index) {
    s[write_index++] = s[start_index];
  }

  s[write_index] = '\0';

  return s;
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

  if (s == NULL || substr == NULL) {
    return -1;
  }

  if (c_is_empty_string(s) || c_is_empty_string(substr)) {
    return -1;
  }

  int str_len = c_strlen(s);
  int substr_len = c_strlen(substr);

  for (int i = 0; i <= str_len - substr_len; ++i) {
    int j = 0;
    while (j < substr_len && s[i + j] == substr[j]) {
      ++j;
    }

    if (j == substr_len) {
      return i;
    }
  }
  return -1;
}

int c_num_substr(const char *s, const char *substr) {

  if (s == NULL || substr == NULL) {
    return -1;
  }

  if (c_is_empty_string(s) || c_is_empty_string(substr)) {
    return 0;
  }

  int count = 0;
  int i = 0;

  while (s[i] != '\0') {
    int match_pos = c_strstr(s + i, substr);
    if (match_pos < 0) {
      break;
    }
    count++;
    i += match_pos + 1;
  }

  return count;
}

// Size substr_new must be same as substr_old
void c_str_overwrite_first(char *s, const char *substr_old,
                           const char *substr_new, const int buff_size) {

  if (s == NULL || substr_old == NULL || substr_new == NULL) {
    return;
  }

  if (c_is_empty_string(s) || c_is_empty_string(substr_old) ||
      c_is_empty_string(substr_new)) {
    return;
  }

  const int STRSTR_RES = c_strstr(s, substr_old);

  if (STRSTR_RES >= 0) {
    c_overwrite_from(s, substr_new, STRSTR_RES, buff_size);
  }
}

// Size substr_new must be same as substr_old
char *c_str_replace_all(char *s, const char *substr_old,
                        const char *substr_new) {

  if (s == NULL) {
    return s;
  }

  const int SUBSTR_LEN = c_strlen(substr_old);
  const int STR_LEN = c_strlen(s);

  for (int i = 0; i < STR_LEN; i += SUBSTR_LEN) {
    c_str_replace_first(s + i, substr_old, substr_new);
  }

  return s;
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

  if (s1 == NULL || s2 == NULL) {
    return FALSE;
  }

  const int s1_len = c_strlen(s1);
  const int s2_len = c_strlen(s2);

  if (s1_len != s2_len || s1_len == 0) {
    return FALSE;
  }

  int count[ASCII_SIZE] = {0};

  for (int i = 0; s1[i] != '\0'; ++i) {
    unsigned char c = c_letter_to_lower(s1[i]);
    count[c]++;
  }

  for (int i = 0; s2[i] != '\0'; ++i) {
    unsigned char c = c_letter_to_lower(s2[i]);
    count[c]--;
  }

  for (int i = 0; i < ASCII_SIZE; ++i) {
    if (count[i] != 0) {
      return FALSE;
    }
  }

  return TRUE;
}

int c_atoi(const char *s) {

  // c_atoi don't process NULL and empty str
  /*
  if (s == NULL || c_is_empty_string(s)) {
    return 0;
  }
  */

  int res = 0;
  int i = 0;
  qboolean is_negative = FALSE;

  if (s[i] == '-') {
    i++;
    is_negative = TRUE;
  }

  for (; s[i] != '\0' && c_is_digit(s[i]); ++i) {
    res = (res * 10) + (s[i] - '0');
  }

  return is_negative ? -res : res;
}

// Required: s must have enough size for num
char *c_itoa(const int num, char *s) {

  if (s == NULL) {
    return s;
  }

  qboolean is_negative = (num < 0);
  int copy_num = (is_negative) ? -num : num;
  int delim = 10;
  int i = 0;

  do {
    int tmp = copy_num % delim;
    s[i] = tmp + '0';
    ++i;

  } while (copy_num /= delim);

  if (is_negative) {
    s[i++] = '-';
  }

  c_reverse(s);

  s[i] = '\0';

  return s;
}
