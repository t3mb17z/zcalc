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

  ZToken *tokens;
  ZNumber result = 0;
  size_t count = 0;
  ZToken_Tokenize(expr, &tokens, &count);
  ZToken_to_rpn(tokens, count);

  result = Zeval_rpn(tokens, count);

  printf("%Lf\n", result);

  return 0;
}
