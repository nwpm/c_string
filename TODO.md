#TODO

## Bugs
-[*] c_delete_word_duplicate. Work incorrect
-[] c_first_unique_char have bug

## Features
-[*] c_strtok. Add the execution result to the array
-[] c_sort_words. Add implementation
-[*] c_entab. Add implementation

# Tests
-[] Write test for c_invert_symbols
-[*] Write test for c_delete_spaces
-[] Write test for c_delete_punctuation
-[] Write test for c_reverse
-[*] Write test for c_trim
-[*] Write test for c_detab
-[] Write test for c_reverse_word_order
-[] Write test for c_sort_chars
-[] Tests for c_insert_substr_from


## Refactoring
-[] Replace _c_get_arr_of_words by _c_get_words_arr_by_delim
-[*] c_detab. Simplify
-[*] c_first_unique_char. Simplify
-[] char s[] replace by char *s
-[] Refactor all code

## Done
-[*] Optimize c_strlen, c_strcmp, c_detab, 
     c_change_char_to work for all string // 26.04.2025
-[*] Opimize c_is_palindrome, c_first_unique_char, delete c_count_symbols, refactor c_is_symbol, c_delete_punctuation, tests for c_trim, c_reverse, c_delete_punctuation, c_sort_chars // 30.04.2025

-[*] tests.c() 
      - added tests for c_detab
      - added tests for c_entab
     c_string.c
      - comments for c_detab
      - definition of c_insert_substr_from
      - definition of c_detab
     c_string.h
      - declaration of c_insert_substr_from

// 01.05.2025

-[*] c_string.c  
      -Change c_insert_substr_from. 'to' buffer must have enough space for 'substr'
      -c_reverse_word_order now don't add delim in the end
      -c_delete_word_duplicate added realization
      -c_strtok added realization
      -c_sort_words added realization
     tests.c
      -c_insert_substr_from
      -c_reverse_word_order
     c_string.h
      -added declarations for c_strstr
      - c_num_substr
      - c_atoi
      - c_itoa
// 03.05.2025
     
-[*] c_string.c
      -added realizations for c_strstr, c_num_substr, c_str_replace_first,
       c_str_replace_all , c_str_replace_n, c_is_anagrams
     c_string.h
      -added declarations for c_strstr
      - c_str_replace_first, all , n
      - c_is_anagrams
     _str_internal.h 
      -added declaration for _c_insert_str_from
     _str_internal.c 
      -added definition for _c_insert_str_from
// 04.05.2025

-[*] c_string.c
      -added realizations for c_atoi, c_itoa
// 05.05.2025

-[*] started 2 new, separate branches for memory and optimizations

-[*] _str_internal.h 
     -remove compare_symbols
     -change parametrs for _get_size_arr2d
     _str_internal.c
     -remove compare_symbols
     -new parametr for _get_size_arr2d - rows
     c_string.c
     -refactor c_strlen, c_strcmp, c_remove_digits, c_is_string_of_digits, c_count_words
      c_char_in_string, c_first_unique_char, c_strstr, c_num_substr
     -added new typedef qboolean and added his for c_is_palindrome, c_is_string_of_digits
     _c_common.h
     -separate file for const and typedef
//06.05.2025

-[*] c_stirng.h
     - added qboolean res type for c_is_palindrome, c_is_string_of_digits, c_is_punct_char,
     c_is_letter, c_is_digit, c_is_space, c_is_tab, c_is_empty_string, c_is_char_in_string, c_is_anagrams
     c_string.c 
     - reafctor c_atoi, c_isstring_of_digits, c_is_cahr_in_string, c_is_anagrams, c_delete_duplicates, c_invert_symbols, c_trim
     _str_internal.h
     - delete function _change_letter_size
     - rename _c_insert_char_sort to _c_sort_str_chars
     _str_internal.c
     - delete function _change_letter_size
//07.05.2025





