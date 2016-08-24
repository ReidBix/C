/*
 *Reid Bixler
 *rmb3yz
 *September 19, 2014
 *CS 2150 Post-Lab 3 StackNode.cpp
 */


#include <iostream>
#include "StackNode.h"

using namespace std;

StackNode::StackNode() {
  value = 0;
  next = NULL;
  previous = NULL;
}

ostream& operator<<(ostream& output, const StackNode& node) {
    return output << "(" << node.value << "," << node.next << "," << node.previous << ")";
}

