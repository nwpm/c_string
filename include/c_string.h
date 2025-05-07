#ifndef C_STRING_H
#define C_STRING_H

#include "../src/internal/_c_common.h"

int c_strlen(const char *s);
int c_strcmp(const char *first, const char *second);
int c_remove_digits(char *s);
int c_count_words(const char *s);
int c_first_unique_char(const char *s);
int c_strstr(const char *s, const char *substr);
int c_num_substr(const char *s, const char *substr);
int c_atoi(const char *s);

qboolean c_is_palindrom(const char *s);
qboolean c_is_string_of_digits(const char *s);
qboolean c_is_punct_char(const char c);
qboolean c_is_letter(const char c);
qboolean c_is_digit(const char c);
qboolean c_is_space(const char c);
qboolean c_is_tab(const char c);
qboolean c_is_empty_string(const char *s);
qboolean c_is_char_in_string(const char *s, const char chr);
qboolean c_is_anagrams(const char *s1, const char *s2);
qboolean c_is_upper_letter(const char c);
qboolean c_is_lower_letter(const char c);

char c_letter_to_lower(char c);
char c_letter_to_upper(char c);

void c_delete_duplicates(char *s);
void c_delete_spaces(char *s);
void c_strcpy(char *to, const char *from);
void c_str_to_lower(char *s);
void c_str_to_upper(char *s);
void c_strcat(char *to, char *from);
void c_change_char_all(char *s, const char from_char, const char to_char);
void c_invert_symbols(char *s);
void c_trim(char *s);
void c_reverse(char *s);
void c_delete_punctuation(char *s);
void c_sort_chars(char *s);
void c_detab(char *s, const int space_for_tab);
void c_entab(char *s, const int space_for_tab);
void c_insert_str_from(char *to, const char *substr, const int insert_from);
void c_reverse_word_order(char *s, const char delim);
void c_delete_word_duplicate(char *s);
void c_strtok(char *s, const int cols, char (*result)[cols], const char delim);
void c_sort_words(char *s);
void c_str_replace_first(char *s, const char *substr_old,
                         const char *substr_new);
void c_str_replace_all(char *s, const char *substr_old, const char *substr_new);
void c_str_replace_n(char *s, const char *substr_old, const char *substr_new,
                     const int n);
void c_itoa(const int num, char *s);

#endif // !C_STRING_H
