#include "../include/c_string.h" // better way to include?
#include "internal/_c_common.h"
#include "internal/_str_internal.h"

/*
 * @file c_string.c
 * @brief Source file for c_string lib
 * @author nwpm
 * @date 20.05.2025
*/

/*
  * @brief Return the length of given byte string
  * @param *s - poiner to the null-terminated byte string to be examinated
  * @return The length of the null-terminated byte string or -1 if *s - NULL
  * @example ./examples/c_strlen.c
*/
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

/*
  * @brief Copies the character string pointed to by from,
  * including the null terminator, to the character array 
  * whose first element is pointed to by dest.
  * @param *dest - pointer to the character array to write to
  * @param *from - pointer to the null-terminated byte string to copy from
  * @return Pointer dest or NULL if dest or from is NULL
  * @warning UB if size of dest not enough for from
  * @example ./examples/c_strcpy.c
*/
char *c_strcpy(char *dest, const char *from) {

  if(dest == NULL || from == NULL){
    return NULL;
  }

  int i = 0;
  while ((dest[i] = from[i]) != '\0') {
    ++i;
  }

  return dest;
}

/*
  * @brief Copies the character string pointed to by from, 
  * including the null terminator, to the character array whose 
  * first element is pointed to by dest.
  * @param *dest - pointer to the character array to write to
  * @param *from - pointer to the null-terminated byte string to copy from
  * @param dest_buff_size - size of array dest
  * @return Pointer dest or NULL if dest or from is NULL, or dest_buff_size <= 0
  * @note Checks if the size of the character array dest is sufficient for the string from.
  * @example ./examples/c_strcpy_safe.c
*/
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

