//C++ Project 11 - Binary Search Tree - 3/16/17
//Creates a binary search tree that can be modified by the user

#include <iostream>
#include <string.h>
#include <stdlib.h>
#include <fstream>
#include <limits>
#include "BinaryNode.h"

using namespace std;

//prototypes
void addBinaryNode(BinaryNode* & head, BinaryNode* newNode);
void addBinaryNodeRecursion(BinaryNode* current, BinaryNode* newNode);
bool deleteBinaryNode(BinaryNode* & head, int value);
bool deleteBinaryNodeRecursion(BinaryNode* current, int value);
void displayTree(BinaryNode* current, int numSpaces);
void deleteTree(BinaryNode* treeNode);
void getInput(char* input);
void trimWhitespace(char* text);
int getInt(char* message);

const int INPUT_SIZE = 201;

int main(){
  BinaryNode* head = NULL;
  char input[INPUT_SIZE];
  char number[11];
  int copyIndex;
  int deletedValue;

  cout << "\n-----Binary Search Tree v1.0-----\n";
  cout << "Creates a binary search tree in the console\n";
  cout << "Enter 'file' to use a file as input or 'quit' to exit the program.\n";
  cout << "C++ Project 11 - Nathan Purwosumarto\n\n";

  while(true){
    cout << "Initial Numbers: ";
    getInput(input);
    //if input = quit, then end the program
    if(strcmp(input, "quit") == 0){
      cout << "\nProgram Terminated." << endl;
      break;
    }
    //if the user inputs 'file', prompt for filename
    else if(strcmp(input, "file") == 0){
      cout << "Enter filename: ";
      getInput(input);
      fstream myfile(input);
      if (myfile.is_open()){
        //if file is found, copy contents into input
        myfile.getline(input, 501);
        trimWhitespace(input);
        cout << input << endl;
        myfile.close();
      }
      //tell the user if filename is invalid
      else{
        cout << "Unable to open file.\n\n";
        continue;
      }
    }
    //extracts numbers from the input char array one by one
    copyIndex = 0;
    fill(number, number + 11, ' ');
    for(int i = 0; i < strlen(input); i++){
      if(isdigit(input[i])){
        number[copyIndex] = input[i];
        copyIndex++;
      }
      //add the extracted number into the binary search tree
      else if(copyIndex != 0){
        addBinaryNode(head, new BinaryNode(strtol(number, NULL, 10)));
        fill(number, number + 11, ' ');
        copyIndex = 0;
      }
    }
    //add the extracted number into the binary search tree
    if(copyIndex != 0){
      addBinaryNode(head, new BinaryNode(strtol(number, NULL, 10)));
      fill(number, number + 11, ' ');
      copyIndex = 0;
    }
    //display the full binary search tree after all numbers have been added
    cout << "\nBinary Tree (leftmost node is head): \n";
    displayTree(head, 0);
    //prompt the user if they want to modify the existing binary tree
    cout << "\nDo you wish to modify the binary tree? \nCommands: 'add', 'delete', 'print' or 'next' to continue\n";
    while(!strcmp(input, "next") == 0){
      cout << "\nInput: ";
      getInput(input);
      //adds a number to the binary tree
      if(strcmp(input, "add") == 0){
        addBinaryNode(head, new BinaryNode(getInt("Value to add: ")));
        cin.ignore(81, '\n');
      }
      //displays the binary tree
      else if(strcmp(input, "print") == 0){
        cout << "Binary Tree (leftmost node is head): \n";
        displayTree(head, 0);
      }
      //deletes a number from the binary tree
      else if(strcmp(input, "delete") == 0){
        deletedValue = getInt("Value to delete: ");
        if(deleteBinaryNode(head, deletedValue)){
          cout << "Sucessfully deleted '" << deletedValue << "'\n";
        }
        else{
          cout << '\'' << deletedValue << "' was not found\n";
        }
        cin.ignore(81, '\n');
      }
      else if(!strcmp(input, "next") == 0){
        cout << "<Invalid Input>\n";
      }
    }
    //delete the tree to avoid memory leak when the head is set to another new BinaryNode
    if(head != NULL){
      deleteTree(head);
      head = NULL;
    }
    cout << endl;
  }

  return 0;
}

