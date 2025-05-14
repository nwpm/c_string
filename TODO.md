#TODO

# Bugs
-[] c_first_unique_char fix with stdlib stack-overflow problem

# Features

# Tests


# Refactoring
-[*] different flags for each "part". libunity, libcstring and tests


# Done
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

-[*] Makefile
     - refactor all make file. now we have "3 build"
     libunity, libcstring and tests
     tests.c
     - deleted all simple tests, now all tests will be with
     unity lib.
// 09.05.2025

-[*] Makefile
     - different flags for parts compilation
     c_string.c
     - correct work c_strlen with null parametr
     tests.c
     - c_strlen cases : all 
     - c_strcmp cases : all
     - c_remove_digits : all
     - c_count_words : all
     - c_first_unique_char : all
// 10.05.2025

-[*] tests.c
     - added tests for c_strstr, c_num_substr, c_atoi, c_is_palindrom, 
     c_is_string_of_digits, c_is_punct_char, c_is_letter, c_is_digit
     c_string.h 
     - set parametrs to unsigned char in c_is_punct_char, c_is_letter, c_is_digit, c_is_space
     c_string.c
     - refactor functions c_strstr, c_atoi, c_is_palindrom
// 12.05.2025


-[*] tests.c
     - rework all current tests.
     c_string.c
     - refactor c_delete_spaces, c_str_to_lower, c_str_to_upper, c_is_space, c_is_anagrams, c_invert_symbols.
     delete c_is_tab
// 13.05.2025

-[*] tests.c
     - added tests for c_is_space, c_is_empty_string, c_index_of_char,
     c_is_anagrams, c_is_upper_letter, c_is_lower_letter, c_letter_to_lower, c_letter_to_upper, c_delete_spaces, c_str_to_lower, c_str_to_upper, c_invert_symbols, c_reverse, c_delete_punctuation, c_change_char_all, c_delete_duplicate,
c_strcpy.
     c_string.c
     - c_is_char_in_string now c_index_of_char, c_delete_punctuation now return number of removed chars, c_delete_duplicates refactor, c_strcpy return ptr to "to" string,
     c_string.h
     - c_is_char_in_string change to c_index_of_char, c_delete_punctuation return value int now. c_strcpy, c_str_to_lower, c_str_to_upper, c_invert_symbols,c_reverse, c_change_char_all, c_delete_duplicates, c_sort_chars return value char*















