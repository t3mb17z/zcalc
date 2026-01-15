
#include <stdbool.h>
#include <stdint.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <ncursesw/ncurses.h>

#include "calc.h"
#include "iparse.h"
#include "token.h"

void ui(void) {
  initscr();
  noecho();
  raw();
  keypad(stdscr, TRUE);
  cbreak();

  char *buffer = calloc(1024, 1);
  ZToken *expr;
  size_t cap = 0;
  ZNumber result = 0;

  nodelay(stdscr, TRUE);
  signed char ch = 0;
  int idx = 0;
  for(;;) {
    ch = getch();
    if((ch >= '0' && ch <= '9') || strchr("+-*^/()", ch)) {
      buffer[idx++] = ch;
      ZToken_Tokenize(buffer, &expr, &cap);
      ZToken_to_rpn(expr, cap);
      result = Zeval_rpn(expr, cap);
    } else if(ch == 127) {
      buffer[--idx] = 0;
      idx++;
    }

    if(ch == 'q')
      break;

    mvprintw(0, 0, "%s", buffer);
    mvprintw(1, 0, "-------------------------------");
    mvprintw(2, 0, "%.4Lf", result);
  }

  endwin();
}

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

  printf("Result: %.4Lf", result);

  return 0;
}
