/**
 *Reid Bixler
 *rmb3yz
 *September 2, 2014
 *CS 2150 In-Lab 1 LifeCycle.h
 */

#ifndef LIFECYCLE_H
#define LIFECYCLE_H
#include <string>

using namespace std;


// ---------------------------------------------------  class definition
class MyObject {
public:
    static int numObjs;
    MyObject(const char *n = "--default--");      // default constructor
    MyObject(const MyObject& rhs);                // copy constructor
    ~MyObject();                                  // destructor
    string getName() const {
        return name;
    }
    void setName(const string newName) {
        name = newName;
    }
    friend ostream& operator<<(ostream& output, const MyObject& obj);
private:
    string name;
    int id;
};


#endif
