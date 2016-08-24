/*
 * Reid Bixler
 * rmb3yz
 * September 23, 2014
 * CS 2150 Pre-Lab 4 prelab4.cpp
 */

#include <iostream>
#include <cmath>
#include <string>
#include <limits.h>

using namespace std;

void sizeOfTest();
void outputBinary(int x);
void overflow();

int main(){
  sizeOfTest();
  cout << endl;
  int x;
  cout << "Type an integer to be converted to binary: " << endl;
  cin >> x;
  outputBinary(x);
  cout << endl;
  overflow();
  cout << endl;
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

void overflow(){
  int maxInt = INT_MAX;
  cout << "Created maximum value for int: " << maxInt << endl;
  cout << "Attempting to add 1 to maxInt" << endl;
  maxInt = maxInt + 1;
  cout << "Success!" << endl;
  cout << "The new int is: " << maxInt << endl;
  cout << "This new int is when the int loops from the max possible int to the minimum possible int" << endl;
}



//Your magic (32 bit) floating point number is 8.796875
//This is the number that needs to be converted to (little endian) binary,
//and expressed in hexadecimal.

//Your other magic floating point number is, in hex, 0x00c01ec2
//This is the number that needs to be converted to a (32 bit) floating point number.
//Note that the hexadecimal printed above is in little-endian format!
