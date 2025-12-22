#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "token.h"
#include "iparse.h"

ZTokenResult ZToken_Tokenize(const char *input, ZToken ***tokens) {

  size_t size = strlen(input);
  *tokens = calloc(1, sizeof(ZToken *));
  if(*tokens == NULL) return ZTOKEN_NONMEMORY;
  for(size_t i = 0; i < size; i++) {
    (*tokens)[i] = calloc(1, sizeof(ZToken));
    if((*tokens)[i] == NULL) {
      for(size_t j = 0; j < i; j++) {
        free((*tokens)[j]);
      }
      free(*tokens);
    }
  }
  for(size_t i = 0; i < size; i++) {
    if(strstr(input, "+-/*")) {
      (*tokens)[i]->tok.op = input[i];
      (*tokens)[i]->type = ZTOKEN_TYPE_OP;
    } else if(Zis_digit(input[i])) {
      size_t old_index = i;
      ZNumber temp = 0.0;
      while(Zis_digit(input[i++]));
      char *buffer = malloc(i - old_index);
      strncpy(buffer, &input[old_index], i - old_index);
      temp = Zstr_to_number(buffer);
      if(temp == 0.0 && errno != 0) {
        free(tokens);
        return ZTOKEN_NONMEMORY;
      }
      (*tokens)[i]->type = ZTOKEN_TYPE_DIGIT;
    } else if(input[i] == '(') { // ) 
      (*tokens)[i]->type = ZTOKEN_TYPE_LPAR;
    } else if(input[i] == ')') {
      (*tokens)[i]->type = ZTOKEN_TYPE_RPAR;
    }
  }

  return ZTOKEN_OK;
}
