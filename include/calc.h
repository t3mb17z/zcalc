#ifndef Z_calc_h
#define Z_calc_h

#include "iparse.h"
#include "token.h"

typedef enum _ZOperType {
  ZOPER_TYPE_ADD = 43,
  ZOPER_TYPE_SUBS = 45,
  ZOPER_TYPE_MUL = 42,
  ZOPER_TYPE_DIV = 47,
  ZOPER_TYPE_POW = 94,
  ZOPER_TYPE_FACT = 33,
} ZOperType;

ZTokenResult ZToken_to_rpn(ZToken *tokens, size_t size);
ZTokenResult Zperform_oper(ZNumber a, ZNumber b, ZOperType oper_type, ZNumber *buf);
ZNumber Zeval_rpn(ZToken *list, size_t size);

#endif
