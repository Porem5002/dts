# dts
A header-only library that adds generic data structures to the C programming language

## Overview
The objective of the dts library is to provide commonly used data structures and allow programmers to easily work with them, these constructs are generic and should work with any other type.

At the moment there is no type checking applied to the internal types of the data structures, but I plan to add some kind of type checking system when the **DTS_DEBUG_CHECKS** flag is enabled. 

The library currently supports:
- arrays
- dynamic arrays (dynarray & bukarray)
- linked lists
- trees

**NOTE:** Tree data structure is not recommended to be used, because it will suffer major changes to its functions and functionality.

Before using, take this into consideration:
- The library is written using C99 features and does not aim to be campatible with any standard that came before it.
- The library was not written with strict-aliasing rules in mind, it may violate them to implement certain features, so a flag such as **-fno-strict-aliasing** should be used when compiling code that uses the library.
## Usage
To use dts you need to define some flags to enable the features that you want to use and after that you just need to #include the header file.

These are the flags: 
```C
// FLAG_NAME         FEATURE
DTS_DEBUG_CHECKS  // Enable debug checks like bounds checking
DTS_USE_ARRAY     // array
DTS_USE_DYNARRAY  // dynarray (dynamic array)
DTS_USE_BUKARRAY  // bukarray (dynamic array)
DTS_USE_LIST      // list (linked list)
DTS_USE_TREE      // tree
```
For example if we want to use arrays and lists, we do something like this:
```C
#define DTS_USE_ARRAY
#define DTS_USE_LIST
#include "dts.h"
```

But if you want to make sure everything is working correctly or run any of the examples provided, you can use [CMake](https://cmake.org/) to build the examples and the tests.

**To do so, follow the following steps:**

Create a new directory called 'build', inside this project's directory
```Bash
mkdir build
cd build
```
Then run the following commands inside that new directory, replacing **(generator of choice)** with the specific generator that better suits your development environment (**"Unix Makefiles"**, **"Visual Studio 17"**, etc...)
```Bash
cmake .. -G (generator of choice)
cmake --build .
```
After this the examples and tests will be built and their executable binaries will be placed in 'build'.

Finally you can run the tests using **ctest**, while inside the 'build' directory:
```Bash
ctest
```

## License
[MIT License](https://choosealicense.com/licenses/mit/)
