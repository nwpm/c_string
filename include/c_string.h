#ifndef C_STRING_H
#define C_STRING_H

int c_strlen(const char s[]);
int c_strcmp(const char first[], const char second[]);
int c_remove_digits(char s[]);
int c_is_string_of_digits(const char s[]);
int c_is_palindrom(const char s[]);
int c_count_words(const char s[]);
int c_is_char_in_string(const char s[], const char chr);
int c_first_unique_char(const char s[]);

int c_is_punct_char(const char c);
int c_is_letter(const char c);
int c_is_digit(const char c);
int c_is_space(const char c);
int c_is_tab(const char c);
int c_is_empty_string(const char s[]);

void c_delete_duplicates(char s[]);
void c_delete_spaces(char s[]);
void c_strcpy(char to[], const char from[]);
void c_to_lower(char s[]);
void c_to_upper(char s[]);
void c_strcat(char to[], char from[]);
void c_change_char_to(char s[], const char from_char, const char to_char);
void c_invert_symbols(char s[]);
void c_trim(char s[]);
void c_reverse(char s[]);
void c_delete_punctuation(char s[]);
void c_sort_chars(char s[]);
void c_detab(char s[], const int space_for_tab);
void c_entab(char s[], const int space_for_tab);

/////

int c_insert_substr_from(char *to, const char *substr, int *insert_from);

void c_strtok(char s[], char **result, const char delim);
void c_reverse_word_order(char s[], const char delim);
void c_sort_words(char s[]);
void c_delete_word_duplicate(char s[]);

#endif // !C_STRING_H
