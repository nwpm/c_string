#ifndef C_STRING_H
#define C_STRING_H

static const int LOWER_LETTER_START = 97;
static const int LOWER_LETTER_END = 122;

static const int UPPER_LETTER_START = 65;
static const int UPPER_LETTER_END = 90;

static const int TRUE = 1;
static const int FALSE = 0;

static const int SIZE_STRING_END = 1;

static const int DIFFERENCE_LETTERS_SIZE = 32;

enum _operation_type { PLUS = 1, MINUS = 2 };

void _c_change_letter_size(char s[], int bottom_border, int upper_border,
                           enum _operation_type operation);

void _c_delete_from_str(char s[], int expression_res);

int _c_compare_symbols(const char first[], const char second[], int min_length);

void _c_get_words_array(char **arr, char s[]); // !

// 14
int c_strlen(const char s[]);
int c_strcmp(const char first[], const char second[]);
int c_count_symbols(const char s[]);
int c_remove_digits(char s[]);
int c_is_string_of_digits(char s[]);
int c_delete_duplicates(char s[]);
int c_is_palindrom(char s[]);

int c_is_symbol(const char c);
int c_is_letter(const char c);
int c_is_digit(const char c);

void c_strcpy(char to[], const char from[]);
void c_to_lower(char s[]);
void c_to_upper(char s[]);
void c_strcat(char to[], char from[]);

void c_entab(char s[], const int space_for_tab);
void detab(char s[], const int space_for_tab);
int c_count_words(char s[]);
// void c_strtok(char s[]);
int c_is_symbol_in_string(char s[], char chr);
int c_first_unique_symbol(char s[]);

int c_is_space(const char c);
int c_is_tab(const char c);
int c_is_empty_string(const char s[]);

void c_invert_symbols(char s[]);
void c_delete_spaces(char s[]);
void c_delete_punctuation(char s[]);
void c_reverse(char s[]);
void c_change_symbol_to(char s[], char remove_char, char add_char);
void c_trim(char s[]);

#endif // !C_STRING_H
