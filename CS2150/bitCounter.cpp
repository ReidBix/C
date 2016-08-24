/*
 * Reid Bixler
 * rmb3yz
 * September 26, 2014
 * CS 2150 Post-Lab 4 bitCounter.cpp
 */

#include <iostream>
#include <cstdlib>

using namespace std;

int bitCounter(int num);

int main(int argc, char **argv) {
  if (argc == 2){ 
  string s(argv[1]); 
  int input = atoi(s.c_str());
    cout << "The number of 1's in the binary representation of " << input << " is " << bitCounter(input) << endl;
  } else {
    cout << "Error: wrong number of parameters, please only give one" << endl;
    exit(-1); 
  }
  return 0;
}

int bitCounter(int num) {
  if (num == 0) {
    return 0;
  }
  else if (num == 1){
    return 1;
  }
  else if (num%2 == 0){
    return bitCounter(num/2);
  }
  else if (num%2 == 1){
    return bitCounter(num/2) + 1;
  } else {
    return -1;
  }
}
