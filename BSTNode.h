// BSTNode.h
// Dylan Vanmali for CS24 Prof. Franklin Spring 2015

#ifndef __BST_NODE_H__
#define __BST_NODE_H__

template < class T >
class BSTNode {
 public:
  
  BSTNode<T>(T v) {
    value = v;
    leftChild = rightChild = NULL;
  }
  
  // These are the attributes of a BST<T>::Node you can use.                  
  T getValue() const {return value;}
  T* getPointer() const {return &value;}
  BSTNode<T> *leftChild;
  BSTNode<T> *rightChild;
  
 private:
  T value;
};

#endif
