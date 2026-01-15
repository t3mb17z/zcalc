#include <stdbool.h>
#include <stdlib.h>
#include <errno.h>

#include "iparse.h"

inline bool Zis_digit(char chr) {
  return (chr >= '0' && chr <= '9');
}

ZNumber Zchar_to_number(char chr) {
  return (ZNumber)chr - '0';
}

ZNumber Zstr_to_number(const char *number) {
  ZNumber result = 0;

  const char *ptemp = number;

  if(!*ptemp) {
    errno = ZNUMBER_NONUMBER;
    result = 0.0; return result;
  }

  bool last_was_dot = false;
  char dot_count = 0;
  if(*ptemp == '-') ptemp++;
  if(*ptemp == '.') {
    errno = ZNUMBER_PREPERIOD;
    result = 0.0; return result;
  }
  while(*ptemp) {

    if(*ptemp == '.') {
      ptemp++, last_was_dot = true;
      if(++dot_count > 1) {
        errno = ZNUMBER_MULTIPERIOD;
        result = 0.0; return result;
      }
      continue;
    } else
      last_was_dot = false;

    if(*ptemp == '-') {
      errno = ZNUMBER_DOUBLE_NEGATIVE;
      result = 0.0; return result;
    }

    if(Zis_digit(*ptemp)) {
      ptemp++;
      continue;
    } else {
      errno = ZNUMBER_NONDIGIT;
      result = 0.0; return result;
    }

  }

  if(last_was_dot) {
    errno = ZNUMBER_UNTERMINATED;
    result = 0.0; return result;
  }

  result = strtold(number, NULL);
  errno = ZNUMBER_OK;

  return result;
}
