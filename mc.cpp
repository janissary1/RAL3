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
//prints cpu time
void printRun(std::chrono::duration<double> run_time) {
    std::cout << "Computation Time: " << run_time.count() << "s" << std::endl;
}
double prob1, prob2;

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
    double policy[4] = {0.25,0.25,0.25,0.25};
    char** board = build_board();
    std::vector<std::array<int,4>> episode = generateEpisode(policy,board);
    for(int i = 0; i < 10; i++) {
        for(int k = 0; k < 10; k++) {
            printf("%2.c", board[k][i]);
        }
        std::cout << "\n";
    }
    // ----------------- monte carlo learning ----------------- //
    auto end = std::chrono::system_clock::now(); // end time
    std::chrono::duration<double> elapsed_seconds = end-start;
    std::cout << "Total ";
    printRun(elapsed_seconds);
   
    return 0;
}
