#ifndef ZLT_LINK_H
#define ZLT_LINK_H

#include"xyz.h"

typedef struct {
  void *next;
} zltLink;

#define zltLinkMemb(p, m) zltMemb(p, zltLink, m)

static inline zltLink zltLinkMake() {
  return (zltLink) { .next = NULL };
}

typedef zltLinkDtor(void *link);

void zltLinkClean(void *link, zltLinkDtor *dtor);

typedef struct {
  void *next;
  void *prev;
} zltDbLink;

#define zltDbLinkMemb(p, m) zltMemb(p, zltDbLink, m)

static inline zltDbLink zltDbLinkMake() {
  return (zltDbLink) { .next = NULL, .prev = NULL };
}

#endif
