/*
 * Reid Bixler
 * rmb3yz
 * CS 2150 Pre-Lab 9 heap.cpp
 * November 25, 2014
 */

//Also code taken from CS 2150 and changed slightly for my implementation of heap
#include <iostream>
#include "heap.h"
#include <utility>
#include "huffTreeNode.h"
using namespace std;

// default constructor
heap::heap() : heap_size(0) {
  huffTreeNode *h = new huffTreeNode();
  hp.push_back(h);
}

// builds a heap from an unsorted vector
heap::heap(vector<huffTreeNode*> vec) : heap_size(vec.size()) {
    hp = vec;
    hp.push_back(hp[0]);
    huffTreeNode *h = new huffTreeNode();
    hp.push_back(h);
    hp[0] = h;
    for ( int i = heap_size/2; i > 0; i--)
      percolateDown(i);
}

// the destructor doesn't need to do much
heap::~heap() {
}

void heap::insert(huffTreeNode* x) {
    // a vector push_back will resize as necessary
    hp.push_back(x);
    // move it up into the right position
    percolateUp(++heap_size);
}

void heap::percolateUp(int hole) {
    // get the value just inserted
  huffTreeNode *h = hp[hole];
    // while we haven't run off the top and while the
    // value is less than the parent...
  for ( ; (hole > 1) && (h->getFreq()) < (hp[hole/2]->getFreq()); hole /= 2 )
        hp[hole] = hp[hole/2]; // move the parent down
    // correct position found!  insert at that spot
  hp[hole] = h;
}


huffTreeNode* heap::deleteMin() {
    // make sure the heap is not empty
    if ( heap_size == 0 )
        throw "deleteMin() called on empty heap";
    // save the value to be returned
    huffTreeNode *ret = hp[1];
    // move the last inserted position into the root
    hp[1] = hp[heap_size--];
    // make sure the vector knows that there is one less element
    hp.pop_back();
    // percolate the root down to the proper position
    percolateDown(1);
    // return the old root node
    return ret;
}

void heap::percolateDown(int hole) {
    // get the value to percolate down
  huffTreeNode *h = hp[hole];
    // while there is a left child...
    while ( hole*2 <= heap_size ) {
        int child = hole*2; // the left child
        // is there a right child?  if so, is it lesser?
        if ( (child+1 <= heap_size) && ((hp[child+1]->getFreq()) < (hp[child]->getFreq())) )
            child++;
        // if the child is greater than the node...
        if ( (h->getFreq()) > (hp[child]->getFreq()) ) {
            hp[hole] = hp[child]; // move child up
            hole = child;             // move hole down
        } else
            break;
    }
    // correct position found!  insert at that spot
    hp[hole] = h;
}

huffTreeNode* heap::findMin() {
    if ( heap_size == 0 )
        throw "findMin() called on empty heap";
    return hp[1];
}

unsigned int heap::size() {
    return heap_size;
}

void heap::makeEmpty() {
    heap_size = 0;
}

bool heap::isEmpty() {
    return heap_size == 0;
}

void heap::print() {
  // cout << "(" << get<1>(heap[0]) << ") ";
  //   for ( int i = 1; i <= heap_size; i++ ) {
  //     cout << get<1>(heap[i]) << " ";
  //       // next line from from http://tinyurl.com/mf9tbgm
  //       bool isPow2 = (((i+1) & ~(i))==(i+1))? i+1 : 0;
  //       if ( isPow2 )
  //           cout << endl << "\t";
  //   }
  //   cout << endl;

    int newline = 2;
    int leadSpaces = 30;
    int inbetweenSpaces = (leadSpaces - 2) / 2;
    for (int sp = 1; sp <= leadSpaces; sp++)
      cout << " ";
    for (int i = 1; i <= heap_size; i++)
      {
	if (i == newline)
	  { 
	    cout << endl;;
	    inbetweenSpaces = leadSpaces;
	    leadSpaces = (leadSpaces - 2) / 2;
	    for (int sp = 1; sp <= leadSpaces; sp++)
	      cout << " ";
	    newline *= 2;
	  }
	if ((hp[i]->getFreq()) < 10)
	  cout << (hp[i]->getFreq()) << " ";
	else
	  cout << (hp[i]->getFreq());
	for (int sp = 1; sp <= inbetweenSpaces; sp++)
	  cout << " ";
      }
    cout << endl;
}
