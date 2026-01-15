#ifndef Z_window_h
#define Z_window_h

#include <stdbool.h>
#include <wchar.h>

#include <ncursesw/ncurses.h>

#include "datalist/list.h"

typedef enum _ZWindowResult {
  ZWINDOW_OK = 0,
  ZWINDOW_EALREADY_FREED,
  ZWINDOW_ENOBUFFER,
  ZWINDOW_ENOMEMORY,
  ZWINDOW_ENULL,
} ZWindowResult;

typedef struct ZWindow {
  wchar_t *data;
  WINDOW *info;
  WINDOW *border;
  bool has_border;
} ZWindow;

ZWindowResult ZWindow_new(ZWindow *win, bool with_border);
ZWindowResult ZWindow_set_text(ZWindow *win, wchar_t *text);
ZWindowResult ZWindow_append_text(ZWindow *win, wchar_t *text);
ZWindowResult ZWindow_free(ZWindow *win);

#endif
