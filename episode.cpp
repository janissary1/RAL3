#include <stdlib.h>
#include <iostream>
#include <random>
#include <vector>
#include <array>
//A = {up,right,down,left}
std::vector< std::array<int,4> > generateEpisode(double* policy){
    std::default_random_engine generator;
    std::uniform_int_distribution<int> initial_state(0,9);

    int x = initial_state(generator);
    int y = initial_state(generator);
    int A = select_action(policy);
    
    if (x != 9 && y != 9){
        std::vector< std::array<int,4> > episode;
        std::array<int, 4> first = {x,y,A,-1};
        episode.push_back(first);
        while (x != 9 && y != 9){
            A = select_action(policy);
            switch(A){
                case 0: //up
                    if (x ==)

                case 1: //right
                case 2: //down
                case 3: //left
            }
            std::array<int, 4> next = {x,y,A,-1};
        }
        
        return episode;

    }
    else{
        return generateEpisode(policy);
    }
}
int select_action(double* policy){
    std::default_random_engine generator;
    std::uniform_int_distribution<int> random_action(0,4);
    int rando = random_action(generator);
    long upper_bound,lower_bound = 0;
    for (int i = 0; i < 4; i++){
        upper_bound += policy[i];
        if (lower_bound < rando && rando <= upper_bound){
            return i;
        }
        lower_bound += policy[i];
    }
}
//wall logic
bool left_of_wall(int x, int y){
    if (x == 9){return true;}
    if (x == 4 && y != 2 && y != 7){return true;}
    return false;
}
bool right_of_wall(int x, int y){
    if (x == 0){return true;}
    if (x == 5 && y != 2 && y != 7){return true;}
    return false;
}
bool above_wall(int x, int y){
    if (y == 9){return true;}
    if (y == 4 && x != 2 && y != 7){return true;}
    return false;
}
bool below_wall(int x, int y){
    if (y == 0){return true;}
    if (y == 5 && x != 2 && y != 7){return true;}
    return false;
}

int main(int argc, char** args){
    std::cout << "kek\n";
    double policy[4] = {0.25,0.25,0.25,0.25};
    generateEpisode(policy);
    return 0;
}