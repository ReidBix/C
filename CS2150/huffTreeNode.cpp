/*
 * Reid Bixler
 * rmb3yz
 * CS 2150 Pre-Lab 9 huffTreeNode.cpp
 * November 25, 2014
 */

//Implementation of huffman tree node for use in huffmanenc.cpp
#include <iostream>
#include "huffTreeNode.h"

using namespace std;

huffTreeNode::huffTreeNode(){
  freq = 0;
  sym = 0;
  left = NULL;
  right = NULL;
}

huffTreeNode::huffTreeNode(char s, int f){
  sym = s;
  freq = f;
  left = NULL;
  right = NULL;
}

char huffTreeNode::getSym(){
  return sym;
}

int huffTreeNode::getFreq(){
  return freq;
}

void huffTreeNode::setSym(char s){
  sym = s;
}

void huffTreeNode::setFreq(int f){
  freq = f;
}

void huffTreeNode::setLeftRight(huffTreeNode *hl, huffTreeNode *hr){
  left = hl;
  right = hr;
}

huffTreeNode* huffTreeNode::getLeft(){
  return left;
}

huffTreeNode* huffTreeNode::getRight(){
  return right;
}
