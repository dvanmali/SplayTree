// SplayTree.h
// Dylan Vanmali
// CS130A Spring 2017 Prof. Suri

#ifndef __SPLAYTREE_H__
#define __SPLAYTREE_H__

#include "BSTNode.h"

#include <iostream>
using namespace std;

template <typename T>
class SplayTree {
 public:  
  // Default constructor
  SplayTree<T>() { root = NULL; }

  // Destructor
  ~SplayTree<T>() { deleteTree(root); }
  
  //Copy constructor (deep copy)
  SplayTree<T>( const SplayTree<T> &o ) { root = copyTree(o.root); }

  //Assignment (deep copy)
  SplayTree<T>& operator=(const SplayTree<T> &o) { 
    deleteTree(root);
    root = copyTree(o.root); 
    return *this;
  }

  //Stream Output Operator
  friend std::ostream& operator<< (std::ostream& strm, const SplayTree<T>& tree) {
    if (tree.root != NULL)
      return tree.showTree(strm, tree.root);
    else
      return strm;
  }

  // getSize Function Calls Private Function
  int getSize() const { return getSize(root); }

  // getHeight Function Calls Private Function
  int getHeight() const { return getHeight(root); }

  // Find Function Calls Private Function
  BSTNode<T>* find(const T& v) const {
    BSTNode<T>* result = find(root, v);
    if (result == NULL)
      cout << "item " << v << " not found; not present" << endl;
    else
      cout << "item " << v << " found" << endl;
    return result;
  }

  // Delete Function Calls Private Function
  BSTNode<T>* deleteValue(const T& v) {
    BSTNode<T>* result = deleteValue(root, v);
    if (result == NULL)
      cout << "item " << v << " not deleted; not present" << endl;
    else
      cout << "item " << v << " deleted" << endl;
    return result;
  }

  // Insert Function Calls Private Function
  BSTNode<T>* insert(const T v) {
    root = insert(root,v);
    int height = getHeightToValue(root,v);
    root = splay(root,v,height);
    return root;
  }
  
  
 private:

  BSTNode<T> *root;

  std::ostream& showTree(std::ostream &os, BSTNode<T> *n) const;
  bool printLevel(std::ostream &os, BSTNode<T> *n, int level, bool first) const;
  BSTNode<T>* copyTree(const BSTNode<T> *n);
  void deleteTree(BSTNode<T> *n);
  int getSize(const BSTNode<T> *n) const;   // Gets number of nodes starting at node n
  int getHeight(const BSTNode<T> *n) const; // Gets height starting at node n
  int getHeightToValue(const BSTNode<T> *n, T v) const; // For splay, gets height until it reaches value v
  
  void splay(BSTNode<T> *n);
  BSTNode<T>* join(BSTNode<T> *t1, BSTNode<T> *t2);
  BSTNode<T>* split(BSTNode<T> *n, T v); // Returns broken branch, remaining stays as root

  BSTNode<T>* rightRotate(BSTNode<T> *n);
  BSTNode<T>* leftRotate(BSTNode<T> *n);
  BSTNode<T>* splay(BSTNode<T>* root, T v, int heightAtNode);
  
  BSTNode<T>* find(BSTNode<T> *n, const T v) const;
  BSTNode<T>* deleteValue(BSTNode<T> *n, const T v);
  BSTNode<T>* insert(BSTNode<T> *n, const T v);
  
};

#endif
