//C++ Project 11 - Binary Search Tree - 3/16/17
//Creates a binary search tree that can be modified by the user

#include <iostream>
#include <string.h>
#include <stdlib.h>
#include <fstream>
#include "BinaryNode.h"

using namespace std;

//prototypes
void addBinaryNode(BinaryNode* & head, BinaryNode* newNode);
void addBinaryNodeRecursion(BinaryNode* current, BinaryNode* newNode);
void displayTree(BinaryNode* current, int numSpaces);
void deleteTree(BinaryNode* treeNode);
void getInput(char* input);
void trimWhitespace(char* text);

const int INPUT_SIZE = 201;

int main(){
  BinaryNode* head = NULL;
  char input[INPUT_SIZE];
  char number[11];
  int copyIndex;

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
        cout << "Number(s) to add: ";
        getInput(input);
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
      }
      //displays the binary tree
      else if(strcmp(input, "print") == 0){
        cout << "Binary Tree (leftmost node is head): \n";
        displayTree(head, 0);
      }
      //deletes a number from the binary tree
      else if(strcmp(input, "delete") == 0){
        cout << "WIP\n";
      }
      else if(!strcmp(input, "next") == 0){
        cout << "<Invalid Input>\n";
      }
    }
    //delete the tree to avoid memory leak when the head is set to another new BinaryNode
    deleteTree(head);
    head = NULL;
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

//prints out the binary tree to the console
void displayTree(BinaryNode* current, int numSpaces){
  if(current->getRightChild() != NULL){
    displayTree(current->getRightChild(), numSpaces+1);
  }
  for(int i = 0; i < numSpaces; i++){
    cout << "   ";
  }
  cout << current->getValue() << endl;
  if(current->getLeftChild() != NULL){
    displayTree(current->getLeftChild(), numSpaces+1);
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
