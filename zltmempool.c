#include<stdlib.h>
#include<string.h>
#include"zltmempool.h"

static size_t blockCount(size_t size) {
  size_t n = size / sizeof(zltMemPoolNode);
  return size % sizeof(zltMemPoolNode) ? n + 1 : n;
}

static int insertNode(zltMemPool *mp, size_t i, size_t j, size_t k);

int zltMemPoolMake(zltMemPool *mp, size_t size) {
  size_t n = blockCount(size) + 2;
  if (n <= 2) {
    return -1;
  }
  mp->data = (zltMemPoolNode *) malloc(sizeof(zltMemPoolNode) * n);
  if (!mp->data) [[unlikely]] {
    return -1;
  }
  mp->size = n;
  insertNode(mp, 0, 1, n - 1);
  mp->data[1].used = false;
  return 0;
}

int insertNode(zltMemPool *mp, size_t i, size_t j, size_t k) {
  mp->data[i].next = j;
  mp->data[j].prev = i;
  mp->data[j].next = k;
  mp->data[k].prev = j;
  return 0;
}

static size_t alloc(zltMemPool *mp, size_t i, size_t n);

size_t zltMemPoolAlloc(zltMemPool *mp, size_t size) {
  return alloc(mp, 0, blockCount(size) + 1);
}

static int expand(zltMemPool *mp);
static size_t findIdles(zltMemPool *mp, size_t i, size_t n);

size_t alloc(zltMemPool *mp, size_t n) {
  size_t i = findIdles(mp, 1, n);
  if (i) {
    size_t j = i + n;
    size_t k = mp->data[i].next;
    if (j != k) {
      insertNode(mp, i, j, k);
      mp->data[j].used = false;
    }
    mp->data[i].used = true;
    return i;
  } else {
    i = mp->data[mp->size - 1].prev;
    if (expand(mp)) [[unlikely]] {
      return (size_t) -1;
    }
    return alloc(mp, i, n);
  }
}

static int catIdles(zltMemPool *mp, size_t i);

int expand(zltMemPool *mp) {
  if (sizeof(zltMemPoolNode) * (mp->size << 1) < sizeof(zltMemPoolNode) * mp->size) {
    return -1;
  }
  zltMemPoolNode *data = (zltMemPoolNode *) realloc(mp->data, sizeof(zltMemPoolNode) * (mp->size << 1));
  if (!data) {
    return -1;
  }
  mp->data = data;
  size_t i = mp->size - 1;
  mp->size = mp->size << 1;
  mp->data[i].next = mp->size - 1;
  mp->data[i].used = false;
  catIdles(mp, i);
  return true;
}

static int catIdles1(zltMemPool *mp, size_t i);

int catIdles(zltMemPool *mp, size_t i) {
  size_t j = mp->data[i].prev;
  if (j && !mp->data[j].used) {
    mp->data[j].next = mp->data[i].next;
    return catIdles(mp, j);
  } else {
    return catIdles1(mp, i);
  }
}

int catIdles1(zltMemPool *mp, size_t i) {
  size_t j = mp->data[i].next;
  if (j != mp->size - 1 && !mp->data[j].used) {
    mp->data[i].next = mp->data[j].next;
    return catIdles1(mp, i);
  } else {
    return 0;
  }
}

size_t findIdles(zltMemPool *mp, size_t i, size_t n) {
  zltMemPoolNode *node = mp->data + i;
  if (!node->used && (node->next - i) >= n) {
    return i;
  }
  if (node->next != mp->size - 1) {
    return findIdles(mp, node->next, n);
  }
  return (size_t) -1;
}

int zltMemPoolFree(zltMemPool *mp, size_t i) {
  mp->data[i].used = false;
  return catIdles(mp, i);
}

size_t zltMemPoolRealloc(zltMemPool *mp, size_t i, size_t size) {
  size_t n = blockCount(size) + 1;
  size_t j = mp->data[i].next;
  size_t m = j - i;
  if (n < m) {
    insertNode(mp, i, i + n, j);
    mp->data[i + n].used = false;
    mp->data[i].used = true;
    return i;
  } else if (n > m) {
    j = alloc(mp, 1, n);
    if (j == (size_t) -1) [[unlikely]] {
      return (size_t) -1;
    }
    memcpy(zltMemPoolGet(mp, i), zltMemPoolGet(mp, j), sizeof(zltMemPoolNode) * (m - 1));
    mp->data[i].used = false;
    catIdles(mp, i);
    return j;
  } else {
    return i;
  }
}
