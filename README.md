# dts
A header-only library that adds generic data structures to the C programming language

## Overview
The objective of the dts library is to provide commonly used data structures and allow programmers to easily work with them, these constructs are generic and should work with any other type.

The library currently supports:
- arrays
- dynamic arrays
- linked lists
- trees

Before using, take this into consideration:
- The library is written using C99 features and does not aim to be campatible with any standard that came before it.
- The library was not written with strict-aliasing rules in mind, it may violate them to implement certain features, so a flag such as **-fno-strict-aliasing** should be used when compiling code that uses the library.
## Usage
To use dts you need to define some flags to enable the features that you want to use and after that you just need to #include the header file.

These are the flags: 
```C
// FLAG_NAME         FEATURE
DTS_USE_ARRAY     // array
DTS_USE_DYNARRAY  // dynarray (dynamic array)
DTS_USE_LIST      // list (linked list)
DTS_USE_TREE      // tree
```
For example if we want to use arrays and lists, we do something like this:
```C
#define DTS_USE_ARRAY
#define DTS_USE_LIST
#include "dts.h"
```

## License
[MIT License](https://choosealicense.com/licenses/mit/)
