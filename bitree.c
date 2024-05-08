#include"bitree.h"

void zltBiTreeClean(void *tree, zltBiTreeDtor *dtor) {
  if (!tree) {
    return;
  }
  zltBiTreeClean(zltBiTreeMemb(tree, lchd), dtor);
  zltBiTreeClean(zltBiTreeMemb(tree, rchd), dtor);
  dtor(tree);
}

void *zltBiTreeMostSide(const void *tree, int side) {
  void *next = zltBiTreeMemb(tree, children)[side];
  return next ? zltBiTreeMostSide(next, side) : tree;
}

// iterators begin
static void *nxy1(const void *tree, int xy);

void *zltBiTreeNXY(const void *tree, int xy) {
  void *x = zltBiTreeMemb(tree, children)[xy];
  if (x) {
    return x;
  }
  void *y = zltBiTreeMemb(tree, children)[!xy];
  if (y) {
    return y;
  }
  return nxy1(tree, xy);
}

void *nxy1(const void *tree, int xy) {
  zltBiTree *parent = (zltBiTree *) zltBiTreeMemb(tree, parent);
  if (!parent) {
    return NULL;
  }
  if (tree == parent->children[xy] && parent->children[!xy]) {
    return parent->children[!xy];
  }
  return nxy1(parent, xy);
}

static void *xny1(const void *tree, int xy);

void *zltBiTreeXNY(const void *tree, int xy) {
  void *y = zltBiTreeMemb(tree, children)[!xy];
  if (y) {
    return zltBiTreeMostSide(y, xy);
  }
  return xny1(tree, xy);
}

void *xny1(const void *tree, int xy) {
  zltBiTree *parent = (zltBiTree *) zltBiTreeMemb(tree, parent);
  if (!parent) {
    return NULL;
  }
  if (tree == parent->children[xy]) {
    return parent;
  }
  return xny1(parent, xy);
}

void *zltBiTreeXYN(const void *tree, int xy) {
  zltBiTree *parent = (zltBiTree *) zltBiTreeMemb(tree, parent);
  if (!parent) {
    return NULL;
  }
  void *y = parent->children[!xy];
  if (tree != y && y) {
    return zltBiTreeMostSide(y, xy);
  }
  return parent;
}
// iterators end

void *zltBiTreeRotate(void *tree, bool right) {
  zltBiTree *parent = (zltBiTree *) zltBiTreeMemb(tree, parent);
  zltBiTree *child = (zltBiTree *) zltBiTreeMemb(tree, children)[!right];
  zltBiTreeMemb(tree, parent) = child;
  zltBiTreeMemb(tree, children)[!right] = child->children[right];
  child->parent = parent;
  child->children[right] = tree;
  if (parent) {
    parent->children[tree == parent->rchd] = child;
  }
}

// find operations begin
void *zltBiTreeFind(const void *tree, zltBiTreeCmpForFind *cmp, const void *data) {
  if (!tree) {
    return NULL;
  }
  int diff = cmp(data, tree);
  if (!diff) {
    return tree;
  }
  void *next = zltTreeMemb(tree, children)[diff > 0];
  return zltBiTreeFind(next, cmp, data);
}

void **zltBiTreeFindForInsert(void **parent, void **tree, zltBiTreeCmpForFind *cmp, const void *data) {
  if (!*tree) {
    return tree;
  }
  int diff = cmp(data, *tree);
  if (!diff) {
    return tree;
  }
  *parent = *tree;
  void **next = &zltBiTreeMemb(*tree, children)[diff > 0];
  return zltBiTreeFindForInsert(parent, next, cmp, data);
}
// find operations end
