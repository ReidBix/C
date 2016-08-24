/*
 * Reid Bixler
 * rmb3yz
 * October 7, 2014
 * CS 2150 Pre-Lab 5 TreeNode.h
 */


#ifndef TREENODE_H
#define TREENODE_H

#include <string>
using namespace std;

class TreeNode {
public:
    TreeNode();						//Default Constructor
    TreeNode(const string & val);	//Constructor

private:
    string value;
    TreeNode *left, *right;			// for trees
    friend class TreeCalc;			//gives TreeCalc access to private data
};

#endif
