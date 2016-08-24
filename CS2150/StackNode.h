/*
 *Reid Bixler
 *rmb3yz
 *September 19, 2014
 *CS 2150 Post-Lab 3 StackNode.h
 */


#ifndef STACKNODE_H
#define STACKNODE_H

#include <iostream>

using namespace std;

class StackNode {
public:
    StackNode();       

    friend ostream& operator<<(ostream& output, const StackNode& node);
      

private:
    int value;
    StackNode *next, *previous;
    
    friend class Stack;

    friend class StackItr;

    friend class StackTest;

};

#endif
