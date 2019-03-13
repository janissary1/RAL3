/*
    Tony Misic 500759917
    Daniel Bellissimo 500749419
    CPS841 Assignment 3 Question 2 Monte-Carlo Implementation
*/
#include <episode.cpp>
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
int main(int argc, char** args){
    double policy[4] = {0.25,0.25,0.25,0.25};
    char** board = build_board();
    generateEpisode(policy,board);
    
    for(int i = 0; i < 10; i++){
        for(int k = 0; k < 10; k++){
            std::cout << board[k][i];
        }
        std::cout << "\n";
    }
   
    return 0;
}