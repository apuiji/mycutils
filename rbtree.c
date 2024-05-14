#include"rbtree.h"

// after insert operations begin
static void afterInsert1(void **root, void *node, void *parent, void *gparent);
static void afterInsert2(void **root, void *node, void *parent, void *gparent);

void zltRBTreeAfterInsert(void **root, void *node) {
  void *parent = zltBiTreeMemb(node, parent);
  if (!parent) {
    zltRBTreeMemb(node, red) = false;
    *root = node;
    return;
  }
  if (!zltRBTreeMemb(parent, red)) {
    return;
  }
  void *gparent = zltBiTreeMemb(parent, parent);
  void *uncle = zltBiTreeMemb(gparent, children)[parent == zltBiTreeMemb(gparent, lchd)];
  if (uncle && zltRBTreeMemb(uncle, red)) {
    zltRBTreeMemb(parent, red) = false;
    zltRBTreeMemb(uncle, red) = false;
    zltRBTreeMemb(gparent, red) = true;
    zltRBTreeAfterInsert(root, gparent);
    return;
  }
  if ((node == zltBiTreeMemb(parent, lchd)) == (parent == zltBiTreeMemb(gparent, lchd))) {
    afterInsert1(root, node, parent, gparent);
  } else {
    afterInsert2(root, node, parent, gparent);
  }
}

//     GB        PR        PB
//    /  \      /  \      /  \_
//   PR  UB -> NR  GB -> NR  GR
//  /  \          /  \      /  \_
// NR  SB        SB  UB    SB  UB
void afterInsert1(void **root, void *node, void *parent, void *gparent) {
  int left = node == zltBiTreeMemb(parent, lchd);
  zltBiTreeRotate(gparent, !left);
  zltRBTreeMemb(parent, red) = false;
  zltRBTreeMemb(gparent, red) = true;
  if (*root == gparent) {
    *root = parent;
  }
}

//   GB        GB        __NR__        __NB__
//  /  \      /  \      /      \      /      \_
// PR  UB -> NR  UB -> PR      GB -> PR      GR
//   \      /  \         \    /  \     \    /  \_
//   NR    PR  YB        XB  YB  UB    XB  YB  UB
//  /  \     \_
// XB  YB    XB
void afterInsert2(void **root, void *node, void *parent, void *gparent) {
  int left = node == zltBiTreeMemb(parent, lchd);
  zltBiTreeRotate(parent, !left);
  zltBiTreeRotate(gparent, left);
  zltRBTreeMemb(node, red) = false;
  zltRBTreeMemb(gparent, red) = true;
  if (*root == gparent) {
    *root = node;
  }
}
// after insert operations end

// before erase operations begin
static void beforeErase1(void **root, void *node);
static void beforeErase2(void **root, void *node, void *child);
static void beforeErase3(void **root, void *node);
static void beforeErase4(void **root, void *node, void *sibling, void *parent);
static void beforeErase5(void **root, void *node, void *sibling, void *parent);

void zltRBTreeBeforeErase(void **root, void *node) {
  beforeErase1(root, node);
  if (zltBiTreeMemb(node, lchd)) {
    beforeErase2(root, node, zltBiTreeMemb(node, lchd));
    return;
  }
  if (zltBiTreeMemb(node, rchd)) {
    beforeErase2(root, node, zltBiTreeMemb(node, rchd));
    return;
  }
  if (zltRBTreeMemb(node, red)) {
    return;
  }
  beforeErase3(root, node);
}

void beforeErase1(void **root, void *node) {
  void *a = zltBiTreeXNY(node, 1);
  if (!a) {
    return;
  }
  zltRBTreeSwap(node, a);
  if (*root == node) {
    *root = a;
  }
}

void beforeErase2(void **root, void *node, void *child) {
  void *parent = zltBiTreeMemb(node, parent);
  zltBiTreeMemb(child, parent) = parent;
  zltRBTreeMemb(child, red) = false;
  if (!parent) {
    *root = child;
  } else {
    zltBiTreeMemb(parent, children)[node == zltBiTreeMemb(parent, rchd)] = child;
  }
}

