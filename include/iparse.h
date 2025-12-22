#ifndef Z_iparse_h
#define Z_iparse_h

#include <stdbool.h>

typedef long double ZNumber;

typedef enum _ZNumberResult {
  ZNUMBER_OK = 0,
  ZNUMBER_PREPERIOD,
  ZNUMBER_MULTIPERIOD,
  ZNUMBER_DOUBLE_NEGATIVE,
  ZNUMBER_NONDIGIT,
  ZNUMBER_UNTERMINATED,
  ZNUMBER_NONUMBER,
} ZNumberResult;

ZNumber Zchar_to_number(char chr);
ZNumber Zstr_to_number(const char *str);
bool Zis_digit(char chr);

#endif
