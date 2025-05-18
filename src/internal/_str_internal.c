#include "_str_internal.h"

void _c_swap_char(char *c1, char *c2) {
  char tmp_val = *c1;
  *c1 = *c2;
  *c2 = tmp_val;
}
