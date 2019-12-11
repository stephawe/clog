/*
CLOG logging library
 
Copyright (C) 2019 Stephane Weiss

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <https://www.gnu.org/licenses/>.
*/

#pragma once

#include <stdio.h>
#include <string.h>
#include <time.h>

#ifndef MAX_CONFIG
#define MAX_CONFIG 3
#endif

#define LOG(a, ...) \
  CLOG_log((a), __FILE__, __LINE__, __VA_ARGS__);

#define DEBUG(...) LOG("D", __VA_ARGS__)
#define INFO(...) LOG("I", __VA_ARGS__)
#define WARNING(...) LOG("W", __VA_ARGS__)
#define ERROR(...) LOG("E", __VA_ARGS__)
#define FATAL(...) LOG("F", __VA_ARGS__)

#define LVL_DEBUG    1
#define LVL_ERROR    2
#define LVL_FATAL    4
#define LVL_INFO     8
#define LVL_WARNING 16

#ifdef __cplusplus
extern "C" {
#endif

  struct CLOG_config {
    FILE *out;
    char levels;
    int _id;
  };

  void CLOG_init();
  int CLOG_add(const struct CLOG_config *config);
  void CLOG_remove(int idx);

  void CLOG_log(const char *level, const char *filename, int line, const char *msg, ...);

#ifdef __cplusplus
}
#endif
