#include "episode.h"

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
int main(int argc, char** args){
    double*** policy = initpolicy();
    std::array<std::array<char,10>,10> board = build_board();
    std::vector< std::array<int,4> > out = generateEpisode(policy,1.0,0.0);
    
    for(int i = 0 ; i < out.size(); i++){
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