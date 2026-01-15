#include <stdlib.h>
#include <wchar.h>

#include <ncursesw/ncurses.h>

#include <ui/window.h>

static void wclean(WINDOW *win) {
  wclear(win);
  wrefresh(win);
  delwin(win);
}

ZWindowResult ZWindow_new(ZWindow *win, bool with_border) {
  if(win == NULL)
    return ZWINDOW_ENOBUFFER;

  win->info = newwin(0, 0, 0, 0);
  if(with_border)
    win->border = newwin(0, 0, 0, 0);
  else
    win->border = NULL;
  win->data = calloc(512, sizeof(wchar_t));
  win->has_border = with_border;

  return ZWINDOW_OK;
}

ZWindowResult ZWindow_set_text(ZWindow *win, wchar_t *text) {
  win->data = wcsdup(text);
  if(win->data == NULL)
    return ZWINDOW_ENOMEMORY;
  else
    return ZWINDOW_OK;
}

ZWindowResult ZWindow_append_text(ZWindow *win, wchar_t *text) {
  size_t len = wcslen(text);
  if(wcslen(win->data) + len + 1)
    return 1;
  return 0;
}

ZWindowResult ZWindow_free(ZWindow *win) {
  if(win == NULL)
    return ZWINDOW_EALREADY_FREED;

  free(win->data);
  wclean(win->info);
  if(win->has_border)
    wclean(win->border);
  win->border = false;

  return ZWINDOW_OK;
}
