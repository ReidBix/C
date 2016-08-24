/*
 * Reid Bixler
 * rmb3yz
 * CS 2150 Pre-Lab 9 huffTreeNode.h
 * November 25, 2014
 */

//Implementation of a node for the huffman tree. Has a symbol, frequency, and pointers to its two children.
#ifndef HUFFTREENODE_H
#define HUFFTREENODE_H

using namespace std;

class huffTreeNode {
 public:
  huffTreeNode();
  huffTreeNode(char s, int f);
  char getSym();
  int getFreq();
  void setSym(char s);
  void setFreq(int f);
  void setLeftRight(huffTreeNode* hl, huffTreeNode *hr);
  huffTreeNode* getLeft();
  huffTreeNode* getRight();

 private:
  char sym;
  int freq;
  huffTreeNode *left;
  huffTreeNode *right;
};

#endif


