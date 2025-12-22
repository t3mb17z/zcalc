#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "token.h"
#include "iparse.h"

ZTokenResult ZToken_Tokenize(const char *input, ZToken ***tokens, size_t *tok_counter) {

  size_t size = strlen(input);
  size_t tok_count = 0;

  *tokens = calloc(1, sizeof(ZToken *));
  if(*tokens == NULL) return ZTOKEN_NONMEMORY;
  for(size_t i = 0; i < size; i++) {
    (*tokens)[i] = calloc(1, sizeof(ZToken));
    if((*tokens)[i] == NULL) {
      for(size_t j = 0; j < i - 1; j++) {
        free((*tokens)[j]);
      }
      free(*tokens);
      return ZTOKEN_NONMEMORY;
    }
  }

  for(size_t i = 0; i < size; i++) {
    if(strstr(input, "+-/*")) {
      (*tokens)[i]->tok.op = input[i];
      (*tokens)[i]->type = ZTOKEN_TYPE_OP;
    } else if(Zis_digit(input[i])) {
      size_t old_index = i;
      ZNumber temp = 0.0;
      while(Zis_digit(input[i]) || input[i] == '.') i++;
      char *buffer = malloc(i - old_index);
      strncpy(buffer, &input[old_index], i - old_index);
      temp = Zstr_to_number(buffer);
      if(temp == 0.0 && errno != ZNUMBER_OK) {
        for(size_t j = 0; j < i - 1; j++)
          free((*tokens)[j]);
        free(*tokens);
        return ZTOKEN_NONMEMORY;
      }
      (*tokens)[tok_count]->tok.number = temp;
      (*tokens)[tok_count]->type = ZTOKEN_TYPE_DIGIT;
    } else if(input[i] == '(') { // ) 
      (*tokens)[i]->type = ZTOKEN_TYPE_LPAR;
    } else if(input[i] == ')') {
      (*tokens)[i]->type = ZTOKEN_TYPE_RPAR;
    }

    tok_count++;
  }

  if(tok_counter != NULL) {
    *tok_counter = tok_count;
  }

  return ZTOKEN_OK;
}

ZTokenResult ZToken_Free(ZToken **tokens, size_t size) {
  if(tokens == NULL) return ZTOKEN_ALREADY_FREED;
  for(size_t i = 0; i < size; i++) {
    if(tokens[i] == NULL) continue;
    else free(tokens[i]);
  }
  free(tokens);
  return ZTOKEN_OK;
}
