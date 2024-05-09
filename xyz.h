#ifndef ZLT_XYZ_H
#define ZLT_XYZ_H

#include<stdbool.h>
#include<stddef.h>
#include<string.h>

#define zltMemb(p, t, m) (((t *) (p))->m)
#define zltOffsetOf(t, m) ((size_t) &zltMemb(NULL, t, m))
#define zltContainerOf(p, t, m) ((t *) ((char *) (p) - zltOffsetOf(t, m)))

/// @return 0-15, -1 when not a hex digit character
int zltIsHexDigitChar(int c);

void zltMemSwap(void *a, void *b, size_t size);

typedef struct {
  const char *data;
  size_t size;
} zltString;

static inline zltString zltStrMake(const char *data, size_t size) {
  return (zltString) { .data = data, .size = size };
}

/// @param data requires string constant literal
#define zltStrMakeStatic(data) zltStringMake(data, sizeof(data))

/// different of stdlib strtol, requires /^\d+/, ignore bads like out of range
/// @param[out] dest usually initialized by 0
const char *zltStrToLong(long *dest, const char *it, const char *end);

/// different of stdlib strtol, requires /^[01]+/, ignore bads like out of range
/// @param[out] dest usually initialized by 0
const char *zltStrToLong2(long *dest, const char *it, const char *end);

/// different of stdlib strtol, requires /^[0-3]+/, ignore bads like out of range
/// @param[out] dest usually initialized by 0
const char *zltStrToLong4(long *dest, const char *it, const char *end);

/// different of stdlib strtol, requires /^[0-7]+/, ignore bads like out of range
/// @param[out] dest usually initialized by 0
const char *zltStrToLong8(long *dest, const char *it, const char *end);

/// different of stdlib strtol, requires /^[[:xdigit:]]+/, ignore bads like out of range
/// @param[out] dest usually initialized by 0
const char *zltStrToLong16(long *dest, const char *it, const char *end);

/// different of stdlib strtod, requires /^(\d+\.\d*|\.?\d+)([Ee][+-]?\d+)?/, ignore bads like out of range
/// @param[out] dest usually initialized by 0
const char *zltStrToDouble(double *dest, const char *it, const char *end);

#endif
