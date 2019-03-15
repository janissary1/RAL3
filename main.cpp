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

void printRun(std::chrono::duration<double> run_time) {
    std::cout << "Computation Time: " << run_time.count() << "s" << std::endl;
}

int main(int argc, char** argv){
    double prob1, prob2;
    if ( argc > 1 ) {
        prob1 = atof(argv[1]);
        prob2 = atof(argv[2]);
    } else {
        std::cout << "Not enough arguments!" << std::endl;
        return 1;
    }

    //double p[4] = {0.9,0.1,0,0};
    double alpha[3] = {0.05,0.1,0.2};
    for(int tests = 0; tests < 3; tests++){
        //Sarsa Test with 10 000 Iterations
        std::printf("Running Sarsa ... with alpha = %lf\n10000 Episodes\np1= %lf\np2= %lf\n", alpha[tests],prob1,prob2);
        double*** policy = init3d(0.25);
        double*** q = init3d(0.0);
        auto start = std::chrono::system_clock::now(); // start time
        for(int i = 0; i < 10000; i++){
            //policy,q,p1,p2,alpha,gamma,epsilon
            sarsa(policy,q,prob1,prob2,alpha[tests],0.9,0.1);
        }
        policy = setPolicy(q);
        printPolicy(policy);
        auto end = std::chrono::system_clock::now(); // end time
        std::chrono::duration<double> elapsed_seconds = end-start;
        printRun(elapsed_seconds);

        //Q learn Test 10 000 Iterations
        std::printf("Running Qlearn ... with alpha = %lf\n10000 Episodes\np1= %lf\np2= %lf\n",alpha[tests],prob1,prob2);
        double*** policy2 = init3d(0.25);
        double*** q2 = init3d(0.0);
        start = std::chrono::system_clock::now();
        for(int i = 0; i < 10000; i++){
            //policy,q,p1,p2,alpha,gamma,epsilon
            qlearn(policy2,q2,prob1,prob2,alpha[tests],0.9,0.1);
        }
        policy2 = setPolicy(q2);
        printPolicy(policy2);
        end = std::chrono::system_clock::now(); // end time
        elapsed_seconds = end-start;
        printRun(elapsed_seconds);


    

    }
    
   
    return 0;
    
}