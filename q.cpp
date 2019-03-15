/*
    Tony Misic 500759917
    Daniel Bellissimo 500749419
    CPS841 Assignment 3 Question 2 Q-Learning Implementation
*/
#include "q.h"


void qlearn(double*** policy, double*** q,double p1, double p2, double alpha, double gamma,double epsilon){
    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_int_distribution<int> dist(0, 9);
    
    int x1 = dist(mt);
    int y1 = dist(mt);
    int t = 0;
    if (x1 != 9 && y1 != 0){
            while (t < 200) {
                int x2,y2,a2;
                int a1 = epsilon_greedy(q[y1][x1],epsilon);

                int R = -1;
                std::array<int, 2> next_state = take_action(x1,y1,a1,p1,p2);

                x2 = next_state[0];
                y2 = next_state[1];
                
                a2 = maxIndex(policy[y2][x2],4);
                if (x2 == 9 && y2 == 0){
                    R=100;
                    q[y1][x1][a1] = q[y1][x1][a1] + alpha*(R + gamma*q[y2][x2][a2] - q[y1][x1][a1]);
                    break;
                    }
                else {
                    q[y1][x1][a1] = q[y1][x1][a1] + alpha*(R + gamma*q[y2][x2][a2] - q[y1][x1][a1]);
                }
                
                x1 = x2;
                y1 = y2;
                t++;
            }
        }
    else{
        return qlearn(policy,q,p1,p2,alpha,gamma,epsilon);
        }
    
}
