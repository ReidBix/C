/*
 * Reid Bixler
 * rmb3yz
 * October 7, 2014
 * CS 2150 In-Lab binarynode.h
 */

/* binarynode.h: binary node class definition */
#ifndef BINARY_NODE_H
#define BINARY_NODE_H

#include <string>
using namespace std;

class BinaryNode {
    string element;
    BinaryNode *left;
    BinaryNode *right;

    BinaryNode( const string & theElement, BinaryNode *lt, BinaryNode *rt )
        : element( theElement ), left( lt ), right( rt ) { }
    friend class BinarySearchTree;
};

#endif