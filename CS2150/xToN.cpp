/**
 *Reid Bixler
 *rmb3yz
 *September 2, 2014
 *CS 2150 Pre-Lab 1
 */

#include <iostream>
using namespace std;

// Recursive function for x to the n with ONLY 2 inputs
int xToN(int x, int n) {
  // Base case when n = 0
  if (n == 0){
    return 1;
  }
  // Final return
  else if (n == 1){
    return x;
  }
  // Recursive case
  else {
    return x * x * xToN(x, n-2);
  }
}

// Implementation of the xToN method in the main method
int main ( ) {
  // Using the same format as the example in the tutorial
  int x, n, z;
  cin >> x;
  cin >> n;
  z = xToN(x, n);
  cout << x << " ^ " << n << " = " << z << endl;
  return 0;
}
