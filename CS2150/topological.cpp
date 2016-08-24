#include <iostream>
#include <vector>
#include <stack>
#include <list>
#include <fstream>
#include <stdlib.h>
#include <string>
#include <stdio.h>
#include <sstream>

using namespace std;

/** @brief A class description for a topological graph
 *
 * This class allows for the topological sorting of a graph given some edges
 */
class topoGraph {
public:

  /** @brief Creates a new topological graph for a given size.
   *
   * This function creates a topological graph given a number that will be the
   * size of the number of elements in the graph
   * @param x The number of elements in the topological graph
   */
  topoGraph(int x);


  /** @brief Creates a new edge given two ints for the graph.
   *
   * This function creates a new edge given two ints for the topological graph
   * in order to createa  map that is topologically sorted
   * @param x First parameter for the edge, X will be bound by Y
   * @param y Second parameter for the edge, Y will the bounds of X
   * @return Nothing
   */
  void addEdge(int x, int y);

  /** @brief Does a topological sort on the topological graph.
   *
   * This function will call the topological function in order to properly
   * and topologically order the stack of elements
   * @return Will return the sorted stack of elements (in reverse order because
   * it is a stack)
   */
  stack<int> topoSort();

  /** @brief The function called by the topological sort to recursively sort
   *
   * This function computes the indices of the given elements based off of an
   * adjacency map that will tell whether an element has been accessed (prevA)
   * and then recursively calls on the new element
   * @param x The location of the element being called upon
   * @param s The sorted stack of elements so far
   * @param prevA The previously accessed elements (adjacency list)
   * @return Nothing
   */
  void topoSortFunc(int x, stack<int> &s, bool prevA[]);

private:
  int numV; /** The number of vertices in the graph */
  list<int> *pointersToNodes; /**An array of list of ints which will be pointers to the nodes */
};

int main (int argc, char **argv) {
    // verify the correct number of parameters
    if ( argc != 2 ) {
        cout << "Must supply the input file name as the one and only parameter" << endl;
        exit(1);
    }
    // attempt to open the supplied file
    ifstream file(argv[1], ifstream::binary);
    // report any problems opening the file and then exit
    if ( !file.is_open() ) {
        cout << "Unable to open file '" << argv[1] << "'." << endl;
        exit(2);
    }
    // read in two strings
    list<string> listt;
    string line1, line2;
    file >> line1;
    file >> line2;
    while (line1 != "0" && line2 != "0"){
      // output those strings
      //cout << line1 << " " << line2 << endl;
      listt.push_back(line1);
      listt.push_back(line2);
      // string comparison done with ==, but not shown here
      file >> line1;
      file >> line2;
    }
    listt.sort();
    listt.unique();
    int listSize = listt.size();
    string *sArr = new string[listSize];
    int c = 0;
    for(list<string>::iterator itr = listt.begin(); itr != listt.end(); ++itr){
    sArr[c] = *itr; 
    ++c;
    }

    file.close();

    ifstream file2(argv[1], ifstream::binary);
    // report any problems opening the file and then exit
    if ( !file2.is_open() ) {
        cout << "Unable to open file '" << argv[1] << "'." << endl;
        exit(2);
    }
    // read in two strings

    topoGraph tg(listSize);
    string Line1, Line2;
    file >> line1;
    file >> line2;
    while (line1 != "0" && line2 != "0"){
      // output those strings
      cout << line1 << " " << line2 << endl;
      for (int i = 0; i < sArr->size(); ++i){
	if (sArr[i] == line1){
	  for (int j = 0; j < sArr->size(); ++j){
	    if(sArr[j] == line2){
	      tg.addEdge(i, j);
	    }
	  }
	}
      }
      // string comparison done with ==, but not shown here
      file >> line1;
      file >> line2;
    }
    stack<int> ss = tg.topoSort();
    stack<string> sS;
    while (ss.empty() == false){
      sS.push(sArr[ss.top()]);
      ss.pop();
    }
    while (sS.empty() == false){
      cout << sS.top() << " ";
      sS.pop();
    }
    cout << endl;
    
    delete [] sArr;
    // close the file before exiting
    file.close();
}


topoGraph::topoGraph(int x){
  this->numV = x;
  pointersToNodes = new list<int>[numV];
}

void topoGraph::addEdge(int x, int y){
  pointersToNodes[x].push_back(y);
}

stack<int> topoGraph::topoSort(){
  stack<int> s;
  bool *prevA = new bool[numV];
  stringstream ss(stringstream::in | stringstream::out);
  for (int i = 0; i < numV; ++i){
    prevA[i] = false;
  }
  for (int j = 0; j < numV; ++j){
    if (prevA[j] == false){
      topoSortFunc(j, s, prevA);
    }
  }
  return s;
}

void topoGraph::topoSortFunc(int x, stack<int> &s, bool prevA[]){
  prevA[x] = true;
  
  for(list<int>::iterator itr = pointersToNodes[x].begin(); itr != pointersToNodes[x].end(); ++itr){
    if (!(prevA[*itr])){
      topoSortFunc(*itr, s, prevA);
    }
}
  s.push(x);
}
