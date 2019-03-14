/*
    Tony Misic 500759917
    Daniel Bellissimo 500749419
    CPS841 Assignment 3 Question 2 Monte-Carlo Implementation
*/
#include "episode.h"
#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <iostream>
#include <fstream>
#include <chrono>
#include <algorithm>
#include <numeric>

double*** initpolicy();
//prints cpu time
void printRun(std::chrono::duration<double> run_time) {
    std::cout << "Computation Time: " << run_time.count() << "s" << std::endl;
}
double prob1, prob2;
double epsilon = 0.1;
const int UP = 0, RIGHT = 1, DOWN = 2, LEFT = 3;

int main(int argc, char** argv) {
    srand(time(NULL));
    if ( argc > 1 ) {
        prob1 = atof(argv[1]);
        prob2 = atof(argv[2]);
    } else {
        std::cout << "Not enough arguments!" << std::endl;
    }
    auto start = std::chrono::system_clock::now(); // start time
    // ----------------- monte carlo learning ----------------- //
    //init policy
    double*** policy = initpolicy();
    //init a arbitrary policy with e-soft policy
    
    //int Q
    std::array<std::array<std::array<double, 4>, 10>, 10> Q = {};
    //init returns
    std::array<std::array<std::array<double, 4>, 10>, 10> returns = {};
    //generate episode
    std::vector< std::array<int,4> > episode = generateEpisode(policy,prob1,prob2);
    


    // ----------------- monte carlo learning ----------------- //
    auto end = std::chrono::system_clock::now(); // end time
    std::chrono::duration<double> elapsed_seconds = end-start;
    std::cout << "Total ";
    printRun(elapsed_seconds);
   
    return 0;
}

double*** initpolicy(){
    double*** policy;
      
    policy = new double**[10];
    for(int x = 0; x < 10; ++x) {
        policy[x] = new double*[10];
        for(int y = 0; y < 10; ++y) {
            policy[x][y] = new double[4];
            for(int z = 0; z < 4; ++z) { // initialize the values to whatever you want the default to be
                policy[x][y][z] = 0.25;
            }
        }
    }
    return policy;

}