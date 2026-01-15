#include "datalist/stack.h"
#include "datalist/list.h"

#include <stdlib.h>
#include <string.h>

ZListResult ZStack_new(ZList *list, size_t elem_count, size_t elem_size) {
  if(list == NULL)
    return ZLIST_ENOBUFFER;

  *list = (ZList){ 0 };
  list->data = calloc(elem_count * elem_size, 1);
  if(list->data == NULL) return ZLIST_ENONMEMORY;
  list->elem_size = elem_size;
  list->type = ZLIST_TYPE_STACK;
  list->count = 0;
  list->cap = elem_count * elem_size;

  return ZLIST_OK;
}

ZListResult ZStack_resize(ZList *list, size_t new_size) {
  if(list->type != ZLIST_TYPE_STACK)
    return ZLIST_EMISMATCH;

  if(new_size <= list->cap) return ZLIST_OK;

  list->data = realloc(list->data, new_size * list->elem_size);
  if(list->data == NULL) return ZLIST_ENONMEMORY;
  list->cap = new_size;

  return ZLIST_OK;
}

ZListResult ZStack_push(ZList *list, const void *data) {
  if(list->type != ZLIST_TYPE_STACK)
    return ZLIST_EMISMATCH;
  if(list->count + list->elem_size > list->cap)
    return ZLIST_FULL;

  memcpy(&list->data[list->count], data, list->elem_size);
  list->count += list->elem_size;

  return ZLIST_OK;
}

ZListResult ZStack_peek(const ZList *list, void *buffer) {
  if(list->type != ZLIST_TYPE_STACK)
    return ZLIST_EMISMATCH;
  if(buffer == NULL || buffer == NULL)
    return ZLIST_ENOBUFFER;
  if(list->count == 0)
    return ZLIST_EMPTY;

  memcpy(buffer, &list->data[list->count - list->elem_size], list->elem_size);

  return ZLIST_OK;
}

ZListResult ZStack_pop_into(ZList *list, void *buffer) {
  if(list->type != ZLIST_TYPE_STACK)
    return ZLIST_EMISMATCH;
  if(list == NULL || buffer == NULL)
    return ZLIST_ENOBUFFER;
  if(list->count == 0) {
    memset(buffer, 0, list->elem_size);
    return ZLIST_OK;
  }

  memcpy(buffer, &list->data[list->count - list->elem_size], list->elem_size);
  memset(&list->data[list->count - list->elem_size], 0, list->elem_size);
  list->count -= list->elem_size;

  return ZLIST_OK;
}

ZListResult ZStack_pop(ZList *list) {
  if(list->type != ZLIST_TYPE_STACK)
    return ZLIST_EMISMATCH;
  if(list->count == 0)
    return ZLIST_EMPTY;

  memset(&list->data[list->count - list->elem_size], 0, list->elem_size);
  list->count -= list->elem_size;

  return ZLIST_OK;
}

ZListResult ZStack_free(ZList *list) {
  if(list->type != ZLIST_TYPE_STACK)
    return ZLIST_EMISMATCH;
  if(list->data == NULL)
    return ZLIST_EALREADY_FREED;

  free(list->data);
  list->type = ZLIST_TYPE_UNKNOWN;
  list->cap = list->count = 0;
  list->elem_size = 0;
  list->type = ZLIST_TYPE_UNKNOWN;

  return ZLIST_OK;
}
