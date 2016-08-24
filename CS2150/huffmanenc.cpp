/*
 * Reid Bixler
 * rmb3yz
 * CS 2150 Pre-Lab 9 huffmanenc.cpp
 * November 25, 2014
 */

//#include files
#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>
#include "heap.h"
#include "huffTreeNode.h"
#include <vector>

using namespace std;

//declarations for methods made later
void huffmanTree(huffTreeNode *h, int height, char codestring[], string codes[]);
void encode(string in, string out, string codes[]);

//Main code
int main(int argc, char **argv){
  //If more than 1 input parameter, yell at user
  if ( argc != 2) {
    cout << "Must supply the input file name as the one and only parameter" << endl;
    exit(1);
  }
  //Read file for the first time
  string line;
  ifstream file (argv[1]);
  heap hp;
  unordered_map<char, int> freqMap;
  //Put every character into an unordered map to calculate frequencies
  if (file.is_open()){
    while (getline(file,line)){
      int sizeOfLine = line.size();
      for (int i = 0; i < sizeOfLine; ++i){
	char c = line[i];
	int cInt = (int) c;
	if (cInt >= 32){
	  unordered_map<char, int>::const_iterator got = freqMap.find(c);
	  if (got == freqMap.end()){
	    freqMap.insert({{c,1}});
	  } else {
	    int prevFreq = got->second;
	    prevFreq++;
	    freqMap[c] = prevFreq;
	  }
	}
      }
    }
    //Go through the now calculated frequencies and put into a user-made heap (priority queue)
    for ( auto it = freqMap.begin(); it != freqMap.end(); ++it ){
      pair<char, int> x (it->first, it->second);
      if (it->second != 0){
	huffTreeNode *h = new huffTreeNode();
	h->setSym(get<0>(x));
	h->setFreq(get<1>(x));
	hp.insert(h);
      }
    }
    cout << endl;
    file.close();
    //Create the huffman tree, results in 1 node left
    int hpSize = hp.size()-1;
    for (int i = 0; i < hpSize; ++i){
      huffTreeNode* tRoot = new huffTreeNode();
      huffTreeNode* tLeft = hp.deleteMin();
      huffTreeNode* tRight = hp.deleteMin();
      tRoot->setLeftRight(tLeft, tRight);
      tRoot->setFreq((tLeft->getFreq()+tRight->getFreq()));      
      hp.insert(tRoot);
    }
    //Calculate the codes from the huffman tree given the 1 node, puts codes into an array of strings (max of 256 possible character combinations)
    huffTreeNode *huffStart = hp.findMin();
    int h = 0;
    char codestring[hpSize+1];
    string codes[256];
    huffmanTree(huffStart, h, codestring, codes);
    //Encode the file into an output file given the new codes
    string in = argv[1];
    string out = "myEncode.txt";
    encode (in, out, codes);
    //Print out the new output file
    ifstream newOut(out);
    cout << newOut.rdbuf();
  }
  //If couldn't open file, end
  else cout << "Unable to open file";
  return 0;
}

//Huffman tree method to calculate the strings of binary based off of frequencies. Uses recursion on the tree to go down based off of most frequent to least frequent.
void huffmanTree(huffTreeNode *h, int height, char codestring[], string codes[]){
  if ((h->getLeft() == NULL && (h->getRight() == NULL))){
    codestring[height] = 0;
    string str(codestring);
    codes[h->getSym()] = str;
    } else {
      codestring[height] = '0';
      huffmanTree(h->getLeft(), height+1, codestring, codes);
      codestring[height] = '1';
      huffmanTree(h->getRight(), height+1, codestring, codes);
    }
}

//Encode method to encode the input stream into the output stream. Uses the C io rather than C++. Results in everything that is eventually printed.
void encode(string in, string out, string codes[]){
  char c;
  string s;
  int totEncSym = 0;
  int totDisSym = 0;
  int compressBits = 0;
  FILE *inFile = fopen(in.c_str(), "r");
  if (inFile == NULL) {
    cout << "File '" << in << "' does not exist!" << endl;
    exit(2);
  }
  FILE *outFile = fopen(out.c_str(), "w");
   for (int l = 0; l < 256; ++l){
      if (codes[l].size() != 0){
	string str;
	str = str + (char)l;
	str = str + " ";
	str = str + codes[l];
	str = str + "\n";
	fprintf(outFile, "%s", str.c_str());
	++totDisSym;
      }
    }
   fprintf(outFile, "----------------------------------------\n");
   while ( (c = fgetc(inFile)) != EOF ){
     if (c > 31) {
       string code = codes[c];
       fprintf(outFile, "%s", code.c_str());
       if (c == 32){
	 fprintf(outFile, " \n");
       } else {
	 fprintf(outFile, " ");
       }
       ++totEncSym;
       compressBits = compressBits + code.size();
     }
   }
   fclose(inFile);
   fprintf(outFile, "\n----------------------------------------\n");
   fprintf(outFile, "%s %d %s", "There are a total of", totEncSym, "that are encoded.\n");
   fprintf(outFile, "%s %d %s", "There are", totDisSym, "distinct symbols used.\n");
   int originalBits = 8 * totEncSym;
   fprintf(outFile, "%s %d %s", "There were", originalBits, "in the original file.\n");
   fprintf(outFile, "%s %d %s", "There were", compressBits, "in the compressed file.\n");
   float ratio = (float)originalBits / compressBits;
   fprintf(outFile, "%s %f%s", "This gives a compression ratio of", ratio, ".\n");
   float cost = (float)compressBits / totEncSym;
   fprintf(outFile, "%s %f %s", "The cost of the Huffman tree is", cost, "bits per character.\n");
   fclose(outFile);
}