void addBinaryNode(BinaryNode* & head, BinaryNode* newNode){
  if(head == NULL){
    head = newNode;
  }
  else{
    addBinaryNodeRecursion(head, newNode);
  }
}

void addBinaryNodeRecursion(BinaryNode* current, BinaryNode* newNode){
  //if child value is greater or equal to parent value, go down the right branch
  if(newNode->getValue() >= current->getValue()){
    if(current->getRightChild() != NULL){
      addBinaryNodeRecursion(current->getRightChild(), newNode);
    }
    else{
      current->setRightChild(newNode);
    }
  }
  //if child value is less than parent value, go down the left branch
  else{
    if(current->getLeftChild() != NULL){
      addBinaryNodeRecursion(current->getLeftChild(), newNode);
    }
    else{
      current->setLeftChild(newNode);
    }
  }
}

bool deleteBinaryNode(BinaryNode* & head, int value){
  if(head == NULL){
    return false;
  }
  //if head is to be deleted
  else if(head->getValue() == value){
    BinaryNode* temp;
    //if head has both children
    if(head->getLeftChild() != NULL && head->getRightChild() != NULL){
      temp = head->getLeftChild();
      if(temp->getRightChild() == NULL){
        temp->setRightChild(head->getRightChild());
        delete head;
        head = temp;
      }
      else{
        while(temp->getRightChild() != NULL){
          temp = temp->getRightChild();
        }
        int newHeadValue = temp->getValue();
        temp->setValue(value);
        deleteBinaryNodeRecursion(head->getLeftChild(), value);
        head->setValue(newHeadValue);
      }
    }
    //if head only has left child
    else if(head->getLeftChild() != NULL && head->getRightChild() == NULL){
      temp = head->getLeftChild();
      delete head;
      head = temp;
    }
    //if head only has right child
    else if(head->getLeftChild() == NULL && head->getRightChild() != NULL){
      temp = head->getRightChild();
      delete head;
      head = temp;
    }
    //if head has no children
    else if(head->getLeftChild() == NULL && head->getRightChild() == NULL){
      delete head;
      head = NULL;
    }
    return true;
  }
  else{
    return deleteBinaryNodeRecursion(head, value);
  }
}

