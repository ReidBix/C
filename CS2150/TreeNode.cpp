/*
 * Reid Bixler
 * rmb3yz
 * October 7, 2014
 * CS 2150 Pre-Lab 5 TreeNode.cpp
 */


#include "TreeNode.h"

//Default Constructor -left and right are NULL, value '?'
TreeNode::TreeNode() {
    value="?";
    left=NULL;
    right=NULL;
}

//Constructor - sets value to val
TreeNode::TreeNode(const string & val) {
    value=val;
    left=NULL;
    right=NULL;
}
