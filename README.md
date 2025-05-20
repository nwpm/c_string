# c_string

## Description

'c_string' - This is a small library written in C language,
providing various functions for working with strings.
It was written for educational purposes,
to study the basics of development in C language.

**Key features**

Exists in two versions:

- Version with stdlib.h (`use-stdlib-memory` branch)
- Version that does not use any dependencies (`master` branch)

## Possibilities

- Copying and comparing strings (`c_strcpy`, `c_strcmp`, etc.)
- Splitting a string by character (`c_split_delim`)
- Searching for a substring (`c_strstr`)
- Converting a number to a string and forward (`c_itoa`, `c_atoi`)
- Working with substrings and replacing substrings (`c_str_replace_first`)
- Wrappers with checks and safe work with buffers

## Project structure

- src/ # Main library code
- include/ # Header files
- tests/ # Tests and Unity framework
- examples/ # Examples of using lib
- Makefile # Project build
- README.md

## Setup

### Requirements

- **C compiler** with support for the **C99** standard (e.g. `gcc`, `clang`)
- **GNU Make**
- **Linux** — the main target platform
  (on other OSes the project may require some work)

### Steps

1. Clone repository

   ```bash
   git clone https://github.com/nwpm/c_string.git

   ```

2. Build lib

   ```bash
   #lib
   make debug   #build lib in debug version
   make release #build lib in release version

   make install   #install lib in /usr/local/lib/
   make uninstall #uninstall lib from /usr/local/lib/

   ./bin/debug/libcstring_tests #run
   ```

## License

MIT License [LICENSE](https://github.com/nwpm/c_string/blob/master/LICENSE.md)