bool deleteBinaryNodeRecursion(BinaryNode* current, int value){
  BinaryNode* temp;
  //cout << current->getValue() << endl;
  if(current->getValue() <= value){
    if(current->getRightChild() == NULL){
      return false;
    }
    if(current->getRightChild()->getValue() == value){
      //if node to be deleted has both children
      if(current->getRightChild()->getLeftChild() != NULL && current->getRightChild()->getRightChild() != NULL){
        temp = current->getRightChild()->getLeftChild();

        if(temp->getRightChild() == NULL){
          temp->setRightChild(current->getRightChild()->getRightChild());
          delete current->getRightChild();
          current->setRightChild(temp);
        }
        else{
          while(temp->getRightChild() != NULL){
            temp = temp->getRightChild();
          }
          int newValue = temp->getValue();
          temp->setValue(value);
          deleteBinaryNodeRecursion(current->getRightChild()->getLeftChild(), value);
          current->getRightChild()->setValue(newValue);
        }
        return true;
      }
      //if node to be deleted only has left child
      else if(current->getRightChild()->getLeftChild() != NULL && current->getRightChild()->getRightChild() == NULL){
        temp = current->getRightChild()->getLeftChild();
        delete current->getRightChild();
        current->setRightChild(temp);
        return true;
      }
      //if node to be deleted only has right child
      else if(current->getRightChild()->getLeftChild() == NULL && current->getRightChild()->getRightChild() != NULL){
        temp = current->getRightChild()->getRightChild();
        delete current->getRightChild();
        current->setRightChild(temp);
        return true;
      }
      //if node to be deleted has no children
      else if(current->getRightChild()->getLeftChild() == NULL && current->getRightChild()->getRightChild() == NULL){
        delete current->getRightChild();
        current->setRightChild(NULL);
        return true;
      }
    }
    else{
        return deleteBinaryNodeRecursion(current->getRightChild(), value);
    }
  }
  else{
    if(current->getLeftChild() == NULL){
      return false;
    }
    if(current->getLeftChild()->getValue() == value){
      //if node to be deleted has both children
      if(current->getLeftChild()->getLeftChild() != NULL && current->getLeftChild()->getRightChild() != NULL){
        temp = current->getLeftChild()->getLeftChild();

        if(temp->getRightChild() == NULL){
          temp->setRightChild(current->getLeftChild()->getRightChild());
          delete current->getLeftChild();
          current->setLeftChild(temp);
        }
        else{
          while(temp->getRightChild() != NULL){
            temp = temp->getRightChild();
          }
          int newValue = temp->getValue();
          temp->setValue(value);
          deleteBinaryNodeRecursion(current->getLeftChild()->getLeftChild(), value);
          current->getLeftChild()->setValue(newValue);
        }
        return true;
      }
      //if node to be deleted only has left child
      else if(current->getLeftChild()->getLeftChild() != NULL && current->getLeftChild()->getRightChild() == NULL){
        temp = current->getLeftChild()->getLeftChild();
        delete current->getLeftChild();
        current->setLeftChild(temp);
        return true;
      }
      //if node to be deleted only has right child
      else if(current->getLeftChild()->getLeftChild() == NULL && current->getLeftChild()->getRightChild() != NULL){
        temp = current->getLeftChild()->getRightChild();
        delete current->getLeftChild();
        current->setLeftChild(temp);
        return true;
      }
      //if node to be deleted has no children
      else if(current->getLeftChild()->getLeftChild() == NULL && current->getLeftChild()->getRightChild() == NULL){
        delete current->getLeftChild();
        current->setLeftChild(NULL);
        return true;
      }
    }
    else{
        return deleteBinaryNodeRecursion(current->getLeftChild(), value);
    }
  }
}

//prints out the binary tree to the console
void displayTree(BinaryNode* head, int numSpaces){
  if(head == NULL){
    return;
  }
  if(head->getRightChild() != NULL){
    displayTree(head->getRightChild(), numSpaces+1);
  }
  for(int i = 0; i < numSpaces; i++){
    cout << "   ";
  }
  cout << head->getValue() << endl;
  if(head->getLeftChild() != NULL){
    displayTree(head->getLeftChild(), numSpaces+1);
  }
}

//deletes all nodes in a binary tree
void deleteTree(BinaryNode* treeNode){
  if(treeNode->getRightChild() != NULL){
    deleteTree(treeNode->getRightChild());
    treeNode->setRightChild(NULL);
  }
  if(treeNode->getLeftChild() != NULL){
    deleteTree(treeNode->getLeftChild());
    treeNode->setLeftChild(NULL);
  }
  delete treeNode;
  //treeNode = NULL;
}

//stores user input into a char*
void getInput(char* input){
  fill(input, input + INPUT_SIZE, ' ');
  cin.getline(input, INPUT_SIZE);
  trimWhitespace(input);
}

//remove extra whitespaces to make sure input is compared as intended
void trimWhitespace(char* text){
  char* newText = text;
  char lastChar = ' ';
  while(*text != '\0'){
    if(!(*text == ' ' && lastChar == ' ')){
      *newText = *text;
      lastChar = *text;
      newText++;
    }
    text++;
  }
  if(*(newText-1) != ' '){
    *newText = '\0';
  }
  else{
    *(newText-1) = '\0';
  }
}

//prompts the user for an integer
int getInt(char* message){
  int number;
  bool valid = false;
  while (!valid){
    cout << message;
    cin >> number;
    //delete excess whitespace
    while (cin.peek() == ' '){
      cin.ignore(1);
    }
    if(cin.peek() != '\n'){
      cin.clear();
      cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    else{
      valid = true;
    }
  }
  return number;
}
