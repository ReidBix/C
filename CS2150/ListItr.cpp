/*
 *Reid Bixler
 *rmb3yz
 *September 9, 2014
 *CS 2150 Pre-Lab 2 ListItr.cpp
 */

#include <iostream>
#include "ListItr.h"
#include "ListNode.h"

using namespace std;

ListItr::ListItr(){
  current = NULL;
}

ListItr::ListItr(ListNode *theNode){
  current = theNode;
}

bool ListItr::isPastEnd() const{
  return current->next == NULL;
}

bool ListItr::isPastBeginning() const{
  return current->previous == NULL;
}

void ListItr::moveForward(){
  if (!isPastEnd()){
    current = current->next;
  }
}

void ListItr::moveBackward(){
  if (!isPastBeginning()){
      current = current->previous;
    }
}

int ListItr::retrieve() const{
  return current->value;
}

ostream& operator<<(ostream& output, const ListItr& iter) {
    // output in format:  (current)
  ListNode L1 = *(iter.current);
  return output << "(" << iter.current << "," << L1 <<  ")";
}
