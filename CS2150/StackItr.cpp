/*
 *Reid Bixler
 *rmb3yz
 *September 19, 2014
 *CS 2150 Post-Lab 3 StackItr.cpp
 */

#include <iostream>
#include "StackItr.h"
#include "StackNode.h"

using namespace std;

StackItr::StackItr(){
  current = NULL;
}

StackItr::StackItr(StackNode *theNode){
  current = theNode;
}

bool StackItr::isPastEnd() const{
  return current->next == NULL;
}

bool StackItr::isPastBeginning() const{
  return current->previous == NULL;
}

void StackItr::moveForward(){
  if (!isPastEnd()){
    current = current->next;
  }
}

void StackItr::moveBackward(){
  if (!isPastBeginning()){
      current = current->previous;
    }
}

int StackItr::retrieve() const{
  return current->value;
}

ostream& operator<<(ostream& output, const StackItr& iter) {
  StackNode L1 = *(iter.current);
  return output << "(" << iter.current << "," << L1 <<  ")";
}
