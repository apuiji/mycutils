#include<ctype.h>
#include<math.h>
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

const char *zltStrToLong(long *dest, const char *it, const char *end) {
  for (; it != end && isdigit(*it); ++it) {
    *dest = (*dest * 10) | (*it - '0');
  }
  return it;
}

const char *zltStrToLong2(long *dest, const char *it, const char *end) {
  for (; it != end && (*it == '0' || *it == '1'); ++it) {
    *dest = (*dest << 1) | (*it - '0');
  }
  return it;
}

const char *zltStrToLong4(long *dest, const char *it, const char *end) {
  for (; it != end && *it >= '0' && *it <= '3'; ++it) {
    *dest = (*dest << 2) | (*it - '0');
  }
  return it;
}

const char *zltStrToLong8(long *dest, const char *it, const char *end) {
  for (; it != end && *it >= '0' && *it <= '7'; ++it) {
    *dest = (*dest << 3) | (*it - '0');
  }
  return it;
}

const char *zltStrToLong16(long *dest, const char *it, const char *end) {
  for (; it != end; ++it) {
    int i = zltIsHexDigitChar(*it);
    if (i < 0) {
      break;
    }
    *dest = (*dest << 4) | i;
  }
  return it;
}

static const char *strToDouble1(double *dest, const char *it, const char *end);
static const char *strToDouble2(double *dest, const char *it, const char *end);

const char *zltStrToDouble(double *dest, const char *it, const char *end) {
  const char *it1 = strToDouble1(dest, it, end);
  return it1 ? zltStrToDouble2(dest, it1, end) : it;
}

const char *strToDouble1(double *dest, const char *it, const char *end) {
  if (it == end) {
    return NULL;
  }
  const char *it1;
  if (isdigit(*it)) {
    long l = 0;
    it1 = zltStrToLong(&l, it, end);
    *dest += l;
  } else if (*it == '.' && it + 1 != end && isdigit(it[1])) {
    it1 = it;
  } else {
    return NULL;
  }
  if (it1 == end || *it1 != '.') {
    return it1;
  }
  long l = 0;
  const char *it2 = zltStrToLong(&l, it1 + 1, end);
  *dest += l / pow(10, it2 - it1 - 1);
  return it2;
}

const char *strToDouble2(double *dest, const char *it, const char *end) {
  if (end - it < 2) {
    return it;
  }
  if (*it != 'E' && *it != 'e') {
    return it;
  }
  long e = 0;
  const char *it1;
  if (it[1] == '+') {
    it1 = zltStrToLong(&e, it + 2, end);
    if (it1 == it + 2) {
      return it;
    }
  } else if (it[1] == '-') {
    it1 = zltStrToLong(&e, it + 2, end);
    if (it1 == it + 2) {
      return it;
    }
    e = -e;
  } else {
    it1 = zltStrToLong(&e, it + 1, end);
    if (it1 == it + 1) {
      return it;
    }
  }
  *dest *= pow(10, e);
  return it1;
}
