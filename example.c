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

int main(int argc, char **argv) {
  FILE *f = fopen("test.log", "w");
  if (!f) {
    perror("Failed to open");
  }
  struct CLOG_config conf = {
    .out = stdout,
    .levels = LVL_DEBUG | LVL_FATAL
  };
  struct CLOG_config file_conf = {
    .out = f,
    .levels = LVL_FATAL | LVL_WARNING | LVL_INFO
  };
  CLOG_init();
  CLOG_add(&conf);
  CLOG_add(&file_conf);
  DEBUG("Debug log without no param");
  WARNING("The parameter: %s", "test");
  INFO("Multiple parameters: string %s, integer %d", "test", 12);
  FATAL("Fatal error: %s", "test message");
  return 0;
}