/*
  * @brief Appends a copy of the character string pointed to by from to the end
  * of the character string pointed to by dest. 
  * The character from[0] replaces the null terminator at the end of dest. 
  * The resulting byte string is null-terminated.
  * @param *dest - pointer to the character array to append to
  * @param *from - pointer to the null-terminated byte string to append from
  * @return Pointer dest or NULL if dest or from is NULL, or dest == from
  * @note Size of dest array must be no less than dest + from len
  * @example ./examples/c_strcat.c
*/
char *c_strcat(char *dest, const char *from) {

  if (dest == NULL || from == NULL || dest == from) {
    return NULL;
  }

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

/*
  * @brief Changes the case of the input string to lowercase
  * @param *s - pointer to the character array being edited
  * @return Pointer s or NULL if s is NULL
  * @example ./examples/c_str_to_lower.c
*/
char *c_str_to_lower(char *s) {

  if (s == NULL) {
    return s;
  }

  for (int i = 0; s[i] != '\0'; ++i) {
    s[i] = c_is_upper_letter(s[i]) ? c_letter_to_lower(s[i]) : s[i];
  }

  return s;
}

/*
  * @brief Changes the case of the input string to uppercase
  * @param *s - pointer to the character array being edited
  * @return Pointer s or NULL if s is NULL
  * @example ./examples/c_str_to_upper.c
*/
char *c_str_to_upper(char *s) {

  if (s == NULL) {
    return s;
  }

  for (int i = 0; s[i] != '\0'; ++i) {
    s[i] = c_is_lower_letter(s[i]) ? c_letter_to_upper(s[i]) : s[i];
  }

  return s;
}

/*
  * @brief Compares two null-terminated byte strings lexicographically.
  * @details The sign of the result is the sign of the difference between 
  * the values of the first pair of characters that differ in the strings being compared.
  * @param *first - pointer to the null-terminated byte string to compare
  * @param *second - pointer to the null-terminated byte string to compare
  * @return Negative value - if the first appears before second in lexicographicalorder. 
  * Positive value - if first appears after second in lexicographical order.
  * Zero - if first and second equal
  * @warning UB if pointers of fisrt and second are not
  * null-terminated strings
  * @example ./examples/c_strcmp.c
*/
int c_strcmp(const char *first, const char *second) {
  while (*first && (*first == *second)) {
    ++first;
    ++second;
  }
  return *first - *second;
}

/*
  * @brief Compares two null-terminated byte strings lexicographically.
  * @details The sign of the result is the sign of the difference between 
  * the values of the first pair of characters that differ in the strings being compared. Have check for NULL pointer
  * @param *first - pointer to the null-terminated byte string to compare
  * @param *second - pointer to the null-terminated byte string to compare
  * @return Negative value - if the first appears before second in lexicographicalorder. If pointer to the first string is NULL return -1.If pointer to the second string is NULL return 1, If both return 0.
  * Positive value - if first appears after second in lexicographical order.
  * Zero - if first and second equal
  * @note Have check for NULL pointers
  * @example ./examples/c_strcmp_safe.c
*/
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

/*
  * @brief Check for lowercase character symbol
  * @param *s - unsigned char for check
  * @return TRUE if char in lowercase, FALSE if not
  * @example ./examples/c_is_lower_letter.c
*/
qboolean c_is_lower_letter(unsigned char c) {
  return (c >= 'a' && c <= 'z');
}

/*
  * @brief Check for uppercase character symbol
  * @param *s - unsigned char for check
  * @return TRUE if char in uppercase, FALSE if not
  * @example ./examples/c_is_upper_letter.c
*/
qboolean c_is_upper_letter(unsigned char c) {
  return (c >= 'A' && c <= 'Z');
}

/*
  * @brief Convert char to the lowercase
  * @param *s - unsigned char for convert
  * @return Lowercase unsigned char
  * @example ./examples/c_letter_to_lower.c
*/
char c_letter_to_lower(unsigned char c) {
  if (c_is_upper_letter(c)) {
    return c += DIFFERENCE_LETTERS_SIZE;
  }
  return c;
}

/*
  * @brief Convert char to the uppercase
  * @param *s - unsigned char for convert
  * @return Uppercase unsigned char
  * @example ./examples/c_letter_to_upper.c
*/
char c_letter_to_upper(unsigned char c) {
  if (c_is_lower_letter(c)) {
    return c -= DIFFERENCE_LETTERS_SIZE;
  }
  return c;
}

/*
  * @brief Invert case of null-terminated string
  * @param *s - pointer to the null-terminated string
  * @return *s - null-terminated string with invert case
  * @example ./examples/c_invert_symbols.c
*/
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

/*
  * @brief Overwrite chars of null_terminated string dest from insert_from index,by chars from null-terminated string substr
  * @param *s - pointer to the null-terminated string
  * @param *substr - pointer to the null-terminated string of writting chars
  * @param insert_from - starting index of dest string from which the overwriting begin
  * @return *s - null-terminated, overwrited string
  * @example ./examples/c_overwrite_from.c
*/
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

/*
  * @brief Removes all spaces from null-terminated string
  * @param *s - pointer to the null-terminated string
  * @return Number of deleted spaces. -1 if string has not spaces
  * @note Have check for NULL pointer
  * @example ./examples/c_delete_spaces.c
*/
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

/*
  * @brief Removes all punctuation chars from null-terminated string
  * @param *s - pointer to the null-terminated string
  * @return Number of deleted spaces. -1 if string has not spaces
  * @note Have check for NULL pointer.
  * @example ./examples/c_delete_punctuation.c
*/
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

/*
  * @brief Reverses the order of chars in null-terminated string
  * @param *s - pointer to the null-terminated string
  * @return Pointer to reversed string. NULL if pointer to the string is NULL
  * @note Have check for NULL pointer.
  * @example ./examples/c_delete_reverse.c
*/
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

/*
  * @brief Remove all digits from null-terminated string
  * @param *s - pointer to the null-terminated string
  * @return Number of removed digits. -1 if string pointer is NULL
  * @note Have check for NULL pointer.
  * @example ./examples/c_remove_digits.c
*/
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

/*
  * @brief Count number of words separated by delim in null-terminated string
  * @param *s - pointer to the null-terminated string
  * @param delim - word separation symbol
  * @return Number of words sepatated by delim in string. -1 if string pointer is NULL
  * @note Have check for NULL pointer.
  * @example ./examples/c_count_words_delim.c
*/
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

/*
  * @brief Check if length of null-terminated string is 0
  * @param *s - pointer to the null-terminated string
  * @return TRUE if length of string is 0 and if pointer "s" is NULL
  * @note Have check for NULL pointer.
  * @example ./examples/c_is_empty_string.c
*/

qboolean c_is_empty_string(const char *s) {

  if (s == NULL) {
    return TRUE;
  }

  return !c_strlen(s);
}

/*
  * @brief Check if all chars in null-terminated string is chars of digits
  * @param *s - pointer to the null-terminated string
  * @return TRUE if all chars in string is digits. FALSE if not, 
  * or pointer "s" is NULL or string is empty.
  * @note Have check for NULL pointer and empty string.
  * @example ./examples/c_delete_reverse.c
*/
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

/*
  * @brief Return index of first char "c"
  * @param *s - pointer to the null-terminated string
  * @param c - ???
  * @return Index
  * @note Have check for NULL pointer.
  * @example ./examples/c_delete_reverse.c
*/
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

/*
  * @brief Remove all duplicated chars in null-terminated string
  * @param *s - pointer to the null-terminated string
  * @return Pointed to the cleaned string. 
  * NULL if pointer to the string is NULL
  * @note Have check for NULL pointer.
  * @example ./examples/c_delete_duplicates.c
*/
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

/*
  * @brief Check if a string is palindrom
  * @param *s - pointer to the null-terminated string
  * @return TRUE if string is palindrome. 
  * FALSE if not palindrome or string pointer is NULL or string is empty
  * @note Have check for NULL pointer.
  * @example ./examples/c_is_palindrom.c
*/
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

/*
  * @brief Return index of first unique char
  * @param *s - pointer to the null-terminated string
  * @return Index of first unique char.
  * -1 if pointer to stirng is NULL
  * @note Have check for NULL pointer.
  * @example ./examples/c_first_unique_char.c
*/
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

/*
  * @brief Checks if char is digit
  * @param c - unsigned char 
  * @return TRUE if char is digit. FALSE if not.
  * @example ./examples/c_is_digit.c
*/
qboolean c_is_digit(unsigned char c) { return (c >= '0' && c <= '9'); }

/*
  * @brief Checks if char is punctuation char
  * @details Punctuation char is char in ASCII table 
  * which start from 33 code, end with 126 code. And excluding codes of digits,
  * upper and lower letters.
  * @param c - unsigned char
  * @return TRUE if "c" is punct char. FALSE if not.
  * @example ./examples/c_is_punct_char.c
*/
qboolean c_is_punct_char(unsigned char c) {
  return ((c >= '!' && c <= '/') || (c >= ':' && c <= '@') ||
          (c >= '[' && c <= '`') || (c >= '{' && c <= '~'));
}

/*
  * @brief Checks if char is space char
  * @param c - unsigned char
  * @return TRUE if "c" is space char. FALSE if not.
  * @example ./examples/c_is_space.c
*/
qboolean c_is_space(unsigned char c) {
  return c == ' ' || c == '\t' || c == '\n' || c == '\r' || c == '\v' ||
         c == '\f';
}

/*
  * @brief Checks if char is letter char
  * @param c - unsigned char
  * @return TRUE if "c" is letter char. FALSE if not.
  * @example ./examples/c_is_letter.c
*/
qboolean c_is_letter(unsigned char c) {
  return ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'));
}

/*
  * @brief Removes spaces from the beginning and end of a string
  * @details Spaces as classified by the currently installed C locale
  * @param *s - pointer to the null-terminated string
  * @example ./examples/c_is_space.c
*/
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
