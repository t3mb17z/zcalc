#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "token.h"
#include "iparse.h"

static uint8_t Zprecedence(char op) {
  switch(op) {
    case '^':
      return 4; break;
    case '/': case '*':
      return 3; break;
    case '+': case '-':
      return 2; break;
    default:
      return 0; break;
  }
}

static ZAssociativeType Zassociativity(char op) {
  if(strchr("!^", op) != NULL)
    return ZASSOCIATIVE_RIGHT;
  else if(strchr("+-*/", op))
    return ZASSOCIATIVE_LEFT;
  else
    return ZASSOCIATIVE_UNKNOWN;
}

ZTokenResult ZToken_Tokenize(const char *input, ZToken **tokens, size_t *tok_counter) {

  size_t size = strlen(input);
  size_t tok_count = 0;

  *tokens = calloc(size, sizeof(ZToken));
  if(*tokens == NULL) return ZTOKEN_NONMEMORY;

  ZToken temp_token = { 0 };
  bool success = false;
  for(size_t i = 0; i < size; i++) {
    if(strchr("+-/*^", input[i])) {
      temp_token.tok.op.value = input[i];
      temp_token.type = ZTOKEN_TYPE_OP;
      temp_token.tok.op.precedence = Zprecedence(input[i]);
      temp_token.tok.op.assoc = Zassociativity(input[i]);
      success = true;
    } else if(Zis_digit(input[i])) {
      size_t old_index = i;
      ZNumber temp = 0.0;
      while(Zis_digit(input[i]) || input[i] == '.') i++;
      char *buffer = malloc(i - old_index + 1);
      strncpy(buffer, &input[old_index], i - old_index + 1);
      buffer[i - old_index] = '\0';
      temp = Zstr_to_number(buffer);
      if(temp == 0.0 && errno != ZNUMBER_OK) {

        size_t idx = (i >= 2) ? i - 1 : i;
        for(size_t j = 0; j < idx; j++)
          free(tokens[j]), tokens[j] = NULL;

        free(tokens);
        return ZTOKEN_NONMEMORY;
      }
      temp_token.tok.number = temp;
      temp_token.type = ZTOKEN_TYPE_ZNUMBER;
      success = true;
      i--;
    } else if(input[i] == '(') { // ) 
      temp_token.type = ZTOKEN_TYPE_LPAR;
      success = true;
    } else if(input[i] == ')') {
      temp_token.type = ZTOKEN_TYPE_RPAR;
      success = true;
    }

    if(success) {
      if(temp_token.type == ZTOKEN_TYPE_ZNUMBER)
        (*tokens)[tok_count].tok.number = temp_token.tok.number;
      else if(temp_token.type == ZTOKEN_TYPE_OP) {
        (*tokens)[tok_count].tok.op = temp_token.tok.op;
      }
      (*tokens)[tok_count].type = temp_token.type;
      
      tok_count++;
    }

    success = false;
    if(input[i] == '\0') break;
  }

  if(tok_counter != NULL)
    *tok_counter = tok_count;

  // if(tok_count < size)
  //   *tokens = realloc(*tokens, tok_count * sizeof(ZToken) + 1);

  return ZTOKEN_OK;
}

ZTokenResult ZToken_Free(ZToken **tokens) {
  if(*tokens == NULL) return ZTOKEN_ALREADY_FREED;
  free(*tokens), *tokens = NULL;
  return ZTOKEN_OK;
}
