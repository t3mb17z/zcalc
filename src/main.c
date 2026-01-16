#include <stdbool.h>
#include <stdint.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <ncursesw/ncurses.h>

#include "calc.h"
#include "iparse.h"
#include "token.h"

int main(int argc, char *argv[]) {

  if(argc < 2) {
    puts("Not enough arguments");
    return 0;
  }

  const char *expr = strdup(argv[1]);

  ZTokenResult res = ZTOKEN_OK;
  ZToken *tokens;
  ZNumber result = 0;
  size_t count = 0;
  res = ZToken_Tokenize(expr, &tokens, &count);
  if(res != ZTOKEN_OK)
    return 0;
  res = ZToken_to_rpn(tokens, count);
  if(res != ZTOKEN_OK)
    return 0;

  result = Zeval_rpn(tokens, count);

  printf("%Lf\n", result);

  return 0;
}
