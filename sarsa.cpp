/*
    Tony Misic 500759917
    Daniel Bellissimo 500749419
    CPS841 Assignment 3 Question 2 SARSA Implementation
*/
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
#include <array>
#include <random>

int select_action(double* policy){
    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_real_distribution<double> dist(0.0, 1.0);
    double rando = dist(mt);
    double upper_bound = 0.0;
    double lower_bound = 0.0;
    for (int i = 0; i < 4; i++){
        upper_bound += policy[i];
        if (lower_bound < rando && rando <= upper_bound){
            return i;
        }
        lower_bound += policy[i];
    }
}
std::array< std::array<std::array<double, 4>, 10>, 10> initq(){
    std::array< std::array<std::array<double, 4>, 10>, 10> Q;
    return Q;
}

std::array< std::array<std::array<double, 4>, 10>, 10> sarsa(std::array< std::array<std::array<double, 4>, 10>, 10> policy,std::array< std::array<std::array<double, 4>, 10>, 10> q,float p1, float p2,char** board, double alpha, double gamma,double epsilon){
    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_int_distribution<int> dist(0, 9);
    
    int x = dist(mt);
    int y = dist(mt);
    int A = epsilon_greedy(policy[y][x],epsilon);
    board[y][x] = 8;
    
    if (x != 9 && y != 0){
        //printf("[%d,%d]:%d\n",x,y,A);

        while (true) {
            double transitionP[4] = {0,0,0,0};
            int next_state;
            int x1 = x;
            int y1 = y;
            int a1 = A;
            int R = -1;
            int x2,y2,a2;

            if (x == 9 && y == 0){R=100;}
            x2 = x;
            y2 = y;
            a2 = epsilon_greedy(q[y1][x1],epsilon);
            q[y1][x1][a1] = q[y1][x1][a1] + alpha*(R + gamma*q[y2][x2][a2] - q[y1][x1][a1]);
            if (x == 9 && y == 0){break;}

            
            //std::printf("[%d,%d]:%d\n",x,y,A);
            /*
            char c ;
            if (A == 0){c = '^';}
            else if (A == 1){c = '>';}
            else if (A == 2){c = 'v';}
            else if (A==3){c = '<';}
            board[y][x] = c;*/
            }
        }
    else{
        return sarsa(policy,q,p1,p2,board,alpha,gamma,epsilon);
    }
}

int epsilon_greedy(std::array<double, 4> policy,float epsilon){
    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_real_distribution<double> dist(0.0, 1.0);
    double rando = dist(mt);
    if (rando <= 0.3){
        std::random_device rd2;
        std::mt19937 mt2(rd2());
        std::uniform_int_distribution<int> dist(0,3);
        int rando = dist(mt2);
        return rando;
        }
    else{return std::distance(policy,std::max_element(policy.begin(),policy.end()));}
}
/*
int maxIndex(std::array<double, 4> arr){

}
*/
