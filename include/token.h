#ifndef ZCALC_token_h
#define ZCALC_token_h

#include "iparse.h"
#include <stddef.h>

typedef enum _ZTokenType {
  ZTOKEN_TYPE_LPAR,
  ZTOKEN_TYPE_RPAR,
  ZTOKEN_TYPE_OP,
  ZTOKEN_TYPE_DIGIT
} ZTokenType;

typedef enum _ZTokenResult {
  ZTOKEN_OK = 0,
  ZTOKEN_NONMEMORY,
  ZTOKEN_ALREADY_FREED,
} ZTokenResult;

typedef struct _ZToken {
  ZTokenType type;
  union {
    char op;
    ZNumber number;
  } tok;
  size_t count;
} ZToken;

/**
 * A function that tokenize a string input
 */
ZTokenResult ZToken_Tokenize(const char *input, ZToken ***tokens, size_t *tok_counter);
/**
 * A function that free tokens
 */
ZTokenResult ZToken_Free(ZToken **tokens, size_t size);

#endif
