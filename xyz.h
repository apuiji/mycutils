#ifndef ZLT_XYZ_H
#define ZLT_XYZ_H

#include<stdbool.h>
#include<stddef.h>

#define zltMemb(p, t, m) (((t *) (p))->m)
#define zltOffsetOf(t, m) ((size_t) &zltMemb(NULL, t, m))
#define zltContainerOf(p, t, m) ((t *) ((char *) (p) - zltOffsetOf(t, m)))

void zltMemSwap(void *a, void *b, size_t size);

#endif
