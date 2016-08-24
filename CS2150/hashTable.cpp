/*
 * Reid Bixler
 * rmb3yz
 * October 21, 2014
 * CS 2150 Pre-Lab 6 hashTable.cpp
 */

#include <iostream>
#include "hashTable.h"
#include <algorithm>

using namespace std;

hashTable::hashTable(){
  table.resize(3);
  sizeOfTable = 0;
}

hashTable::~hashTable(){
  this->makeEmpty();
  this->table.resize(0);
}

bool hashTable::insert(string &s){
  list<string> &bucket = table[tableHash(s)];
  if(find(bucket.begin(), bucket.end(), s) != bucket.end()) {
    return false;
  } else {
    bucket.push_back(s);
    if( sizeOfTable++ > table.size()){
      this->rehash();
    }
    return true;
  }
}

bool hashTable::search(string &s){
  list<string> &bucket = table[tableHash(s)];
  bool found = find(bucket.begin(), bucket.end(), s) != bucket.end();
  return found;
}

void hashTable::makeEmpty(){
  for(int i = 0; i < this->table.size(); ++i){
    table[i].clear();
  }
}

int hashTable::getTableSize(){
  cout << "Max size of hashtable: " << table.size() << endl;
  return sizeOfTable;
}

unsigned int hashTable::tableHash(string &s){
  int hashValue = hash(s, this->table.size());
  hashValue = hashValue%(this->table.size());
  if(hashValue < 0){
    hashValue = hashValue + (this->table.size());
  }
  return hashValue;
}


void hashTable::printHashTable(){
  list<string>::iterator itr;
  for (int i = 0; i < (this->table.size()); ++i){
      int print = 0;
      for(itr = this->table[i].begin(); itr != this->table[i].end(); ++itr){
	cout<<(*itr)<<" ";
	print=1;
      }
      if(print){
	cout << " 'in bucket: " << i << "'" << endl;
      }
    }
}

void hashTable::rehash(){
  //cout << "HELLO, FROM REHASH!" << endl;
  vector<list<string> > originalTable = this->table;
  table.resize(getNextPrime((this->table.size())*2));
  this->makeEmpty();
  sizeOfTable = 0;
  for (int i = 0; i < originalTable.size(); ++i){
    list<string>::iterator iterator = originalTable[i].begin();
    list<string>::iterator end = originalTable[i].end();
    while(iterator != end){
      string element = *iterator;
      insert(element);
      ++iterator;
    }
  }
}

unsigned int hash(string &s, int sizeOfTable){
  int hashValue = 0;
  int stringLength = s.length();
  for (int i = 0; i < stringLength; ++i){
    hashValue = s[i] + (37 * hashValue);
  }
  hashValue = hashValue%sizeOfTable;
  return hashValue;
}

bool checkprime(unsigned int p) {
    if ( p <= 1 )
        return false;
    if ( p == 2 )
        return true;
    if ( p % 2 == 0 )
        return false;
    for ( int i = 3; i*i <= p; i += 2 )
        if ( p % i == 0 )
            return false;
    return true;
}

int getNextPrime (unsigned int n) {
    while ( !checkprime(++n) );
    return n;
}
