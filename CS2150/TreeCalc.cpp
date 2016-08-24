/*
 * Reid Bixler
 * rmb3yz
 * October 7, 2014
 * CS 2150 Pre-Lab 5 TreeCalc.cpp
 */

#include "TreeCalc.h"
#include <iostream>
#include <cstdlib>

using namespace std;

//Constructor
TreeCalc::TreeCalc() {
 
}

//Destructor- frees memory
TreeCalc::~TreeCalc() {
  while(!mystack.empty()){
    delete mystack.top();
    mystack.pop();
  }
}

//Deletes tree/frees memory
void TreeCalc::cleanTree(TreeNode* ptr) {
  if (mystack.size()!=0 && mystack.top()!=NULL) {
    if (!(ptr->left == NULL && ptr->right == NULL)){
      cleanTree(ptr->left);
      cleanTree(ptr->right);
    } else {
      delete mystack.top();
      mystack.pop();
    }
  }
}

//Gets data from user
void TreeCalc::readInput() {
    string response;
    cout << "Enter elements one by one in postfix notation" << endl
         << "Any non-numeric or non-operator character,"
         << " e.g. #, will terminate input" << endl;
    cout << "Enter first element: ";
    cin >> response;
    //while input is legal
    while (isdigit(response[0]) || response[0]=='/' || response[0]=='*'
            || response[0]=='-' || response[0]=='+' ) {
        insert(response);
        cout << "Enter next element: ";
        cin >> response;
    }
}

//Puts value in tree stack
void TreeCalc::insert(const string& val) {
    // insert a value into the tree
  TreeNode* n = new TreeNode(val);
  if (val.length() > 1) {
    mystack.push(n); 
  } else if (val.length() == 1) {
    if (isdigit(val[0])){ 
      mystack.push(n);
      } else {
      TreeNode* B = mystack.top();
      mystack.pop();
      TreeNode* A = mystack.top();
      mystack.pop();
      n->left = A;
      n->right = B;
      mystack.push(n);
      }
  }
}

//Prints data in prefix form
void TreeCalc::printPrefix(TreeNode* ptr) const {
    // print the tree in prefix format
  if (!(ptr->left == NULL && ptr->right == NULL)){
    cout << ptr->value << " ";
    printPrefix(ptr->left);
    printPrefix(ptr->right);
  } else 
    cout << ptr->value << " ";
}

//Prints data in infix form
void TreeCalc::printInfix(TreeNode* ptr) const {
  // print tree in infix format with appropriate parentheses
  if (!(ptr->left == NULL && ptr->right == NULL)){
    if (!isdigit((ptr->value)[0]) && ptr->value.length() == 1) {
      cout << "(";
    }
    printInfix(ptr->left);
    cout << " " << ptr->value << " ";
    printInfix(ptr->right);
    if (!isdigit((ptr->value)[0]) && ptr->value.length() == 1) {
      cout << ")";
    }
  } else 
    cout << ptr->value;
}

//Prints data in postfix form
void TreeCalc::printPostfix(TreeNode* ptr) const {
    // print the tree in postfix form
  if (!(ptr->left == NULL && ptr->right == NULL)){
    printPostfix(ptr->left);
    printPostfix(ptr->right);
    cout << ptr->value << " ";
  } else
    cout << ptr->value << " ";
}

// Prints tree in all 3 (pre,in,post) forms
void TreeCalc::printOutput() const {
 if (mystack.size()!=0 && mystack.top()!=NULL) {
        cout << "Expression tree in postfix expression: ";
        // call your implementation of printPostfix()
	printPostfix(mystack.top());
        cout << endl;
        cout << "Expression tree in infix expression: ";
        // call your implementation of printInfix()
	printInfix(mystack.top());
        cout << endl;
        cout << "Expression tree in prefix expression: ";
        // call your implementation of printPrefix()
	printPrefix(mystack.top());
        cout << endl;
    } else
        cout<< "Size is 0." << endl;
}

//Evaluates tree, returns value
// private calculate() method
int TreeCalc::calculate(TreeNode* ptr) const {
    // Traverse the tree and calculates the result
  string val = ptr->value;
  int dig;
  if (val.length() > 1) {
    if (val[0] == '-'){
      dig = atoi (val.substr(1,val.length()).c_str());
      dig = -dig;
      return dig;
    } else {
      dig = atoi (val.substr(0,val.length()).c_str());
      return dig;
    }
  } else if (val.length() == 1) {
    if (isdigit(val[0])){ 
      dig = atoi (val.c_str());
      return dig;
    } else {
      if (val[0] == '+') {
	return calculate(ptr->left) + calculate(ptr->right);
      }
      else if (val[0] == '-') {;
	return calculate(ptr->left) - calculate(ptr->right);
      }
      else if (val[0] == '*') {
	return calculate(ptr->left) * calculate(ptr->right);
      }
      else if (val[0] == '/') {
	return calculate(ptr->left) / calculate(ptr->right);
      }
    }
  }
  return -1;
}

//Calls calculate, sets the stack back to a blank stack
// public calculate() method. Hides private data from user
int TreeCalc::calculate() {
    int i = 0;
    // call private calculate method here
    i = calculate(mystack.top());
    cleanTree(mystack.top());
    return i;
}
