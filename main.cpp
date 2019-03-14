#include "q.h"
double*** init3d(double val){
    double*** policy;
      
    policy = new double**[10];
    for(int x = 0; x < 10; ++x) {
        policy[x] = new double*[10];
        for(int y = 0; y < 10; ++y) {
            policy[x][y] = new double[4];
            for(int z = 0; z < 4; ++z) { // initialize the values to whatever you want the default to be
                policy[x][y][z] = val;
            }
        }
    }
    return policy;

}
void print(double*** policy){
    for(int i = 0; i < 10; i++){
        for(int k = 0; k < 10; k++){
            std::printf("State [%d,%d]: ",i,k);
            for(int j = 0; j < 4; j++){
                std::cout << policy[k][i][j] << " ";
            }
            std::cout << "\n";
            
        }
    }
}
void printPolicy(double*** policy){
    for(int i = 0; i < 10; i++){
        for(int k = 0; k < 10; k++){
            int j = maxIndex(policy[i][k],4);
            if( j == 0){
                std::cout << "^" << " ";
            }
            else if( j== 1){
                std::cout << ">" << " ";

            }
            else if (j == 2){
                std::cout << "v" << " ";

            }
            else if (j == 3){
                std::cout << "<" << " ";
            }
        }
        std::cout << "\n";
    }
}
double*** setPolicy(double*** q){
    double*** new_p = init3d(0.0);
    for(int i = 0; i < 10; i++){
        for(int k = 0; k < 10; k++){
            int max = maxIndex(q[k][i],4);
            new_p[k][i][max] = 1.0;
        }
    }
    return new_p;
}

int main(int argc, char** args){
    //double p[4] = {0.9,0.1,0,0};
    
    //Sarsa Test with 10 000 Iterations
    
    std::printf("Running Sarsa ...\n");
    double*** policy = init3d(0.25);
    double*** q = init3d(0.0);
    for(int i = 0; i < 10000; i++){
        //policy,q,p1,p2,alpha,gamma,epsilon
        sarsa(policy,q,1.0,0.0,0.1,0.9,0.1);
    }
    policy = setPolicy(q);
    printPolicy(policy);
    
    //Q learn Test 
    std::printf("Running Qlearn ...\n");
    double*** policy2 = init3d(0.25);
    double*** q2 = init3d(0.0);
    for(int i = 0; i < 10000; i++){
        //policy,q,p1,p2,alpha,gamma,epsilon
        qlearn(policy2,q2,1.0,0.0,0.1,0.9,0.1);
    }
    policy2 = setPolicy(q2);
    printPolicy(policy2);
   
   
    return 0;
    
}