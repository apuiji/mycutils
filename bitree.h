#ifndef ZLT_BITREE_H
#define ZLT_BITREE_H

#include"xyz.h"

typedef struct {
  void *parent;
  void *children[0];
  void *lchd;
  void *rchd;
} zltBiTree;

// constructors and destructors begin
static inline zltBiTree zltBiTreeMake(const void *parent) {
  return (zltBiTree) { (void *) parent, NULL, NULL };
}

static inline void zltBiTreeSwap(void *a, void *b) {
  zltMemSwap(a, b, sizeof(zltBiTree));
}

typedef void zltBiTreeDtor(void *tree);

void zltBiTreeClean(void *tree, zltBiTreeDtor *dtor);
// constructors and destructors end

// iterators begin
/// @param side -1 top, 0 left, 1 right
void *zltBiTreeMostSide(const void *tree, int side);

/// @param tree requires not null
/// @param xy 0 NLR, 1 NRL
void *zltBiTreeNXY(const void *tree, int xy);

/// @param tree requires not null
/// @param xy 0
void *zltBiTreeXNY(const void *tree, int xy);

/// @param tree requires not null
/// @param xy 0 LRN, 1 RLN
void *zltBiTreeXYN(const void *tree, int xy);
// iterators end

/// @param tree requires not null and has child on side which another of rotation
/// @param side 0 left, 1 right
void *zltBiTreeRotate(void *tree, int side);

// find operations begin
typedef int zltBiTreeCmpForFind(const void *data, const void *tree);

void *zltBiTreeFind(const void *tree, zltBiTreeCmpForFind *cmp, const void *data);

/// @param[out] parent parent node of inserted, requires not null, usually initialized by null
/// @return insert slot
void **zltBiTreeFindForInsert(void **parent, void **tree, zltBiTreeCmpForFind *cmp, const void *data);
// find operations end

#endif