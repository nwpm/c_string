#include "_str_internal.h"
#include "../../include/c_string.h"
#include "_c_common.h"

void _c_swap_char(char *c1, char *c2) {
  char tmp_val = *c1;
  *c1 = *c2;
  *c2 = tmp_val;
}

int _c_count_tabs(char s[]) {

  int number_of_tabs = 0;

  for (int i = 0; s[i] != '\0'; ++i) {
    if (s[i] == '\t') {
      number_of_tabs++;
    }
  }

  return number_of_tabs;
}

void _c_init_char_arr(char s[], char init_by, const int arr_size) {

  s[arr_size] = '\0';

  for (int i = 0; s[i] != '\0'; ++i) {
    s[i] = init_by;
  }
}

void _c_init_char_arr2d(char init_by, const int rows, const int cols,
                        char (*arr_words)[cols]) {
  for (int i = 0; i < rows; ++i) {
    for (int j = 0; j < cols; ++j) {
      arr_words[i][j] = init_by;
    }
  }
}

int _c_get_size_arr2d(const int rows, const int cols, char (*arr_words)[cols]) {
  int result = 0;
  for (int i = 0; i < rows && arr_words[i][0] != '\0'; ++i) {
    result++;
  }
  return result;
}

void _c_get_arr_of_words(const int cols, char (*arr_words)[cols],
                         const char s[]) {
  int in_word = FALSE;
  int words_index = 0;
  int char_index = 0;

  for (int i = 0; s[i] != '\0'; ++i) {
    if (!c_is_letter(s[i]) && in_word) {
      in_word = FALSE;
      arr_words[words_index][char_index] = '\0';
      words_index++;
      char_index = 0;
    } else if (c_is_letter(s[i]) && !in_word) {
      in_word = TRUE;
      arr_words[words_index][char_index++] = s[i];
    } else if (c_is_letter(s[i]) && in_word) {
      arr_words[words_index][char_index++] = s[i];
    }
  }

  // Add '\0' if we stil in word
  if (in_word) {
    arr_words[words_index][char_index] = '\0';
  }
}

// TODO: replace by this _c_get_arr_of_words
void _c_get_words_arr_by_delim(const int cols, char (*arr_words)[cols],
                               const char s[], const char delim) {
  // TODO Make dynamic array_of_words
  int in_word = FALSE;
  int words_index = 0;
  int char_index = 0;

  for (int i = 0; s[i] != '\0'; ++i) {
    if ((s[i] == delim) && in_word) {
      in_word = FALSE;
      arr_words[words_index][char_index] = '\0';
      words_index++;
      char_index = 0;
    } else if ((s[i] != delim) && !in_word) {
      in_word = TRUE;
      arr_words[words_index][char_index++] = s[i];
    } else if ((s[i] != delim) && in_word) {
      arr_words[words_index][char_index++] = s[i];
    }
  }

  if (in_word) {
    arr_words[words_index][char_index] = '\0';
  }
}

char *_c_sort_str_chars(char *s) {

  if (s == NULL || c_is_empty_string(s)) {
    return s;
  }

  for (int j = 1; s[j] != '\0'; ++j) {
    char key = s[j];
    int i = j - 1;
    for (; i >= 0 && s[i] > key; --i) {
      s[i + 1] = s[i];
    }
    s[i + 1] = key;
  }

  return s;
}

void _c_insert_n_spaces(char s[], const int num_spaces, int *insert_from) {
  for (int k = num_spaces; k != 0; --k) {
    s[(*insert_from)++] = ' ';
  }
}

int _c_is_string_of_spaces(char *s) {
  for (int i = 0; s[i] != '\0'; ++i) {
    if (!c_is_space(s[i])) {
      return FALSE;
    }
  }
  return TRUE;
}

void _c_delete_duplicate_str_arr2d(const int rows, const int cols,
                                   char (*arr_words)[cols]) {
  for (int i = 0; i < rows - 1; ++i) {
    for (int j = i + 1; j < rows; ++j) {
      if (c_strcmp(arr_words[i], arr_words[j]) == 0) {
        arr_words[j][0] = '\0';
      }
    }
  }
}

void _sort_words_arr2d(const int rows, const int cols,
                       char (*arr_words)[cols]) {
  for (int i = 1; i < rows; ++i) {
    char key[cols];
    c_strcpy(key, arr_words[i]);
    int j = i - 1;
    while (j >= 0 && c_strcmp(arr_words[j], key) > 0) {
      c_strcpy(arr_words[j + 1], arr_words[j]);
      --j;
    }
    c_strcpy(arr_words[j + 1], key);
  }
}

void _c_insert_str_from(char *s, const char *substr, int *insert_from) {

  for (int i = 0; substr[i] != '\0'; ++i) {
    s[(*insert_from)++] = substr[i];
  }
}
