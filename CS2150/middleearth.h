#include <iostream>
#include <vector>
#include <string>
#include <map>

#ifndef MIDDLEEARTH_H
#define MIDDLEEARTH_H

using namespace std;

class MiddleEarth {
private:
    int num_city_names, xsize, ysize;
    vector<float> xpos, ypos;
    vector<string> cities;
    float *distances;
    map<string, int> indices;

public:

    /** @brief Creates a new MiddleEarth.
     *
     * This function creates a new Middle-Earth given certain sizes, cities,
     * and seeds.
     * @param xsize Size of the x value of Middle-Earth
     * @param ysize Size of the y value of Middle-Earth
     * @param numcities Number of cities that will be contained in Middle-Earth
     * @param seed Seed of the initial world (will be random)
     */
    MiddleEarth (int xsize, int ysize, int numcities, int seed);

    /** @brief Destructor for a created Middle-Earth
     *
     * This function destroys a previously created Middle-Earth
     */
    ~MiddleEarth();
    
    /** @brief Prints out info on the created Middle-Earth
     *
     * This function prints out all info associated with a previously
     * created Middle-Earth
     * @return nothing
     */
    void print();

    /** @brief Prints a tab-separated table of the distances
     *
     * This function creates a prints a tab-seperated table based off of
     * distances in the cities of Middle-Earth
     * @return Nothing
     */
    void printTable();

    /** @brief Computes and returns distance between 2 cities
     *
     * This function computes the distance between two cities using a
     * hash table such that the method call is O(1)
     * @return The distance between the two passed values
     * @param city1 First city to be used
     * @param city2 Second city to be used
     */
    float getDistance (string city1, string city2);

    /** @brief Calculates the itinerary for cities to travel to
     *
     * This function computes the itinerary for the cities to travel to
     * given that the first city will be thte start and end point
     * @return The list of cities to travel to
     * @param length Length of journey
     */
    vector<string> getItinerary(unsigned int length);
};

#endif
