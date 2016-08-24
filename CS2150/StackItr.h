/*
 *Reid Bixler
 *rmb3yz
 *September 19, 2014
 *CS 2150 Post-Lab 3 StackItr.h
 */


#ifndef STACKITR_H
#define STACKITR_H

#include "StackNode.h"
#include "Stack.h"

class StackItr {
public:
    StackItr();		
    StackItr(StackNode* theNode);
    bool isPastEnd() const;
    bool isPastBeginning() const;
    void moveForward();
    void moveBackward();
    int retrieve() const;
    friend ostream& operator<<(ostream& output, const StackItr& iter);

private:
    StackNode* current;	
    friend class Stack;
};

#endif

