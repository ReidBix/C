/*
 *Reid Bixler
 *rmb3yz
 *September 9, 2014
 *CS 2150 Pre-Lab 2 List.cpp
 */

#include <iostream>
#include "List.h"

using namespace std;

List::List(){
  head = new ListNode;
  tail = new ListNode;
  count = 0;
  head->next=tail;
  tail->previous=head;
  ListItr iter(this->head->next);
}

List::List(const List& source) {      // Copy Constructor
  head=new ListNode;
  tail=new ListNode;
  head->next=tail;
  tail->previous=head;
  count=0;
  ListItr iter(source.head->next);
  while (!iter.isPastEnd()) {       // deep copy of the list
    insertAtTail(iter.retrieve());
    iter.moveForward();
  }
}

List::~List(){
 
}

List& List::operator=(const List& source) { //Equals operator
  if (this == &source)
    return *this;
  else {
    makeEmpty();
    ListItr iter(source.head->next);
    while (!iter.isPastEnd()) {
      insertAtTail(iter.retrieve());
      iter.moveForward();
    }
  }
  return *this;
}

bool List::isEmpty() const{
  if (count == 0){
    return true;
  } else {
    return false;
  }
}

void List::makeEmpty() {
  head = new ListNode;
  tail = new ListNode;
  head->next = tail;
  tail->previous = head;
  count = 0;
  ListItr iter(this->head->next);
}

ListItr List::first(){
  return ListItr(head->next);
}

ListItr List::last(){
  return ListItr(tail->previous);
}

void List::insertAfter(int x, ListItr position){
  ListNode *newNodePointer = new ListNode;
  newNodePointer->value = x;
  newNodePointer->previous = position.current;
  newNodePointer->next = position.current->next;
  position.current->next = newNodePointer;
  newNodePointer->next->previous = newNodePointer;
  count++;
}


void List::insertBefore(int x, ListItr position){
  ListNode *newNodePointer = new ListNode;
  newNodePointer->value = x;
  newNodePointer->next = position.current;
  newNodePointer->previous = position.current->previous;
  position.current->previous = newNodePointer;
  newNodePointer->previous->next = newNodePointer;
  count++;
}



void List::insertAtTail(int x){
  ListNode *newNodePointer = new ListNode;
  newNodePointer->value = x;
  newNodePointer->next = tail;
  newNodePointer->previous = tail->previous;
  tail->previous->next = newNodePointer;
  tail->previous = newNodePointer;
  count++;
}



void List::remove(int x){
  ListItr iter(head->next);
  while (!iter.isPastEnd()) {
    if (iter.retrieve() == x){
      iter.current->previous->next = iter.current->next;
      iter.current->next->previous = iter.current->previous;
      count--;
      break;
    } else{
      iter.moveForward();
    }
  }
}

ListItr List::find(int x){
  ListItr iter(head->next);
  while (!iter.isPastEnd()) {
    if (iter.retrieve() == x){
      return iter;
    } else {
      iter.moveForward();
    }
  }
  return iter;
}


int List::size() const{
  ListItr iter(head->next);
  int size = 0;
  while (!iter.isPastEnd()) {
    size++;
    iter.moveForward();
  }
  return size;
}
