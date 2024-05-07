#include"xyz.h"

int zltIsHexDigitChar(int c) {
  if (c >= '0' && c <= '9') {
    return c - '0';
  }
  if (c >= 'A' && c <= 'F') {
    return c - 'A';
  }
  if (c >= 'a' && c <= 'f') {
    return c - 'a';
  }
  return -1;
}

static inline void memSwapChar(char *a, char *b, size_t size) {
  for (; size; ++a, ++b, --size) {
    char c = *a;
    *a = *b;
    *b = c;
  }
}

static inline void memSwapInt(int *a, int *b, size_t size) {
  for (; size >= sizeof(int); ++a, ++b, size -= sizeof(int)) {
    int c = *a;
    *a = *b;
    *b = c;
  }
  memSwapChar((char *) a, (char *) b, size);
}

void zltMemSwap(void *a, void *b, size_t size) {
  memSwapInt((int *) a, (int *) b, size);
}
