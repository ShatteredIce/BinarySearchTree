//C++ Project 11 - Binary Search Tree - 3/16/17
//Creates a binary search tree that can be modified by the user

#include <iostream>
#include <string.h>
#include "BinaryNode.h"

using namespace std;

//prototypes
void addBinaryNode(BinaryNode* & head, BinaryNode* newNode);

const int INPUT_SIZE = 201;

int main(){
  BinaryNode* head = NULL;
  bool running = true;
  char input[INPUT_SIZE];
  char number[11];
  int copyIndex;

  cout << "\n-----Binary Search Tree v1.0-----\n";
  cout << "Creates a binary search tree in the console\n";
  cout << "C++ Project 11 - Nathan Purwosumarto\n\n";

  while(running){
    cout << "Input: ";
    getInput(input);
    //if input = quit, then end the program
    if(strcmp(input, "quit") == 0){
      cout << "\nProgram Terminated." << endl;
      running = false;
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
        addBinaryNode(new BinaryNode(strtol(number, NULL, 10)));
        fill(number, number + 11, ' ');
        copyIndex = 0;
      }
    }
    //add the extracted number into the binary search tree
    if(copyIndex != 0){
      addBinaryNode(new BinaryNode(strtol(number, NULL, 10)));
      fill(number, number + 11, ' ');
      copyIndex = 0;
    }
  }
  return 0;
}

void addBinaryNode(BinaryNode* & head, BinaryNode* newNode){
  if(head == NULL){
    head = newNode;
  }
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
