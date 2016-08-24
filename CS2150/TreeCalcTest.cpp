/*
 * Reid Bixler
 * rmb3yz
 * October 7, 2014
 * CS 2150 Pre-Lab 5 TreeCalc.h
 */

#include <iostream>
#include "TreeCalc.h"

using namespace std;

int main() {
    TreeCalc tester;
    // read expression input from the user
    tester.readInput();
    // print out the output in postorder, in order, preorder forms
    tester.printOutput();
    // calculate the result of the expression tree
    cout << "The result of the expression tree is "
         << tester.calculate() << endl;
    return 0;
}
