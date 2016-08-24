#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <algorithm>
#include "middleearth.h"

using namespace std;

/** @brief The function called to calculate the distance between a list of cities in order
 *
 * This function computes the total distance of the cycle that starts at the 'start' parameter,
 * goes to each of the cities in the dests vector IN ORDER, and ends back at the 'start'
 * parameter
 * @param me Middle-earth world created which contains the dests and distances between cities
 * @param start First city to start and end at when calculating distances
 * @param dests Vector of strings, the strings being city names in the possible cities in the
 * Middle-Earth created
 * @return Float representing the total distance between the cities in order
 * @see main
 */
float computeDistance (MiddleEarth &me, string start, vector<string> dests);

/** @brief The function called to print out the list of cities given in
 *
 * This function will print out in order the list of cities in a vector given following
 * the format of city -> city -> city... The first and last city will be the same as start
 * @param start The first city to be printed as well as the last
 * @param dests The vector of strings of city names that will be printed out
 * @return Nothing
 * @see main
 */
void printRoute (string start, vector<string> dests);

/** @brief Main function for the traveling salesman problem
 *
 * Main function to take in 5 parameters for the creation of a world with cities in order to
 * calculate the minimum distance between a journey between X number of cities
 *@param argc Number of arguments passed into the function
 *@param argv The array of strings passed into the the function
 *@return The way to let the function know that it exited properly
 *@see computeDistance()
 *@see printRoute()
 */
int main (int argc, char **argv) {
   // check the number of parameters
    if ( argc != 6 ) {
        cout << "Usage: " << argv[0] << " <world_height> <world_width> "
             << "<num_cities> <random_seed> <cities_to_visit>" << endl;
        exit(0);
    }
    // we'll assume the parameters are all well-formed
    int width, height, num_cities, rand_seed, cities_to_visit;
    sscanf (argv[1], "%d", &width);
    sscanf (argv[2], "%d", &height);
    sscanf (argv[3], "%d", &num_cities);
    sscanf (argv[4], "%d", &rand_seed);
    sscanf (argv[5], "%d", &cities_to_visit);
    // Create the world, and select your itinerary
    MiddleEarth me(width, height, num_cities, rand_seed);
    vector<string> dests = me.getItinerary(cities_to_visit);
    sort(dests.begin()+1, dests.end());
    float bestDist = computeDistance(me, dests.front(), dests);
    vector<string> bestDests = dests;
     while(next_permutation(dests.begin()+1, dests.end())) {
      double newDist = computeDistance(me, dests.front(), dests);
      if (newDist < bestDist){
	bestDist = newDist;
	bestDests = dests;
      }
    }
    printRoute(bestDests.front(), bestDests);
    cout << computeDistance(me, bestDests.front(), bestDests) << endl;
    return 0;
}

// This method will compute the full distance of the cycle that starts
// at the 'start' parameter, goes to each of the cities in the dests
// vector IN ORDER, and ends back at the 'start' parameter.
float computeDistance (MiddleEarth &me, string start, vector<string> dests) {
  float sum = me.getDistance(start, dests.at(1));
  for (vector<string>::iterator itr = (dests.begin()+1); itr != (dests.end()-1); ++itr){
    sum = sum + me.getDistance(*itr, *(itr+1));
  }
  sum = sum + me.getDistance(dests.at(dests.size()-1),dests.front());
  return sum;
}

// This method will print the entire route, starting and ending at the
// 'start' parameter.  The output should be of the form:
// Erebor -> Khazad-dum -> Michel Delving -> Bree -> Cirith Ungol -> Erebor
void printRoute (string start, vector<string> dests) {
  for (vector<string>::iterator itr = dests.begin(); itr != dests.end(); ++itr){
    cout << *itr << " -> ";
  }
  cout << start << endl;
}
