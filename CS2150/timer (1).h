/*
 * Reid Bixler
 * rmb3yz
 * October 21, 2014
 * CS 2150 Post-Lab 6 timer.h
 */

#ifndef TIMER_H
#define TIMER_H

#include <iostream>
#include <string>
#include <time.h>
#include <sys/time.h>

using namespace std;

class timer {
private:
    timeval startVar, stopVar;
    bool running;

public:
    timer() : running(0) {}
    ~timer() {}
    timer(timer & myTimer);
    int start();
    int stop();
    string toString();
    ostream & print(ostream &theStream);
    double getTime();
};

ostream & operator<<(ostream & theStream, timer & theTimer);

#endif
