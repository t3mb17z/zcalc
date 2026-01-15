#include "datalist/list.h"

size_t ZList_len(const ZList *list) {
  return list->count / list->elem_size;
}

size_t ZList_cap(const ZList *list) {
  return list->cap / list->elem_size;
}

bool ZList_empty(const ZList *list) {
  return list->count == 0;
}
