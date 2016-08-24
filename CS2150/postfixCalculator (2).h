/*
 *Reid Bixler
 *rmb3yz
 *September 19, 2014
 *CS 2150 Post-Lab 3 postfixCalculator.h
 */

#ifndef POSTFIXCALCULATOR_H
#define POSTFIXCALCULATOR_H

#include <iostream>
#include <string>
#include "Stack.h"

using namespace std;

class PostfixCalculator {
public:
    PostfixCalculator();

    void add();
    void subtract();
    void multiply();
    void divide();
    void negate();
    void pushNum(int x);   
    int getTopValue();
    void evaluate(string s);
    
private:
    Stack stack;
};

#endif
