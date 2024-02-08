#pragma once

#include<stddef.h>

typedef struct zltMemPool zltMemPool;
typedef struct zltMemPoolNode zltMemPoolNode;

struct zltMemPool {
  zltMemPoolNode *data;
  /// aleast 3
  size_t size;
};

struct zltMemPoolNode {
  size_t prev;
  size_t next;
  bool used;
};

/// @return -1 when failed
int zltMemPoolMake(zltMemPool *mp, size_t size);
/// @return block index, 0 when failed
size_t zltMemPoolAlloc(zltMemPool *mp, size_t size);
int zltMemPoolFree(zltMemPool *mp, size_t blockIndex);
/// @return block index, 0 when failed
size_t zltMemPoolRealloc(zltMemPool *mp, size_t blockIndex, size_t size);

static inline void *zltMemPoolGet(zltMemPool *mp, size_t blockIndex) {
  return mp->data + blockIndex + 1;
}
