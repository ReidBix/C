/*
 *Reid Bixler
 *rmb3yz
 *September 9, 2014
 *CS 2150 Pre-Lab 2 ListNode.cpp
 */

#include <iostream>
#include "ListNode.h"

using namespace std;

ListNode::ListNode() {
  value = 0;
  next = NULL;
  previous = NULL;
}

ostream& operator<<(ostream& output, const ListNode& node) {
    // output in format:  (value, next, previous)
    return output << "(" << node.value << "," << node.next << "," << node.previous << ")";
}

