cmake_minimum_required(VERSION 2.6)
project(clog C)
set(CMAKE_PLATFORM_ROOT_BIN $ {
    CMAKE_PLATFORM_INFO_DIR
})

set(CMAKE_C_FLAGS "-O3 -Werror -Wconversion -Wall -std=c11 -pedantic")

include_directories(/usr/local/include)
link_directories(/usr/local/lib /usr/lib /usr/X11R6/lib)

add_library(clog SHARED main.c)

if (BUILD_EXAMPLE)
  add_executable(example example.c)
  target_link_libraries(example clog)
endif()