void beforeErase3(void **root, void *node) {
  void *parent = zltBiTreeMemb(node, parent);
  void *sibling = zltBiTreeMemb(parent, children)[node == zltBiTreeMemb(parent, lchd)];
  (sibling && zltRBTreeMemb(sibling, red) ? beforeErase4 : beforeErase5)(root, node, sibling, parent);
}

//   PB         SR        SB
//  /  \       /  \      /  \
// NB  SR  -> PB  YB -> PR  YB
//    /  \   /  \      /  \
//   XB  YB NB  XB    NB  XB
void beforeErase4(void **root, void *node, void *sibling, void *parent) {
  bool right = node == zltBiTreeMemb(parent, rchd);
  void *x = zltBiTreeMemb(sibling, children)[right];
  zltBiTreeRotate(parent, right);
  zltRBTreeMemb(sibling, red) = false;
  zltRBTreeMemb(parent, red) = true;
  if (*root == parent) {
    *root = sibling;
  }
  beforeErase5(root, node, x, parent);
}

static void beforeErase6(void **root, void *node, void *sibling, void *parent);
static void beforeErase7(void **root, void *node, void *sibling, void *parent);
static void beforeErase8(void **root, void *node, void *sibling, void *parent);

void beforeErase5(void **root, void *node, void *sibling, void *parent) {
  bool right = node == zltBiTreeMemb(parent, rchd);
  void *x = zltBiTreeMemb(sibling, children)[right];
  if (x && zltRBTreeMemb(x, red)) {
    beforeErase6(root, node, sibling, parent);
    return;
  }
  void *y = zltBiTreeMemb(sibling, children)[!right];
  if (y && zltRBTreeMemb(y, red)) {
    beforeErase7(root, node, sibling, parent);
    return;
  }
  beforeErase8(root, node, sibling, parent);
}

//   PC        PC         __XR__        __XC__
//  /  \      /  \       /      \      /      \
// NB  SB -> NB  XR  -> PC      SB -> PB      SB
//    /         /  \   /  \    /     /  \    /
//   XR        UB  SB NB  UB  VB    NB  UB  VB
//  /  \          /
// UB  VB        VB
void beforeErase6(void **root, void *node, void *sibling, void *parent) {
  bool right = node == zltBiTreeMemb(parent, rchd);
  void *x = zltBiTreeMemb(sibling, children)[right];
  zltBiTreeRotate(sibling, !right);
  zltBiTreeRotate(parent, right);
  zltRBTreeMemb(x, red) = zltRBTreeMemb(parent, red);
  zltRBTreeMemb(parent, red) = false;
  if (*root == parent) {
    *root = x;
  }
}

//   PC         SB        SC
//  /  \       /  \      /  \_
// NB  SB  -> PC  YR -> PB  YB
//    /  \   /  \      /  \_
//   XB  YR NB  XB    NB  XB
void beforeErase7(void **root, void *node, void *sibling, void *parent) {
  bool right = node == zltBiTreeMemb(parent, rchd);
  void *y = zltBiTreeMemb(sibling, children)[!right];
  zltBiTreeRotate(parent, right);
  zltRBTreeMemb(sibling, red) = zltRBTreeMemb(parent, red);
  zltRBTreeMemb(y, red) = false;
  zltRBTreeMemb(parent, red) = false;
  if (*root == parent) {
    *root = sibling;
  }
}

//   PC        PC        PB
//  /  \      /  \      /  \
// NB  SB -> NB  SR -> NB  SR
//    /  \      /  \      /  \
//   XB  YB    XB  YB    XB  YB
void beforeErase8(void **root, void *node, void *sibling, void *parent) {
  zltRBTreeMemb(sibling, red) = true;
  if (zltRBTreeMemb(parent, red)) {
    zltRBTreeMemb(parent, red) = false;
  } else {
    beforeErase3(root, parent);
  }
}
