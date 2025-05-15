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
int c_delete_spaces(char *s);
int c_delete_punctuation(char *s);
int c_index_of_char(const char *s, const unsigned char c);

qboolean c_is_palindrom(const char *s);
qboolean c_is_string_of_digits(const char *s);
qboolean c_is_punct_char(const unsigned char c);
qboolean c_is_letter(const unsigned char c);
qboolean c_is_digit(const unsigned char c);
qboolean c_is_space(const unsigned char c);
qboolean c_is_empty_string(const char *s);
qboolean c_is_anagrams(const char *s1, const char *s2);
qboolean c_is_upper_letter(const unsigned char c);
qboolean c_is_lower_letter(const unsigned char c);

char c_letter_to_lower(unsigned char c);
char c_letter_to_upper(unsigned char c);

char *c_strcpy(char *to, const char *from);
char *c_str_to_lower(char *s);
char *c_str_to_upper(char *s);
char *c_invert_symbols(char *s);
char *c_reverse(char *s);
char *c_change_char_all(char *s, const unsigned char from_char,
                        const unsigned char to_char);
char *c_delete_duplicates(char *s);
char *c_sort_chars(char *s);
char *c_strcat(char *dest, const char *from, const int dest_buff_size);
char *c_trim(char *s);
char *c_detab(char *s, const int space_for_tab, const int buff_size);
char *c_entab(char *s, const int space_for_tab, const int buff_size);
char *c_overwrite_from(char *dest, const char *substr, const int insert_from,
                       const int buff_size);

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
