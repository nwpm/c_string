#include "../include/c_string.h" // better way to include?
#include "internal/_c_common.h"
#include "internal/_str_internal.h"
#include <stdlib.h>

void c_free_2d_array(char **array) {

  if (array == NULL) {
    return;
  }

  for (int i = 0; array[i] != NULL; ++i) {
    free(array[i]);
  }

  free(array);
}

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

char *c_strcpy(char *dest, const char *from) {

  int i = 0;
  while ((dest[i] = from[i]) != '\0') {
    ++i;
  }

  return dest;
}

char *c_strcpy_safe(char *dest, const char *from, int dest_buff_size) {

  if (dest == NULL || from == NULL || dest == from || dest_buff_size <= 0) {
    return dest;
  }

  const int from_len = c_strlen(from);

  if (from_len >= dest_buff_size - 1) {
    return NULL;
  }

  return c_strcpy(dest, from);
}

// Required: "dest" string must have size >= to + from
char *c_strcat(char *dest, const char *from) {

  const int from_len = c_strlen(from);
  const int dest_len = c_strlen(dest);

  int start_index = dest_len;
  int end_index = start_index + from_len;
  for (int j = 0; start_index < end_index; ++start_index) {
    dest[start_index] = from[j++];
  }

  dest[start_index] = '\0';

  return dest;
}

