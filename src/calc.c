#include <math.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "calc.h"
#include "datalist/list.h"
#include "datalist/stack.h"
#include "datalist/queue.h"
#include "iparse.h"
#include "token.h"

ZTokenResult ZToken_to_rpn(ZToken *tokens, size_t size) {
  if(tokens == NULL) return ZTOKEN_NOBUFFER;
  if(size < 1) return ZTOKEN_OK;

  ZList output, ops;
  ZToken *temp1 = malloc(sizeof(ZToken));
  ZToken *temp2 = malloc(sizeof(ZToken));
  if(!temp1 || !temp2)
    return ZTOKEN_NONMEMORY;

  ZQueue_new(&output, size, sizeof(ZToken));
  ZStack_new(&ops, size, sizeof(ZToken));

  for(size_t i = 0; i < size; i++) {
    *temp1 = tokens[i];
    if(temp1->type == ZTOKEN_TYPE_ZNUMBER)
      ZQueue_enqueue(&output, temp1);
    else if(temp1->type == ZTOKEN_TYPE_OP) {
      while(!ZList_empty(&ops)) {
        ZStack_peek(&ops, temp2);
        if(
          temp2->type != ZTOKEN_TYPE_LPAR &&
          (
            temp2->tok.op.precedence > temp1->tok.op.precedence ||
            (
              temp2->tok.op.precedence == temp1->tok.op.precedence &&
              temp2->tok.op.assoc == ZASSOCIATIVE_LEFT
            )
          )
        ) {
          ZStack_pop(&ops);
          ZQueue_enqueue(&output, temp2);
        } else break;
      }

      ZStack_push(&ops, temp1);
    } else if(temp1->type == ZTOKEN_TYPE_LPAR)
      ZStack_push(&ops, temp1);
    else if(temp1->type == ZTOKEN_TYPE_RPAR) {
      while(!ZList_empty(&ops)) {
        ZStack_peek(&ops, temp2);
        if(temp2->type == ZTOKEN_TYPE_LPAR) {
          ZStack_pop(&ops);
          break;
        } else {
          ZStack_pop(&ops);
          ZQueue_enqueue(&output, temp2);
        }
      }
    }
  }

  while(ZStack_peek(&ops, temp1) != ZLIST_EMPTY) {
    ZStack_pop(&ops);
    ZQueue_enqueue(&output, temp1);
  }

  free(temp1), free(temp2);
  memcpy(tokens, &output.data[output.head], output.count);
  memset(&tokens[output.count / output.elem_size], 0, output.cap - output.count);
  ZQueue_free(&output);
  ZStack_free(&ops);

  return ZTOKEN_OK;
}

ZNumber Zeval_rpn(ZToken *input, size_t size) {
  ZNumber num = 0;
  ZList output;
  ZStack_new(&output, size, sizeof(ZToken));
  ZToken *temp = malloc(sizeof(ZToken));
  ZToken *a = malloc(sizeof(ZToken));
  ZToken *b = malloc(sizeof(ZToken));
  ZToken *res = malloc(sizeof(ZToken));
  for(size_t i = 0; i < size; i++) {
    *temp = input[i];
    if(temp->type == ZTOKEN_TYPE_ZNUMBER)
      ZStack_push(&output, temp);
    else if(temp->type == ZTOKEN_TYPE_OP) {
      ZStack_pop_into(&output, b);
      if(temp->tok.op.value != '!')
        ZStack_pop_into(&output, a);
      Zperform_oper(a->tok.number, b->tok.number, temp->tok.op.value, &res->tok.number);
      ZStack_push(&output, res);
    }
  }
  ZStack_peek(&output, res);
  ZStack_free(&output);
  free(temp), free(a), free(b);

  num = res->tok.number;
  free(res);

  return num;
}

ZTokenResult Zperform_oper(ZNumber a, ZNumber b, ZOperType oper_type, ZNumber *buf) {
  int num = 1;
  switch(oper_type) {
    case ZOPER_TYPE_ADD:
      *buf = a + b;
      break;
    case ZOPER_TYPE_SUBS:
      *buf = a - b;
      break;
    case ZOPER_TYPE_MUL:
      *buf = a * b;
      break;
    case ZOPER_TYPE_DIV:
      *buf = a / b;
      break;
    case ZOPER_TYPE_FACT:
      for(int i = b; i > 0; i--)
        num *= i;
      *buf = num;
      break;
    case ZOPER_TYPE_POW:
      *buf = powl(a, b);
      break;
    default:
      return ZTOKEN_NOBUFFER;
  }
  return ZTOKEN_OK;
}
