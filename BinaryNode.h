//Header file for BinaryNode.cpp
//Node for a binary search tree, stores int value, BinaryNode* leftchild, and BinaryNode* rightchild

#include <iostream>

using namespace std;

class BinaryNode {
 public:
  BinaryNode(int); //constructor
  int getValue(); //returns the int stored in the node
  void setValue(int);
  void setLeftChild(BinaryNode*); //sets the left child of the node
  void setRightChild(BinaryNode*); //sets the right child of the node
  BinaryNode* getLeftChild(); //gets the leftchild of the node, may be null
  BinaryNode* getRightChild(); //gets the rightchild of the node, may be null
 protected:
  int value;
  BinaryNode* leftchild;
  BinaryNode* rightchild;
};
