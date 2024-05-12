#include"link.h"

void zltLinkClean(void *link, const void *end, zltLinkDtor *dtor) {
  if (link == end) {
    return;
  }
  void *next = zltLinkMemb(link, next);
  dtor(link);
  zltLinkClean(next, dtor);
}
