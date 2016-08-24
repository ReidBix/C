/*
 *Reid Bixler
 *rmb3yz
 *September 16, 2014
 *CS 2150 Pre-Lab 3 postfixCalculator.cpp
 */


#include <iostream>
#include <stack>
#include "postfixCalculator.h"
#include <cstdlib>

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
    return stack.top();
  } else {
    cout << "Error: tried pop() or top() an empty stack" << endl;
    exit(-1);
    return -1;
  }
}
