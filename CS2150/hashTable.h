/*
 * Reid Bixler
 * rmb3yz
 * October 21, 2014
 * CS 2150 Pre-Lab 6 hashTable.h
 */

#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <vector>
#include <list>
#include <string>
#include <iostream>
using namespace std;

class TestHashTable;

class hashTable {
public:
  hashTable();
  ~hashTable();

  bool insert(string &s);
  bool search(string &s);
  int getTableSize();
  void makeEmpty();
  void printHashTable();
  
private:
  vector<list<string> > table;
  int sizeOfTable;
  unsigned int tableHash(string &s);
  void rehash();
  friend class TestHashTable;
};

unsigned int hash(string &s, int sizeOfTable);

bool checkprime(unsigned int p);

int getNextPrime (unsigned int n);

#endif

