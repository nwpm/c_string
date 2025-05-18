#ifndef C_STRING_H
#define C_STRING_H

#include "../src/internal/_c_common.h"

int c_strlen(const char *s);
int c_strcmp(const char *first, const char *second);
int c_strcmp_safe(const char *first, const char *second);
int c_remove_digits(char *s);
int c_first_unique_char(const char *s);
int c_strstr(const char *s, const char *substr);
int c_num_substr(const char *s, const char *substr);
int c_atoi(const char *s);
int c_atoi_safe(const char *s);
int c_delete_spaces(char *s);
int c_delete_punctuation(char *s);
int c_index_of_char(const char *s, unsigned char c);
int c_count_words_delim(const char *s, unsigned char delim);

qboolean c_is_palindrom(const char *s);
qboolean c_is_string_of_digits(const char *s);
qboolean c_is_punct_char(unsigned char c);
qboolean c_is_letter(unsigned char c);
qboolean c_is_digit(unsigned char c);
qboolean c_is_space(unsigned char c);
qboolean c_is_empty_string(const char *s);
qboolean c_is_anagrams(const char *s1, const char *s2);
qboolean c_is_upper_letter(const unsigned char c);
qboolean c_is_lower_letter(const unsigned char c);

char c_letter_to_lower(unsigned char c);
char c_letter_to_upper(unsigned char c);

char *c_strcpy(char *dest, const char *from);
char *c_strcpy_safe(char *dest, const char *from, int dest_buff_size);
char *c_str_to_lower(char *s);
char *c_str_to_upper(char *s);
char *c_invert_symbols(char *s);
char *c_reverse(char *s);
char *c_change_char_all(char *s, unsigned char from_char,
                        unsigned char to_char);
char *c_delete_duplicates(char *s);
char *c_strcat(char *dest, const char *from);
char *c_trim(char *s);
char *c_overwrite_from(char *dest, const char *substr, int insert_from,
                       int buff_size);
char *c_itoa(int num, char *s);

#endif // !C_STRING_H
