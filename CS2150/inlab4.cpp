/*
 * Reid Bixler
 * rmb3yz
 * September 23, 2014
 * CS 2150 In-Lab 4 inlab4.cpp
 */

#include <iostream>
#include <cmath>
#include <string>
#include <limits.h>
#include <cfloat>
#include <climits>
#include <stdint.h>

using namespace std;


void sizeOfTest();
void outputBinary(int x);

const int ROW = 6;
const int COL = 5;

int main(){
  sizeOfTest();
  int intZero = 0;
  int intOne = 1;
  int unIntZero;
  int unIntOne;
  float floatZero = 0.0;
  float floatOne = 1.0;
  double doubleZero = 0.0;
  double doubleOne = 1.0;
  char charZero = '0';
  char charOne = '1';
  bool boolFalse = false;
  bool boolTrue = true;
  int *intPointer = NULL;
  char *charPointer = NULL;
  double *doublePointer = NULL;
  cout << intZero << intOne << unIntZero << unIntOne << floatZero << floatOne << doubleZero << doubleOne << charZero << charOne << boolFalse << boolTrue << intPointer << charPointer << doublePointer << endl;



  //NEXT PART ON ARRAYS
  int IntArray[10];
  char CharArray[10];

  int IntArray2D[ROW][COL];
  char CharArray2D[ROW][COL];
  
  for (int i = 0; i < sizeof(IntArray);++i){
    IntArray[i] = i;
  }
  for (int i = 0; i < sizeof(CharArray);++i){
    IntArray[i] = i;
  }
  for (int i = 0; i < ROW;++i){
    for (int j = 0; j < COL; ++j){
      IntArray2D[i][j] = i * j;
    }
  }
  for (int i = 0; i < ROW;++i){
    for (int j = 0; j < COL; ++j){
      CharArray2D[i][j] = i * j;
    }
  }





  return 0;
}


void sizeOfTest(){
  int a, b;
  a = 1;
  cout << "The size of an int is: " << sizeof(a) << endl;
  cout << "The size of an unsigned int is: " << sizeof(b) << endl;
  float c;
  cout << "The size of a float is: " << sizeof(c) << endl;
  double d;
  cout << "The size of a double is: " << sizeof(d) << endl;
  char e;
  cout << "The size of a char is: " << sizeof(e) << endl;
  bool f;
  cout << "The size of a bool is: " << sizeof(f) << endl;
  int *g;
  cout << "The size of an int pointer is: " << sizeof(g) << endl;
  char *h;
  cout << "The size of a char pointer is: " << sizeof(h) << endl;
  double *i;
  cout << "The size of a double pointer is: " << sizeof(i) << endl;
  float floatMax = FLT_MAX;
  cout << "The max value for a float is: " << floatMax << endl;
  double doubleMax = DBL_MAX;
  cout << "The max value for a double is: " << doubleMax << endl;
  char charMax = INT8_MAX;
  int charCast = (int) charMax;
  cout << "The max value for a char is: " << charCast << endl;

  
}

void outputBinary(int x){
  int value = x;
  int power = 31;
  int count = 0;
  string binary = "";
  while (power >= 0){
    int twoPower = pow(2,power);
    if (x - twoPower >= 0){
      x = x - twoPower;
      binary = binary + '1';
    } else {
      binary = binary + '0';
    }
    count++;
    power--;
    if (count == 4){
      binary = binary + ' ';
      count = 0;
    }
  }
  cout << "The number " << value << " in binary is: " <<  binary << endl;
}
