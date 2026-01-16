#ifndef ZCALC_token_h
#define ZCALC_token_h

#include "iparse.h"
#include <stddef.h>
#include <stdint.h>

typedef enum _ZTokenType {
  ZTOKEN_TYPE_LPAR = 1,
  ZTOKEN_TYPE_RPAR,
  ZTOKEN_TYPE_OP,
  ZTOKEN_TYPE_ZNUMBER
} ZTokenType;

typedef enum _ZAssociativeType {
  ZASSOCIATIVE_LEFT = 1,
  ZASSOCIATIVE_RIGHT,
  ZASSOCIATIVE_UNKNOWN,
} ZAssociativeType;

typedef enum _ZTokenResult {
  ZTOKEN_OK = 0,
  ZTOKEN_NONMEMORY,
  ZTOKEN_ALREADY_FREED,
  ZTOKEN_NOBUFFER,
  ZTOKEN_INVALID,
} ZTokenResult;

typedef struct _ZOperator {
  ZAssociativeType assoc;
  uint8_t precedence;
  char value;
} ZOperator;

typedef struct _ZToken {
  union {
    ZOperator op;
    ZNumber number;
  } tok;
  ZTokenType type;
} ZToken;

/**
 * A function that tokenize a string input
 */
ZTokenResult ZToken_Tokenize(const char *input, ZToken **tokens, size_t *tok_counter);
/**
 * A function that free tokens
 */
ZTokenResult ZToken_Free(ZToken **tokens);

#endif
