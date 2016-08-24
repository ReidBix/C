/*
 * Reid Bixler
 * rmb3yz
 * CS 2150 Pre-Lab 9 threexinput.cpp
 * November 18, 2014
 */

#include <iostream>
#include <cstdlib>
#include "timer.cpp"

using namespace std;

extern "C" int threexplusone(int);


int  main () {
  int  x, n, col;
  double sum = 0;
  sum = 0;
  cout << "Please enter the number you want as parameter for the Collatz subroutine: ";
  cin >> x;
  cout << "Please enter the number you want as the number of times to call the subroutine: ";
  cin >> n;

  if (x <= 0 || n <= 0) {
    cerr << "The numbers must be positive integers.\n";
    return 1;
  }
  
  for (int i = 0; i < n; ++i){
    timer t;
    t.start();
    col = threexplusone(x);
    if(i == 0) {
      cout << "The number of steps in the Collatz for " << x << " is: " << col << endl;
    }
    t.stop();
    cout << "Iteration " << i << " ran in " << t.getTime()*1000 << " milliseconds" << endl;
    sum += t.getTime()*1000;
  }
  sum = sum/n;
  cout << "The average time of " << n << " iterations of " << x << " was: " << sum << " milliseconds" << endl; 
  return 0;
}
