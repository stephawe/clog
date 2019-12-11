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

#include "clog.h"
#include <assert.h>
#include <stdarg.h>
#include <sys/time.h>

static struct CLOG_config configs[MAX_CONFIG];
static short int n_configs;
static int n_size;

static const char *basename(const char *filename) {
  const char *p = strrchr(filename, '/');
  return p ?  p + 1 : filename;
}

static char to_lvl(const char *c) {
  switch(*c) {
    case 'D':
      return LVL_DEBUG;
    case 'E':
      return LVL_ERROR;
    case 'F':
      return LVL_FATAL;
    case 'I':
      return LVL_INFO;
    case 'W':
      return LVL_WARNING;
    default:
      return 0;
  }
}

void CLOG_log(const char *level, const char *filename, int line, const char *fmt, ...) {
  struct timeval now;
  char now_s[50];

  gettimeofday(&now, NULL);
  strftime(now_s, sizeof(now_s), "%F %T", gmtime(&now.tv_sec));
  snprintf(now_s + strlen(now_s), 50 - strlen(now_s), ".%.06ld", now.tv_usec);

  for (int i=0; i < n_configs; i++) {
    if (configs[i].levels & to_lvl(level)) {
      va_list args;
      va_start(args, fmt);
      fprintf(configs[i].out, "{%s}[%s] %s:%d ", level, now_s, basename(filename), line);
      vfprintf(configs[i].out, fmt, args);
      fprintf(configs[i].out, "\n");
      fflush(configs[i].out);
      va_end(args);
    }
  }
}

void CLOG_init() {
  n_configs = 0;
  n_size = 0;
}

int find_free() {
  if (n_size == MAX_CONFIG) return -1;
  return n_size;
}

int find_conf(int id) {
  for(int i = 0; i < n_size; i++) {
    if (configs[i]._id == id) return i;
  }
  return -1;
}

int CLOG_add(const struct CLOG_config *config) {
  int idx = find_free();
  if (idx == -1) {
    return -1;
  }
  configs[idx] = *config;
  configs[idx]._id = n_configs;
  n_configs++;
  n_size++;
  return configs[n_configs]._id;
}

void CLOG_remove(int id) {
  int idx = find_conf(id);
  if (idx == -1) {
    return;
  }
  configs[idx] = configs[n_size - 1];
  n_size--;
}
