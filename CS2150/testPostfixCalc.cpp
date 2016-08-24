/*
 *Reid Bixler
 *rmb3yz
 *September 16, 2014
 *CS 2150 Pre-Lab 3 testPostfixCalc.h
 */

#include <iostream>
#include "postfixCalculator.h"

using namespace std;

int main(){
  PostfixCalculator p;
  p.pushNum(1);
  p.pushNum(2);
  p.pushNum(3);
  p.pushNum(4);
  p.pushNum(5);
  p.add();
  p.add();
  p.add();
  p.add();
  cout << "Result is: " << p.getTopValue() << endl;
  PostfixCalculator p2;
  p2.pushNum(20);
  p2.pushNum(10);
  p2.subtract();
  p2.pushNum(-3);
  p2.pushNum(10);
  p2.subtract();
  p2.subtract();
  p2.pushNum(2);
  p2.subtract();
  cout << "Result is: " << p2.getTopValue() << endl;
  PostfixCalculator p3;
  p3.pushNum(-1);
  p3.pushNum(-2);
  p3.pushNum(-5);
  p3.pushNum(3);
  p3.multiply();
  p3.pushNum(2);
  p3.pushNum(-2);
  p3.multiply();
  p3.multiply();
  p3.multiply();
  p3.multiply();
  cout << "Result is: " << p3.getTopValue() << endl;
  PostfixCalculator p4;
  p4.pushNum(-1512);
  p4.pushNum(-12);
  p4.pushNum(-2);
  p4.divide();
  p4.divide();
  p4.pushNum(-2);
  p4.divide();
  p4.pushNum(3);
  p4.divide();
  cout << "Result is: " << p4.getTopValue() << endl;
  PostfixCalculator p5;
  p5.pushNum(-1);
  p5.negate();
  p5.negate();
  p5.negate();
  cout << "Result is: " << p5.getTopValue() << endl;
  return 0;
}
