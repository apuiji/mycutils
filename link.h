#ifndef ZLT_LINK_H
#define ZLT_LINK_H

typedef struct {
  void *next;
} zltLink;

typedef struct {
  void *next;
  void *prev;
} zltDbLink;

#endif
