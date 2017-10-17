// SplayTree.cpp
// Dylan Vanmali
// CS130A Spring 2017 Prof. Suri

#include <iostream>
#include <string>
#include "BSTNode.h"
#include "SplayTree.h"
using namespace std;

template < typename T >
std::ostream& SplayTree<T>::showTree(std::ostream &os, BSTNode<T> *n) const {
  // This is printed from top down
  int h = getHeight(n);
  for (int i=1; i<=h; i++) {
    printLevel(os, n, i, false);
    os << endl;
  }
}

template < typename T >
bool SplayTree<T>::printLevel(std::ostream &os, BSTNode<T> *n, int level, bool first) const {
  if (n != NULL) {
    if (level == 1) {
      if (first)
	os << ", ";
      os << n->getValue();
      return true;
    }
    else if (level > 1) {
      first = printLevel(os, n->leftChild,  level-1, first);
      first = printLevel(os, n->rightChild, level-1, first);
      return first;
    }
  }
}


template < typename T >
BSTNode<T>* SplayTree<T>::copyTree(const BSTNode<T> *n) {
  if(n == NULL)
    return NULL;
  else {
    BSTNode<T> * mine = new BSTNode<T>(n->getValue());
    mine->leftChild = copyTree(n->leftChild);
    mine->rightChild = copyTree(n->rightChild);
    return mine;
  }
}

template < typename T >
void SplayTree<T>::deleteTree(BSTNode<T> *n) {
  if (n != NULL) {
    deleteTree(n->leftChild);
    deleteTree(n->rightChild);
    delete n;
  }
}

template < typename T >
int SplayTree<T>::getSize(const BSTNode<T> *n) const {
  if (n == NULL) {
    return 0;
  }
  else {
    int leftSide = getSize(n->leftChild);
    int rightSide = getSize(n->rightChild);
    return 1 + leftSide + rightSide;
  }
}

template < typename T >
int SplayTree<T>::getHeight(const BSTNode<T> *n) const {
  if (n == NULL) {
    return 0;
  }
  else {
    int leftSide = getHeight(n->leftChild);
    int rightSide = getHeight(n->rightChild);
    if (leftSide < rightSide)
      return 1 + rightSide;
    else
      return 1 + leftSide;
  }
}

// Function used to get the height to the value v
// Used in splay function for recursive behavior
template < typename T >
int SplayTree<T>::getHeightToValue(const BSTNode<T> *n, T v) const {
  while (n != NULL) {
    if (v == n->getValue())
      return 1;
    else if (v < n->getValue())
      return 1 + getHeightToValue(n->leftChild,v);
    else if (v > n->getValue())
      return 1 + getHeightToValue(n->rightChild,v);
  }
  return 0;
}

// Returns NULL if not present
template < typename T >
BSTNode<T>* SplayTree<T>::deleteValue(BSTNode<T> *n, const T v) {
  BSTNode<T>* location = find(root,v);
  if (location == NULL)
    return NULL;

  // Delete value is at top of tree, t1 after split
  root = splay(root,v,getHeightToValue(root,v));
  BSTNode<T>* tmp = root;
  BSTNode<T>* t1 = root->leftChild;
  BSTNode<T>* t2 = split(root,v);
  delete tmp;
  root = join(t1, t2);
  return root;
}

// TODO
template < typename T >
BSTNode<T>* SplayTree<T>::join(BSTNode<T> *t1, BSTNode<T> *t2) {
  if (t1 == NULL)
    return t2;
  if (t2 == NULL)
    return t1;

  BSTNode<T>* newRoot = t1;
  BSTNode<T>* previous = t1;

  if (newRoot->rightChild == NULL) {
    newRoot->rightChild = t2;
  }
  else {  
    while (newRoot->rightChild != NULL) {
      previous = newRoot;
      newRoot  = newRoot->rightChild;
    }
    previous->rightChild = newRoot->leftChild;
    newRoot->leftChild = t1;
    newRoot->rightChild = t2;
  }
  root = newRoot;
  return root;
}

// Split returns the broken tree from the root
// The other tree can be obtained as the root value
template < typename T >
BSTNode<T>* SplayTree<T>::split(BSTNode<T> *n, T v) {
  if (n == NULL)
    return NULL;
  else if (v < n->getValue()) {
    BSTNode<T>* brokenTree = n->leftChild;
    n->leftChild = NULL;
    return brokenTree;
  }
  else {
    BSTNode<T>* brokenTree = n->rightChild;
    n->rightChild = NULL;
    return brokenTree;
  }
}


template < typename T >
BSTNode<T>* SplayTree<T>::find(BSTNode<T> *n, const T v) const {
  if(n == NULL)
    return NULL;
  if(v == n->getValue())
    return n;
  else if(v < n->getValue())
    return find(n->leftChild, v);
  else
    return find(n->rightChild, v);
}

