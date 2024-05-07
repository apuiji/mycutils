#include"bitree.h"

typedef zltBiTree BiTree;

void zltBiTreeClean(void *tree, zltBiTreeDtor *dtor) {
  if (!tree) {
    return;
  }
  zltBiTreeClean(zltMemb(tree, BiTree, lchd), dtor);
  zltBiTreeClean(zltMemb(tree, BiTree, rchd), dtor);
  dtor(tree);
}

void *zltBiTreeMostSide(const void *tree, int side) {
  void *next = zltMemb(tree, BiTree, children)[side];
  return next ? zltBiTreeMostSide(next, side) : tree;
}
