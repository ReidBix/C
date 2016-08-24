/*
 *Reid Bixler
 *rmb3yz
 *September 19, 2014
 *CS 2150 Post-Lab 3 Stack.cpp
 */

#include <iostream>
#include "Stack.h"

using namespace std;

Stack::Stack(){
  head = new StackNode;
  tail = new StackNode;
  count = 0;
  head->next=tail;
  tail->previous=head;
  StackItr iter(this->head->next);
}

Stack::Stack(const Stack& source) {    
  head=new StackNode;
  tail=new StackNode;
  head->next=tail;
  tail->previous=head;
  count=0;
  StackItr iter(source.head->next);
  while (!iter.isPastEnd()) {      
    insertAtTail(iter.retrieve());
    iter.moveForward();
  }
}

Stack::~Stack(){
 
}

Stack& Stack::operator=(const Stack& source) {
  if (this == &source)
    return *this;
  else {
    makeEmpty();
    StackItr iter(source.head->next);
    while (!iter.isPastEnd()) {
      insertAtTail(iter.retrieve());
      iter.moveForward();
    }
  }
  return *this;
}

bool Stack::isEmpty() const{
  if (count == 0){
    return true;
  } else {
    return false;
  }
}

void Stack::makeEmpty() {
  head = new StackNode;
  tail = new StackNode;
  head->next = tail;
  tail->previous = head;
  count = 0;
  StackItr iter(this->head->next);
}

StackItr Stack::first(){
  return StackItr(head->next);
}

StackItr Stack::last(){
  return StackItr(tail->previous);
}

void Stack::insertAfter(int x, StackItr position){
  StackNode *newNodePointer = new StackNode;
  newNodePointer->value = x;
  newNodePointer->previous = position.current;
  newNodePointer->next = position.current->next;
  position.current->next = newNodePointer;
  newNodePointer->next->previous = newNodePointer;
  count++;
}


void Stack::insertBefore(int x, StackItr position){
  StackNode *newNodePointer = new StackNode;
  newNodePointer->value = x;
  newNodePointer->next = position.current;
  newNodePointer->previous = position.current->previous;
  position.current->previous = newNodePointer;
  newNodePointer->previous->next = newNodePointer;
  count++;
}



void Stack::insertAtTail(int x){
  StackNode *newNodePointer = new StackNode;
  newNodePointer->value = x;
  newNodePointer->next = tail;
  newNodePointer->previous = tail->previous;
  tail->previous->next = newNodePointer;
  tail->previous = newNodePointer;
  count++;
}



void Stack::remove(int x){
  StackItr iter(head->next);
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

StackItr Stack::find(int x){
  StackItr iter(head->next);
  while (!iter.isPastEnd()) {
    if (iter.retrieve() == x){
      return iter;
    } else {
      iter.moveForward();
    }
  }
  return iter;
}


int Stack::size() const{
  StackItr iter(head->next);
  int size = 0;
  while (!iter.isPastEnd()) {
    size++;
    iter.moveForward();
  }
  return size;
}


void Stack::push(int e){
  StackNode *newNodePointer = new StackNode;
  newNodePointer->value = e;
  newNodePointer->next = head->next;
  newNodePointer->previous = head;
  head->next->previous = newNodePointer;
  head->next = newNodePointer;
  count++;
}

int Stack::top(){
  StackItr iter = first();
  return iter.retrieve();
}

void Stack::pop(){
  StackItr iter = first();
  iter.current->previous->next = iter.current->next;
  iter.current->next->previous = iter.current->previous;
  count--;
}

bool Stack::empty(){
  if (isEmpty()){
    return true;
  } else{
    return false;
  }
}
