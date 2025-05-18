#ifndef _STR_INTERNAL_H
#define _STR_INTERNAL_H

#include "_c_common.h"

int _c_count_tabs(const char *s);
int _c_count_spaces(const char *s);

void _c_swap_char(char *c1, char *c2);
void _c_insert_n_spaces(char s[], const int num_spaces, int *insert_from);

#endif // !_STR_INTERNAL_H
