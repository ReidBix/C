/*
 *Reid Bixler
 *rmb3yz
 *September 19, 2014
 *CS 2150 Post-Lab 3 Stack.h
 */

#ifndef STACK_H
#define STACK_H

#include <iostream>
#include <string>
#include "StackNode.h"
#include "StackItr.h"
using namespace std;

class StackItr;

class Stack {
public:
    Stack();			
    Stack(const Stack& source);
    ~Stack();
    Stack& operator=(const Stack& source);
    bool isEmpty() const;
    void makeEmpty();
    StackItr first();
    StackItr last();
    void insertAfter(int x, StackItr position);
    void insertBefore(int x, StackItr position);
    void insertAtTail(int x); 
    void remove(int x); 
    StackItr find(int x);
   
    int size() const;

    void push(int e);
    int top();
    void pop();
    bool empty();

private:
    StackNode *head, *tail;  
    int count;	        
    friend class StackItr;

};

void printStack(Stack& source, bool direction);

#endif





