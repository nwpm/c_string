#ifndef C_STRING_H
#define C_STRING_H

const int lower_start = 97;
const int lower_end = 122;

const int upper_start = 65;
const int upper_end = 90;

const int difference_letters_size = 32;

enum _operation_type { PLUS = 1, MINUS = 2 };

void _c_change_letter_size(char s[], int bottom_border, int upper_border,
                           enum _operation_type operation);

void _c_delete_from_str(char s[], int expression_res);

int _c_compare_symbols(const char first[], const char second[], int min_length);

void _c_get_words_array(char **arr, char s[]); // !

// 14,17,18
int c_strlen(const char s[]);
int c_strcpy(char to[], const char from[]);
int c_strcmp(const char first[], const char second[]);
int c_to_lower(char s[]);
int c_to_upper(char s[]);
int c_count_symbols(const char s[]);
int c_remove_numbers(char s[]);
int c_count_words(char s[]); // !
int c_is_string_of_digits(char s[]);
int c_delete_duplicates(char s[]);
int c_is_symbol_in_string(char s[], char chr);
int c_is_palindrom(char s[]);

char c_first_unique_symbol(char s[]);

void c_invert_symbols(char s[]);
void c_delete_spaces(char s[]);
void c_delete_punctuation(char s[]);
void c_reverse(char s[]);
void c_change_symbol_to(char s[], char remove_char, char add_char);

int get_line(char s[], int length);

void detab(char s[]);
void correct_string(char s[], int length);

#endif // !C_STRING_H
