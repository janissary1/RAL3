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
double average(std::array<double, 4> actions);
bool last_in_episode(int state_x, int state_y, std::vector< std::array<int,4> > episode);
int argmax(std::array<double, 4> a);
double reward(int state_x, int state_y, int action);
double*** initpolicy();
//prints cpu time
void printRun(std::chrono::duration<double> run_time) {
    std::cout << "Computation Time: " << run_time.count() << "s" << std::endl;
}
double prob1, prob2;
double epsilon = 0.1;
double G = 0.0;
double gamma_mine = 0.9;
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
    //init a arbitrary policy with e-soft policy TODO
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            int best = rand() % 4;
            for (int a = 0; a < 4; a++) {
                if (best == a) {
                    policy[i][j][a] = (1 - epsilon + (epsilon / 4));
                } else {
                    policy[i][j][a] = (epsilon / 4);
                }
            }
        }
    }
    //init Q
    std::array<std::array<std::array<double, 4>, 10>, 10> Q = {};
    //init returns
    std::array<std::array<std::vector<double>, 10>, 10> returns = {};
    //episodic learning
    for (int count = 0; count < 10; count++) {
        std::vector< std::array<int,4> > episode = generateEpisode(policy,prob1,prob2);
        G = 0.0;
        for (int t = episode.size() - 1; t >= 0; t--) {
            G = gamma_mine * G + episode[t + 1][3];
            if (last_in_episode(episode[t][0], episode[t][1], episode)) {
                returns[episode[t][0]][episode[t][0]].push_back(G);
                Q[episode[t][0]][episode[t][0]][episode[t][2]] = average(returns[episode[t][0]][episode[t][1]]);
                int best_action = argmax(Q[episode[t][0]][episode[t][0]]);
                for (int a = 0; a < 4; a++) {
                    if (best_action == a) {
                        policy[episode[t][0]][episode[t][1]][a] = (1 - epsilon + (epsilon / 4));
                    } else {
                        policy[episode[t][0]][episode[t][1]][a] = (epsilon / 4);
                    }
                }
            }
        }
    }
    // ----------------- monte carlo learning ----------------- //
    auto end = std::chrono::system_clock::now(); // end time
    std::chrono::duration<double> elapsed_seconds = end-start;
    std::cout << "Total ";
    printRun(elapsed_seconds);

    std::cout << "Optimal Policy: " << std::endl;
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            for (int k = 0; k < 4; k ++) {
                std::cout << Q[i][j][k] << " ";
            }
            std::cout << std::endl;
        }
    }
    return 0;
}

double average(std::vector<double> actions) {
    double sum = 0;
    for (int i = 0; i < actions.size(); i++)
    {
        sum += actions[i];
    }
    return sum / actions.size();
}
bool last_in_episode(int state_x, int state_y, std::vector< std::array<int,4> > episode) {
    int last_index = 0;
    for (int i = 0; i < episode.size(); i++) {
        if (state_x == episode[i][0]) {
            if (state_y == episode[i][1]) {
                last_index = i;
            }
        }
    }
    if (state_x == episode[last_index][0]) {
        if (state_y == episode[last_index][1]) {
            return true;
        }
    }
    return false;
}

int argmax(std::array<double, 4> a) {
    int max = a[0];
    int index = 0;
    for (int i = 1; i < a.size(); i++) {
        if (max < a[i]) {
            max = a[i];
            index = i;
        }
    }
    return index;
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