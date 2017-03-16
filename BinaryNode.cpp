//BinaryNode class for creating a binary search tree
#include <iostream>
#include <string.h>
#include "BinaryNode.h"

using namespace std;

//Constructor: stores an int value, sets left child and right child to NULL
BinaryNode::BinaryNode(int newValue){
  value = newValue;
  leftchild = NULL;
  rightchild = NULL;
}

//returns the int stored in the node
int BinaryNode::getValue(){
  return value;
}

 //sets the leftchild of this node
void BinaryNode::setLeftChild(BinaryNode* newNode){
  leftchild = newNode;
}

//sets the rightchild of this node
void BinaryNode::setRightChild(BinaryNode* newNode){
 rightchild = newNode;
}

//gets the leftchild of the node, may be null
BinaryNode* BinaryNode::getLeftChild(){
  return leftchild;
}

//gets the rightchild of the node, may be null
BinaryNode* BinaryNode::getRightChild(){
  return rightchild;
}
