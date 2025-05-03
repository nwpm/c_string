#ifndef _STR_INTERNAL_H
#define _STR_INTERNAL_H

static const int LOWER_LETTER_START = 97;
static const int LOWER_LETTER_END = 122;

static const int UPPER_LETTER_START = 65;
static const int UPPER_LETTER_END = 90;

static const int TRUE = 1;
static const int FALSE = 0;

static const int STR_END_SYMBOL = 1;

static const int DIFFERENCE_LETTERS_SIZE = 32;

static const char END_SYMBOL = '\0';

enum _operation_type { PLUS = 1, MINUS = 2 };

int _c_compare_symbols(const char first[], const char second[], int min_length);
int _c_count_tabs(char s[]);
int _c_get_size_arr2d(const int cols, char (*arr_words)[cols]);

void _c_delete_from_str(char s[], int expression_res);
void _c_init_char_arr(char s[], char init_by, const int arr_size);
void _c_init_char_arr2d(char init_by, const int rows, const int cols,
                        char (*arr_words)[cols]);
void _c_get_arr_of_words(const int cols, char (*arr_words)[cols],
                         const char s[]);
void _c_get_words_arr_by_delim(const int cols, char (*arr_words)[cols],
                               const char s[], const char delim);
void _c_swap_char(char *c1, char *c2);
void _c_insert_char_sort(char s[]);
void _c_init_char_arr2d(char init_by, const int rows, const int cols,
                        char (*arr_words)[cols]);
void _c_change_letter_size(char s[], int bottom_border, int upper_border,
                           enum _operation_type operation);

void _c_insert_n_spaces(char s[], const int num_spaces, int *insert_from);

int _c_is_string_of_spaces(char *s);

void _c_delete_duplicate_str_arr2d(const int rows, const int cols,
                                   char (*arr_words)[cols]);

void _sort_words_arr2d(const int rows, const int cols, char (*arr_words)[cols]);

#endif // !_STR_INTERNAL_H
