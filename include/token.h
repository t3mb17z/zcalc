#ifndef ZCALC_token_h
#define ZCALC_token_h

#include "iparse.h"

typedef enum _ZTokenType {
  ZTOKEN_TYPE_LPAR,
  ZTOKEN_TYPE_RPAR,
  ZTOKEN_TYPE_OP,
  ZTOKEN_TYPE_DIGIT
} ZTokenType;

typedef enum _ZTokenResult {
  ZTOKEN_OK = 0,
  ZTOKEN_NONMEMORY,
} ZTokenResult;

typedef struct _ZToken {
  ZTokenType type;
  union {
    char op;
    ZNumber number;
  } tok;
} ZToken;

/**
 * A function that tokenize a string input
 */
ZTokenResult ZToken_Tokenize(const char *input, ZToken ***tokens);

#endif
