/*
 *Reid Bixler
 *rmb3yz
 *September 9, 2014
 *CS 2150 Pre-Lab 2 ListNode.h
 */


/*
 * Filename: ListNode.h
 * Description: ListNode class definition
 */

#ifndef LISTNODE_H
#define LISTNODE_H

#include <iostream>

// next line needed because NULL is part of std namespace
using namespace std;

class ListNode {
public:
    ListNode();                 // Constructor

    friend ostream& operator<<(ostream& output, const ListNode& node);
      

private:
    int value;
    ListNode *next, *previous;	// for doubly linked lists

    // List needs to be able to access/change ListNode's next and
    // previous pointers
    friend class List;

    // ListItr needs to access/change ListNode as well
    friend class ListItr;
    // Not writing a destructor is fine in this case since there is no
    // dynamically allocated memory in this class.  No constructor is
    // necessary, as an object will be set up by the List class.

    friend class ListTest;

};

#endif


/* #ifndef LIFECYCLE_H */
/* #define LIFECYCLE_H */
/* #include <string> */

/* using namespace std; */


/* // ---------------------------------------------------  class definition */
/* class MyObject { */
/* public: */
/*     static int numObjs; */
/*     MyObject(const char *n = "--default--");      // default constructor */
/*     MyObject(const MyObject& rhs);                // copy constructor */
/*     ~MyObject();                                  // destructor */
/*     string getName() const { */
/*         return name; */
/*     } */
/*     void setName(const string newName) { */
/*         name = newName; */
/*     } */
/*     friend ostream& operator<<(ostream& output, const MyObject& obj); */
/* private: */
/*     string name; */
/*     int id; */
/* }; */


/* #endif */
