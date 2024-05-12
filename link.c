#include"link.h"

void zltLinkClean(void *link, const void *end, zltLinkDtor *dtor) {
  if (link == end) {
    return;
  }
  void *next = zltLinkMemb(link, next);
  dtor(link);
  zltLinkClean(next, dtor, end);
}

void **zltLinkInsert(void **dest, void *link, void *last) {
  void **next = &zltMemb(last, zltLink, next);
  *next = *dest;
  *dest = link;
  return next;
}

void *zltLinkErase(void **link, void *last) {
  void *a = *link;
  *link = zltMemb(last, zltLink, next);
  zltMemb(last, zltLink, next) = NULL;
  return a;
}
