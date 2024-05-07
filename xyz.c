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

void zltMemSwap(void *a, void *b, size_t size) {
  for (; size >= sizeof(int); a += sizeof(int), b += sizeof(int), size -= sizeof(int)) {
    int c = *(int *) a;
    *(int *) a = *(int *) b;
    *(int *) b = c;
  }
  for (; size; ++a, ++b, --size) {
    char c = *(char *) a;
    *(char *) a = *(char *) b;
    *(char *) b = c;
  }
}
