/*
 * Reid Bixler
 * rmb3yz
 * October 21, 2014
 * CS 2150 Post-Lab 6 wordPuzzle.cpp
 */

// 3x3 time words.txt: 0.000473 seconds
// 4x7 time words.txt: 0.001836 seconds
// 50x50 time words.txt: 0.210134 seconds
// 140x70 time words.txt: 1.031285 seconds
// 250x250 time words.txt: 6.465378 seconds
// 300x300 time words.txt: 7.922125 seconds

// 3x3 time words2.txt: 0.000126 seconds
// 4x7 time words2.txt: 0.000817 seconds
// 50x50 time words2.txt: 0.073291 seconds
// 140x70 time words2.txt: 0.331931 seconds
// 250x250 time words2.txt: 2.750226 seconds
// 300x300 time words2.txt: 3.913906 seconds

//Worst case Big Theta(n)
//Hopeful case Big Theta(# elements / table size)

#include <iostream>
#include <fstream>
#include <string>
#include <stdlib.h>
#include "hashTable.h"
#include "timer.h"
#include <iomanip>
#include <sstream>

using namespace std;

#define MAXROWS 500
#define MAXCOLS 500
char table[MAXROWS][MAXCOLS];

bool readInTable (string filename, int &rows, int &cols);
bool readInDictionary(string filename, hashTable &ht);
char* getWordInTable (int startRow, int startCol, int dir, int len, int numRows, int numCols);

int main(int argc, char **argv){
  if (argc != 3) {
    cout << "Wrong number of input files! Please input ' ./a.out <dictionary_file> <grid_file> '" << endl;
    exit(1);
  }
  hashTable ht;
  hashTable wordsFound;
  bool result1 = readInDictionary(argv[1], ht);
  if (!result1){
    cout << "Error reading in dictionary file!" << endl;
    exit(1);
  }
  int rows, cols;
  bool result2 = readInTable(argv[2], rows, cols);
  if (!result2){
    cout << "Error reading in grid file!" << endl;
    exit(1);
  }
  int totalFound = 0;
  timer t;
  stringstream sstream;
  bool found;
  t.start();
  for (int i = 0; i < rows; ++i){
    for (int j = 0; j < cols; ++j){
      for (int k = 0; k < 8; ++k){
	for (int l = 3; l < 23; ++l){
	  string s(getWordInTable(i,j,k,l,rows,cols));
	  found = ht.search(s);
	  if (found){
	    if (!(s.length() < 3)){
	      if (s.length() == l){
		totalFound++;
		switch(k) {
		case 0:
		  sstream << "N ";
		  break;
		case 1:
		  sstream << "NE";
		  break;
		case 2:
		  sstream << "E ";
		  break;
		case 3:
		  sstream << "SE";
		  break;
		case 4:
		  sstream << "S ";
		  break;
		case 5:
		  sstream << "SW";
		  break;
		case 6:
		  sstream << "W ";
		  break;
		case 7:
		  sstream << "NW";
		  break;
		}
	        sstream << "(" << i << ", " << j << "):\t" << s << endl;
	      }
	    }
	  }
	}
      }
    }
  }
  t.stop();
  cout << sstream.str() ;
  cout << totalFound << " words found" << endl;
  cout << "Found all words in " << t << " seconds" << endl;
  int intTime = (int) (t.getTime() * 1000);
  cout << intTime << endl;
  return 0;
}

bool readInTable (string filename, int &rows, int &cols) {
    string line;
    ifstream file(filename.c_str());
    if ( !file.is_open() )
        return false;
    file >> rows;
    getline (file,line);
    file >> cols;
    getline (file,line);
    getline (file,line);
    file.close();
    int pos = 0;
    for ( int r = 0; r < rows; r++ ) {
        for ( int c = 0; c < cols; c++ ) {
            table[r][c] = line[pos++];
        }
    }
    return true;
}

bool readInDictionary(string filename, hashTable &ht){
  string line;
  ifstream file(filename.c_str());
  if (!file.is_open() )
    return false;
  while (getline (file,line) )
    {
      ht.insert(line);
    }
  file.close();
  return true;
}

char* getWordInTable (int startRow, int startCol, int dir, int len,
                      int numRows, int numCols) {
    static char output[256];
    if ( len >= 255 )
        len = 255;
    int pos = 0, r = startRow, c = startCol;
    for ( int i = 0; i < len; i++ ) {
        if ( (c >= numCols) || (r >= numRows) || (r < 0) || (c < 0) )
            break;
        output[pos++] = table[r][c];
        switch (dir) {
            case 0:
                r--;
                break;
            case 1:
                r--;
                c++;
                break;
            case 2:
                c++;
                break;
            case 3:
                r++;
                c++;
                break;
            case 4:
                r++;
                break;
            case 5:
                r++;
                c--;
                break; 
            case 6:
                c--;
                break;
            case 7:
                r--;
                c--;
                break;
        }
    }
    output[pos] = 0;
    return output;
}








