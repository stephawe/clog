CLOG logging library
====================

Simple logging library for C/C++

* Parameter formatting based on printf
* Several levels of logging: DEBUG, INFO, WARNING, ERROR and FATAL
* Possibility to configure several outputs
* Define which levels are written to which output

License GPL-v3.0

Build
-----

To build the library, run the commands from root of the repository

```bash
mkdir build
cd build
cmake ..
make
```

To build the library and the example

```bash
mkdir build
cd build
cmake _DBUILD_EXAMPLE=true ..
make
```

Usage
-----

As a minimal example, consider the following file `test.c`:
```C
#include "clog.h"

int main(int argc, char **argv) {
  struct CLOG_config conf = {
    .out = stdout,
    .levels = LVL_ERROR | LVL_FATAL
  }; 
  CLOG_init();
  CLOG_add(&conf);
  ERROR("%d error has occured: %s", 1, "message");
  return 0;
}
```

Make sure to copy the header file `clog.h` in the same directory as this source file.
Then compile it with, for example, clang:

`clang test.c -lclog -o test`
