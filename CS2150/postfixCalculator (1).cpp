/*
 *Reid Bixler
 *rmb3yz
 *September 16, 2014
 *CS 2150 In-Lab 3 postfixCalculator.cpp
 */


#include <iostream>
#include <stack>
#include "postfixCalculator.h"
#include <cstdlib>
#include <string>

using namespace std;

PostfixCalculator::PostfixCalculator(){
  cout << "Initializing PostfixCalculator" << endl;
}

void PostfixCalculator::add(){
  int x, y, z;
  if (!stack.empty()){
    x = stack.top();
    stack.pop();
  } else {
    cout << "Error: tried pop() or top() an empty stack" << endl;
    exit(-1);
  }
  if (!stack.empty()){
    y = stack.top();
    stack.pop();
  } else {
    cout << "Error: tried pop() or top() an empty stack" << endl;
    exit(-1);
  }
  z = y + x;
  cout << "Adding integers " << y << " and " << x << " equaling " << z << endl; 
  stack.push(z);
}

void PostfixCalculator::subtract(){
  int x, y, z;
  if (!stack.empty()){
    x = stack.top();
    stack.pop();
  } else {
    cout << "Error: tried pop() or top() an empty stack" << endl;
    exit(-1);
  }
  if (!stack.empty()){
    y = stack.top();
    stack.pop();
  } else {
    cout << "Error: tried pop() or top() an empty stack" << endl;
    exit(-1);
  }
  z = y - x;
  cout << "Subtracting integers " << y << " and " << x << " equaling " << z << endl; 
  stack.push(z);
}

void PostfixCalculator::multiply(){
  int x, y, z;
  if (!stack.empty()){
    x = stack.top();
    stack.pop();
  } else {
    cout << "Error: tried pop() or top() an empty stack" << endl;
    exit(-1);
  }
  if (!stack.empty()){
    y = stack.top();
    stack.pop();
  } else {
    cout << "Error: tried pop() or top() an empty stack" << endl;
    exit(-1);
  }
  z = y * x;
  cout << "Multiplying integers " << y << " and " << x << " equaling " << z << endl; 
  stack.push(z);
}

void PostfixCalculator::divide(){
  int x, y, z;
  if (!stack.empty()){
    x = stack.top();
    stack.pop();
  } else {
    cout << "Error: tried pop() or top() an empty stack" << endl;
    exit(-1);
  }
  if (!stack.empty()){
    y = stack.top();
    stack.pop();
  } else {
    cout << "Error: tried pop() or top() an empty stack" << endl;
    exit(-1);
  }
  z = y / x;
  cout << "Dividing integers " << y << " and " << x << " equaling " << z << endl; 
  stack.push(z);
}

void PostfixCalculator::negate(){
  int x, z;
  if (!stack.empty()){
    x = stack.top();
    stack.pop();
  } else {
    cout << "Error: tried pop() or top() an empty stack" << endl;
    exit(-1);
  }
  z = -x;
  cout << "Negating integer " << x << " equaling " << z << endl;
  stack.push(z);
}

void PostfixCalculator::pushNum(int x){
  cout << "Pushing integer " << x << " to top of stack" << endl;
  stack.push(x);
}

int PostfixCalculator::getTopValue(){
  if (!stack.empty()){
    cout << "Retrieving top value in stack: " << stack.top() << endl;
    return stack.top();
  } else {
    cout << "Error: tried pop() or top() an empty stack" << endl;
    exit(-1);
    return -1;
  }
}

void PostfixCalculator::evaluate(string s){
  int stringLength = s.length();
  string num;
  string num2;
  int dig;
  for (int i = 0; i < stringLength; ++i){
    if (stringLength > 1) {
      if (s[0] == '-'){
	num = s.substr(1,stringLength);
	dig = atoi(num.c_str());
	dig = -dig;
	this->pushNum(dig);
	num = "";
	break;
      } else {
	num = s;
	dig = atoi(num.c_str());
	this->pushNum(dig);
	num = "";
	break;
      }      
    }
    else if (stringLength == 1) {
      if (isdigit(s[0])){
	num = s;
	dig = atoi(num.c_str());
	this->pushNum(dig);
	num = "";
      }
      else if (s[0] == '+') {
	this->add();
      }
      else if (s[0] == '-') {
	this->subtract();
      }
      else if (s[0] == '*') {
	this->multiply();
      }
      else if (s[0] == '/') {
	this->divide();
      }
      else if (s[0] == '~') {
	this->negate();
      }
    } 
  }
  this->getTopValue();
}