// Input root and value to be inserted
// Returns root
template < typename T >
BSTNode<T>* SplayTree<T>::insert(BSTNode<T> *n, const T v) {
  if (n == NULL) {
    BSTNode<T>* newNode = new BSTNode<T>(v);
    cout << "item " << v << " inserted" << endl;
    return newNode;
  }
  if (v == n->getValue()) {
    cout << "item " << v << " not inserted; already present" << endl;
    return n;
  }
  else if (v < n->getValue()) {
    n->leftChild = insert(n->leftChild,v);
    return n;
  }
  else if (v > n->getValue()) {
    n->rightChild = insert(n->rightChild,v);
    return n;
  }
}


// Zig in Right Rotation (for left zig)
template < typename T >
BSTNode<T>* SplayTree<T>::rightRotate(BSTNode<T> *n) {
  BSTNode<T> *m = n->leftChild;
  n->leftChild = m->rightChild;
  m->rightChild = n;
  return m;
}

// Zig in Left Rotation (for right zig)
template < typename T >
BSTNode<T>* SplayTree<T>::leftRotate(BSTNode<T> *n) {
  BSTNode<T> *m = n->rightChild;
  n->rightChild = m->leftChild;
  m->leftChild = n;
  return m;
}

// Splays from root to the value v
// heightAtNode needed for recursive behavior
//   Initial call should be from getHeightAtNode function
// Returns root
template < typename T >
BSTNode<T>* SplayTree<T>::splay(BSTNode<T> *n, T v, int heightAtNode) {
  if (n == NULL || v == n->getValue()) {
    return n;
  }

  // If Height to the value is odd, recurse normally with grandparent
  // Should not rotate once because of this statement, check and balance maintained though
  //   for debugging purposes (no HERE_R or HERE_L should exist if single rotation occurs at leaf)
  //if (heightAtNode % 2 == 1) {
    // Left Subtree
  if (v < n->getValue()) {
    if (n->leftChild == NULL)
      return n;
    // Value is the Left Child
    else if (v == n->leftChild->getValue()) {
      //cout << "HERE_R" << endl;
      return rightRotate(n);
    }
    // Zig-Zig: Left, Left
    else if (v < n->leftChild->getValue()) {
      if (n->leftChild->leftChild == NULL) {
	//cout << "HERE_R" << endl;
	return rightRotate(n);
      }
      //cout << "HERE_RR" << endl;
      n->leftChild->leftChild = splay(n->leftChild->leftChild,v,heightAtNode-2);
      return rightRotate(rightRotate(n));
    }
    // Zig-Zag: Left, Right
    else if (v > n->leftChild->getValue()) {
      if (n->leftChild->rightChild == NULL) {
	//cout << "HERE_R" << endl;
	return rightRotate(n);
      }
      //cout << "HERE_LR" << endl;
      n->leftChild->rightChild = splay(n->leftChild->rightChild,v,heightAtNode-2);
      n->leftChild = leftRotate(n->leftChild);
      return rightRotate(n);
    }
  }
  
    // Right Subtree
  else if (v > n->getValue()) {
    if (n->rightChild == NULL)
      return n;
    // Value is the Right Child   
    else if (v == n->rightChild->getValue()) {
      //cout << "HERE_L" << endl;
      return leftRotate(n);
    }
    // Zig-Zig: Right, Left
    else if (v < n->rightChild->getValue()) {
      if (n->rightChild->leftChild == NULL) {
	//cout << "HERE_L" << endl;
	return leftRotate(n);
      }
      //cout << "HERE_RL" << endl;
      n->rightChild->leftChild = splay(n->rightChild->leftChild,v,heightAtNode-2);
      n->rightChild = rightRotate(n->rightChild);
      return leftRotate(n);
    }
    // Zig-Zag: Right, Right 
    else if (v > n->rightChild->getValue()) {
      if (n->rightChild->rightChild == NULL) {
	//cout << "HERE_L" << endl;
	return leftRotate(n);
      }
      //cout << "HERE_LL" << endl;
      n->rightChild->rightChild = splay(n->rightChild->rightChild,v,heightAtNode-2);
      return leftRotate(leftRotate(n));
    }
  }
  //}
  
  // If Height to the value is even, recurse once in
  /*
    else {
    if (v < n->getValue()) {
      if (n->leftChild == NULL)
	return n;
      // Value is the Left Child
      else if (v == n->leftChild->getValue()) {
	cout << "HERE_Top_R" << endl;
	return rightRotate(n);
      }
      // Right Rotate on top node
      cout << "HERE_Top_R" << endl;
      n->leftChild = splay(n->leftChild,v,heightAtNode-1);
      return rightRotate(n);
    }
    else if (v > n->getValue()) {
      if (n->rightChild == NULL)
	return n;
      // Value is the Right Child
      else if (v == n->rightChild->getValue()) {
	cout << "HERE_Top_L" << endl;
	return leftRotate(n);
      }
      // Left Rotate on top node
      cout << "HERE_Top_L" << endl;
      n->rightChild = splay(n->rightChild,v,heightAtNode-1);
      return leftRotate(n);
    }
  }
  */
}
