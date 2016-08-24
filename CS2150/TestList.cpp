#include <iostream>
#include "List.h"
#include "ListNode.h"
#include "ListItr.h"

using namespace std;

int main () {
  //ListNode
  cout << "Creating 3 ListNodes LN1, LN2, and LN3" << endl;
  ListNode LN1;
  ListNode LN2;
  ListNode LN3;
  cout << "Printing out the contents of newly initialized ListNodes" << endl;
  cout << "LN1" << LN1 << endl;
  cout << "LN2" << LN2 << endl;
  cout << "LN3" << LN3 << endl;


  //List
  cout << "Initializing 2 Lists L1 and L2" << endl;
  List L1;


  cout << "Inserting value of 1 at the tail of L1" << endl;
  L1.insertAtTail(1);


  List L2;
  cout << "Creating List L3 from List L2" << endl;
  List L3(L2);
  cout << "Testing method isEmpty on empty List L2" << endl;
  cout << L2.isEmpty() << endl; 

  cout << "Attempting use of copy assignment operator '=' with L2 = L1" << endl;
  L2 = L1;
  cout << "Testing method isEmpty on non-empty List L2" << endl;
  cout << L2.isEmpty() << endl; 
  cout << "Testing method isEmpty on non-empty List L1" << endl;
  cout << L1.isEmpty() << endl;

  
  cout << "Returning the iterator that points to the ListNode in the first position of L1" << endl;
  cout << (L1.first()) << endl;

  L1.insertAtTail(3);
  L1.insertAtTail(4);
  L1.insertAtTail(5);
  cout << "Size of List L1" << L1.size() << endl;
  cout << "Returning the iterator that points to the ListNode in the last position of L1" << endl;
  cout << (L1.last()) << endl;


  //ListIter
  cout << "Using ListNode LN1" << endl;
  cout << "Creating ListItr LI1" << endl;
  ListItr LI1;
  cout << "Creating ListItr LI2 with LN1 as current" << endl;
  ListItr LI2 = ListItr(&LN1);
  cout << "End of test" << endl;

  return 0;
}