// free()
char *c_strcat_safe(const char *dest, const char *from) {

  if (dest == NULL || from == NULL || dest == from) {
    return NULL;
  }

  const int from_len = c_strlen(from);
  const int dest_len = c_strlen(dest);

  const int result_len = from_len + dest_len;

  char *new_string = calloc(result_len + 1, sizeof(char));

  if (new_string == NULL) {
    return NULL;
  }

  int write_pos = 0;

  for (int i = 0; dest[i] != '\0'; ++i) {
    new_string[write_pos++] = dest[i];
  }

  for (int i = 0; from[i] != '\0'; ++i) {
    new_string[write_pos++] = from[i];
  }

  return new_string;
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

int c_strcmp_safe(const char *first, const char *second) {

  if (first == NULL && second == NULL) {
    return 0;
  }

  if (first == NULL) {
    return -1;
  }

  if (second == NULL) {
    return 1;
  }

  return c_strcmp(first, second);
}

qboolean c_is_lower_letter(const unsigned char c) {
  return (c >= 'a' && c <= 'z');
}

qboolean c_is_upper_letter(const unsigned char c) {
  return (c >= 'A' && c <= 'Z');
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

char *c_overwrite_from(char *dest, const char *substr, int insert_from,
                       int buff_size) {

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

// free()
char *c_insert_from(const char *dest, const char *substr, int insert_from) {

  if (dest == NULL || substr == NULL || insert_from < 0) {
    return NULL;
  }

  const int dest_len = c_strlen(dest);
  const int substr_len = c_strlen(substr);

  if (insert_from > dest_len) {
    return NULL;
  }

  const int result_len = dest_len + substr_len;

  char *new_string = calloc(result_len + 1, sizeof(char));

  if (new_string == NULL) {
    return NULL;
  }

  int write_pos = 0;
  int dest_index = 0;

  if (insert_from != 0) {
    for (; dest_index <= insert_from && dest[dest_index] != '\0';
         ++dest_index) {
      new_string[write_pos++] = dest[dest_index];
    }
  }

  for (int i = 0; substr[i] != '\0'; ++i) {
    new_string[write_pos++] = substr[i];
  }

  for (; dest[dest_index] != '\0'; ++dest_index) {
    new_string[write_pos++] = dest[dest_index];
  }

  new_string[write_pos] = '\0';

  return new_string;
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
// Return poiner to allocated result string
// client must call free()
char *c_entab(const char *s, int space_for_tab) {

  if (s == NULL || c_is_empty_string(s) || space_for_tab <= 0) {
    return NULL;
  }

  const int num_spaces = _c_count_spaces(s);

  if (num_spaces < space_for_tab) {
    return NULL;
  }

  const int str_len = c_strlen(s);
  const int num_tabs = num_spaces / space_for_tab;
  const int res_len = num_tabs + (str_len - num_tabs * space_for_tab);

  char *new_string = calloc(res_len + 1, sizeof(char));

  if (new_string == NULL) {
    return NULL;
  }

  int write_index = 0;

  for (int i = 0; s[i] != '\0';) {
    qboolean is_space_block = TRUE;
    int j = 0;
    for (; j < space_for_tab && j + i < str_len; ++j) {
      if (s[i + j] != ' ') {
        is_space_block = FALSE;
        break;
      }
    }

    if (j < space_for_tab) {
      is_space_block = FALSE;
    }

    if (is_space_block) {
      new_string[write_index++] = '\t';
      i += space_for_tab;
    } else {
      new_string[write_index++] = s[i++];
    }
  }

  new_string[write_index] = '\0';

  return new_string;
}

// c_detab remove /t and insert n spaces
// free()
char *c_detab(const char *s, int space_for_tab) {

  if (s == NULL || c_is_empty_string(s) || space_for_tab < 0) {
    return NULL;
  }

  // Find number of tabs
  int number_of_tabs = _c_count_tabs(s);

  if (number_of_tabs == 0) {
    return NULL;
  }

  // Formula of size new string
  // 1. Find number of chars without tabs
  // 2. Calculate the number of spaces that will replace tabs
  // 3. Result = (1) + (2)
  const int str_len = c_strlen(s);
  const int len_new_string =
      (str_len - number_of_tabs) + (number_of_tabs * space_for_tab);

  char *new_string = calloc(len_new_string + 1, sizeof(char));

  if (new_string == NULL) {
    return NULL;
  }

  int write_index = 0;
  for (int i = 0; s[i] != '\0'; ++i) {
    if (s[i] == '\t') {
      _c_insert_n_spaces(new_string, space_for_tab, &write_index);
    } else {
      new_string[write_index++] = s[i];
    }
  }

  new_string[write_index] = '\0';

  return new_string;
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

char *c_change_char_all(char *s, unsigned char from_char,
                        unsigned char to_char) {

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

int c_count_words_delim(const char *s, unsigned char delim) {

  if (s == NULL) {
    return -1;
  }

  int counter = 0;
  qboolean in_word = FALSE;

  for (int i = 0; s[i] != '\0'; ++i) {
    unsigned char c = s[i];
    if (c == delim && in_word) {
      in_word = FALSE;
    } else if (c != delim && !in_word) {
      in_word = TRUE;
      counter++;
    }
  }

  return counter;
}

qboolean c_is_empty_string(const char *s) {

  if (s == NULL) {
    return TRUE;
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

int c_index_of_char(const char *s, unsigned char c) {

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

  return -1;
}

qboolean c_is_digit(unsigned char c) { return (c >= '0' && c <= '9'); }

qboolean c_is_punct_char(unsigned char c) {
  return ((c >= '!' && c <= '/') || (c >= ':' && c <= '@') ||
          (c >= '[' && c <= '`') || (c >= '{' && c <= '~'));
}

qboolean c_is_space(unsigned char c) {
  return c == ' ' || c == '\t' || c == '\n' || c == '\r' || c == '\v' ||
         c == '\f';
}

qboolean c_is_letter(unsigned char c) {
  return ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'));
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

char **c_split_delim(const char *s, unsigned char delim) {

  if (s == NULL || c_is_empty_string(s)) {
    return NULL;
  }

  const int num_words = c_count_words_delim(s, delim);

  if (num_words <= 1) {
    return NULL;
  }

  char **array_of_words = calloc(num_words + 1, sizeof(char *));

  if (array_of_words == NULL) {
    return NULL;
  }

  int str_pos = 0;
  int array_index = 0;

  for (; array_index < num_words; ++array_index) {

    int word_len = 0;
    int word_begin_pos = str_pos;

    // calculate size of one word array
    for (; s[str_pos] != delim && s[str_pos] != '\0'; ++str_pos) {
      word_len++;
    }

    if (word_len == 0) {
      str_pos++;
      break;
    }

    array_of_words[array_index] = calloc(word_len + 1, sizeof(char));

    if (array_of_words[array_index] == NULL) {
      c_free_2d_array(array_of_words);
      return NULL;
    }

    // or memcpy analog
    for (int j = 0; word_begin_pos < str_pos; ++j) {
      array_of_words[array_index][j] = s[word_begin_pos++];
    }

    str_pos++;
  }

  array_of_words[array_index] = NULL;

  return array_of_words;
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

int c_atoi_safe(const char *s) {

  if (s == NULL) {
    return 0;
  }

  return c_atoi(s);
}

// Required: s must have enough size for num
char *c_itoa(int num, char *s) {

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

// free()
char *c_itoa_safe(int num) {

  const int delim = 10;
  int num_copy = num;
  int num_len = 0;

  while (num_copy /= delim) {
    num_len++;
  }

  char *new_string = calloc(num_len + 1, sizeof(char));

  if (new_string == NULL) {
    return NULL;
  }

  c_itoa(num, new_string);

  return new_string;
}
