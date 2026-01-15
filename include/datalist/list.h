#ifndef Z_list_h
#define Z_list_h

#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>

typedef enum _ZListType {
  ZLIST_TYPE_STACK,
  ZLIST_TYPE_QUEUE,
  ZLIST_TYPE_UNKNOWN
} ZListType;

typedef enum _ZListStat {
  ZLIST_STAT_CAPACITY = 1,
  ZLIST_STAT_SIZE,
} ZListStat;

typedef enum _ZListResult {
  ZLIST_OK = 0,
  ZLIST_FULL,
  ZLIST_EMPTY,
  ZLIST_NONEMPTY,
  ZLIST_ENOBUFFER,
  ZLIST_EALREADY_FREED,
  ZLIST_ENONMEMORY,
  ZLIST_EOVERFLOW,
  ZLIST_EMISMATCH
} ZListResult;

typedef struct _ZList {
  ZListType type;
  uint8_t *data;
  size_t count, cap;
  size_t elem_size;
  size_t head, tail;
} ZList;

typedef bool (*ZListCB)(ZList *list, void *elem);

size_t ZList_len(const ZList *list);
size_t ZList_cap(const ZList *list);
bool ZList_empty(const ZList *list);

#endif
