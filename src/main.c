#include "iparse.h"
#include "token.h"
#include <stdbool.h>
#include <stdio.h>

void print_result(ZNumberResult result) {
  switch(result) {
  case ZNUMBER_OK:
    puts("Ok!"); break;
  case ZNUMBER_NONUMBER:
    puts("Not a number"); break;
  case ZNUMBER_NONDIGIT:
    puts("Not a digit"); break;
  case ZNUMBER_DOUBLE_NEGATIVE:
    puts("It was double negative"); break;
  case ZNUMBER_MULTIPERIOD:
    puts("More than one period"); break;
  case ZNUMBER_PREPERIOD:
    puts("Number started with period"); break;
  case ZNUMBER_UNTERMINATED:
    puts("Unterminated number"); break;
  }
}

int main(void) {

  ZToken **list;
  ZTokenResult result = ZToken_Tokenize("3+5-9*90", &list);
  if(result != ZTOKEN_OK) {
    fprintf(stderr, "Something went wrong at tokenize\n");
    return 1;
  }

  printf("Tokenized successfully!\n");

  return 0;
}
