#ifndef ZLT_XYZ_H
#define ZLT_XYZ_H

#include<stdbool.h>
#include<stddef.h>

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

static inline zltString zltStringMake(const char *data, size_t size) {
  return (zltString) { .data = data, .size = size };
}

/// @param data requires string constant literal
#define zltStringMakeStatic(data) zltStringMake(data, sizeof(data))

#endif
