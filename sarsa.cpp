/*
    Tony Misic 500759917
    Daniel Bellissimo 500749419
    CPS841 Assignment 3 Question 2 SARSA Implementation
*/
#include "sarsa.h"
#include "episode.h"


void sarsa(double*** policy, double*** q,double p1, double p2, double alpha, double gamma,double epsilon){
    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_int_distribution<int> dist(0, 9);
    
    int x1 = dist(mt);
    int y1 = dist(mt);
    int A = epsilon_greedy(policy[y1][x1],epsilon);
    int t = 0;
    if (x1 != 9 && y1 != 0){
            while (t < 200) {
                int x2,y2,a2;
                

                int a1 = A;
                int R = -1;
                std::array<int, 2> next_state = take_action(x1,y1,a1,p1,p2);
                a2 = epsilon_greedy(q[y1][x1],epsilon);//
    
                
                x2 = next_state[0];
                y2 = next_state[1];
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
                A = a2;

                t++;
            }
        }
    else{
        return sarsa(policy,q,p1,p2,alpha,gamma,epsilon);
        }
    
}

int epsilon_greedy(double* policy,double epsilon){
    
    
    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_real_distribution<double> dist(0.0, 1.0);
    double rando = dist(mt);
    if (rando <= epsilon){
        std::random_device rd2;
        std::mt19937 mt2(rd2());
        std::uniform_int_distribution<int> dist(0,3);
        int rando = dist(mt2);
        return rando;
        }
    else{return maxIndex(policy,4);}
}

int maxIndex(double* arr, int len){
    double max = *std::max_element(arr,arr+len);
    for(int i = 0; i < len; i++){
        if (arr[i] == max){
            return i;
        }

    }
}
