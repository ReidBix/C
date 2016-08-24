/*
 * Reid Bixler
 * rmb3yz
 * CS 2150 Pre-Lab 9 heap.h
 * November 25, 2014
 */

//Code taken from CS 2150 and changed to adhere to my implementation for a heap
#ifndef HEAP_H
#define HEAP_H

#include <vector>
#include "huffTreeNode.h"

using namespace std;

class heap {
public:
    heap();
    heap(vector<huffTreeNode*> vec);
    ~heap();

    void insert(huffTreeNode*);
    huffTreeNode* findMin();
    huffTreeNode* deleteMin();
    unsigned int size();
    void makeEmpty();
    bool isEmpty();
    void print();

private:
    vector<huffTreeNode*> hp;
    unsigned int heap_size;
    void percolateUp(int hole);
    void percolateDown(int hole);
};

#endif
