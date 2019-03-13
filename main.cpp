#include "episode.h"

int main(int argc, char** args){
    double policy[4] = {0.25,0.25,0.25,0.25};
    std::array<std::array<char,10>,10> board = build_board();
    std::vector< std::array<int,4> > out = generateEpisode(policy,1.0,0.0);
    for(int i = 0 ; i < 20; i++){
        std::printf("%d,%d:%d,%d\n",out[i][0],out[i][1],out[i][2],out[i][3]);
    }
    /*
    for(int i = 0; i < 10; i++){
        for(int k = 0; k < 10; k++){
            std::cout << board[k][i];
        }
        std::cout << "\n";
    }*/
   
    return 0;
    
}