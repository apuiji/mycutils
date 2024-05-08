#include"link.h"

void zltLinkClean(void *link, zltLinkDtor *dtor) {
  void *next = zltLinkMemb(link, next);
  dtor(link);
  zltLinkClean(next, dtor);
}
