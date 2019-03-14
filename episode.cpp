#include "episode.h"

//A = {up,right,down,left}
std::vector< std::array<int,4> > generateEpisode(double*** policy,double p1, double p2){
    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_int_distribution<int> dist(0, 9);
    
    int x = dist(mt);
    int y = dist(mt);
    int A = select_action(policy[y][x]);
    
    if (x != 9 && y != 0){
        std::vector< std::array<int,4> > episode;
        std::array<int, 4> first = {x,y,A,-1};
    
        episode.push_back(first);
        while (true) {
            std::array<int, 2>  next_state = take_action(x,y,A,p1,p2);
            std::array<int, 4> next = {x,y,A,-1};
            if (x == 9 && y == 0){next[3] = 100;episode.push_back(next);break;}
            episode.push_back(next);
            A = select_action(policy[y][x]);
            x = next_state[0];
            y = next_state[1];
           
        }
        return episode;
    }
    else{
        return generateEpisode(policy,p1,p2);
    }
}
//A = {up,right,down,left}
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

std::array<std::array<char,10>,10> build_board(){
    std::array<std::array<char,10>,10> board ;
    for (int i = 0; i < 10; i++){
        for(int k = 0 ; k < 10; k++){
            board[k][i] = ' ';
        }
    }
    return board;
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
    if (y == 4 && x != 2 && x != 7){return true;}
    return false;
}
bool below_wall(int x, int y){
    if (y == 0){return true;}
    if (y == 5 && x != 2 && x != 7){return true;}
    return false;
}


std::array<int, 2> take_action(int x, int y, int action,double p1,double p2){
   // std::cout << x << " " << y << " " << action << "\n" ;
    int next_state;
    std::array<int, 2>  out;
    double transitionP[4] = {0,0,0,0};
    if (action == 0){ //up
        if (below_wall(x,y)){
            transitionP[0] = (1.0-p1-p2)/2.0; //left adj
            transitionP[1] = (p1+p2); //same
            transitionP[2] = (1.0-p1-p2)/2; //bottom adj
            next_state = select_action(transitionP); //using select action function to select transition using transition probabilities
            if (below_wall(x,y) && right_of_wall(x,y)){ //right corner below wall
                if (next_state == 0){x -= 1;}
                else if (next_state == 2){y += 1;}}
                //else do nothing ...
            else if (below_wall(x,y) && left_of_wall(x,y)){ //left corner below wall
                if (next_state == 0){x -= 1;}
                else if (next_state == 2){y += 1;}}
            
            else if (below_wall(x,y)){//just below wall
                if (next_state == 0){x-=1;}
                else if (next_state == 2){x+=1;}}
        }
        else if (left_of_wall(x,y)){//just left of wall
            transitionP[0] = p1; //desired state //left adj
            transitionP[1] = p2; //same
            transitionP[2] = (1.0-p1-p2)/2.0; //left up adj
            next_state = select_action(transitionP);
            if (next_state == 0){y-=1;}
            //else if(next_state == 1){do nothing}
            else if(next_state == 2){y-=1;x-=1;}
            
        }
        else if (right_of_wall(x,y)){//just right of wall
            transitionP[0] = p1; //desired state //left adj
            transitionP[1] = p2; //same
            transitionP[2] = (1.0-p1-p2)/2.0; //left up adj
            next_state = select_action(transitionP);
            if (next_state == 0){y-=1;}
            //else if(next_state == 1){do nothing}
            else if(next_state == 2){y-=1;x+=1;}
        } 
        else{
            transitionP[0] = p1; //desired state
            transitionP[1] = p2; //same
            transitionP[2] = (1.0-p1-p2)/2.0; //left adj
            transitionP[3] = (1.0-p1-p2)/2.0; //right adj
            next_state = select_action(transitionP);
            if (next_state == 0){y-=1;}
            //else if (next_state == 1){do nothing}
            else if (next_state == 2){y-=1;x-=1;}
            else if (next_state == 3){y-=1;x+=1;}
        }
    }
    if (action == 1){ //right
        if (left_of_wall(x,y)){
            transitionP[0] = (1.0-p1-p2)/2.0; //up adj
            transitionP[1] = (p1+p2); //same
            transitionP[2] = (1.0-p1-p2)/2.0; //down adj
            next_state = select_action(transitionP);
            if (above_wall(x,y)){ 
                if(next_state == 0){y -= 1;}
                else if (next_state == 2){ x -= 1;}
            }
            else if (below_wall(x,y)){
                if (next_state == 0){y -= 1;}
                else if (next_state == 2){x -= 1;}}
                //else do nothing ...
            
            else {
                if(next_state == 0){y-= 1;}
                else if(next_state == 2){y+=1;}
            }
        }
        else if (above_wall(x,y)){
            transitionP[0] = p1; //desired state //left adj
            transitionP[1] = p2; //same
            transitionP[2] = (1.0-p1-p2)/2.0; //left up adj
            next_state = select_action(transitionP);
            if (next_state == 0){x+=1;}
            //else if(next_state == 1){do nothing}
            else if(next_state == 2){y-=1;x+=1;}
        }
        else if (below_wall(x,y)){
            transitionP[0] = p1; //desired state //left adj
            transitionP[1] = p2; //same
            transitionP[2] = (1.0-p1-p2)/2.0; //left up adj
            next_state = select_action(transitionP);
            if (next_state == 0){x+=1;}
            //else if(next_state == 1){do nothing}
            else if(next_state == 2){y+=1;x+=1;}
        }
        else{
            //std::cout << x <<"," << y << "action= " << A <<"right" << "\n";
            transitionP[0] = p1; //desired state
            transitionP[1] = p2; //same
            transitionP[2] = (1.0-p1-p2)/2.0; //top adj
            transitionP[3] = (1.0-p1-p2)/2.0; //bottom adj
            next_state = select_action(transitionP);
            if (next_state == 0){x+=1;}
            //else if (next_state == 1){do nothing}
            else if (next_state == 2){y-=1;x+=1;}
            else if (next_state == 3){y+=1;x+=1;}
        }
    }
    if (action == 2){ //down
        if (above_wall(x,y)){
                transitionP[0] = (1.0-p1-p2)/2.0; //left adj
                transitionP[1] = (p1+p2); //same
                transitionP[2] = (1.0-p1-p2)/2.0; //top adj
                next_state = select_action(transitionP); //using select action function to select transition using transition probabilities
                if (above_wall(x,y) && right_of_wall(x,y)){ //right corner above wall
                    if (next_state == 0){x -= 1;}
                    else if (next_state == 2){y -= 1;}}
                    //else do nothing ...
                else if (above_wall(x,y) && left_of_wall(x,y)){ //left corner above wall
                    if (next_state == 0){x -= 1;}
                    else if (next_state == 2){y -= 1;}}
                
                else if (above_wall(x,y)){//just above wall
                    if (next_state == 0){x-=1;}
                    else if (next_state == 2){x+=1;}}
            }
        else if (left_of_wall(x,y)){//just left of wall
            transitionP[0] = p1; //desired state //left adj
            transitionP[1] = p2; //same
            transitionP[2] = (1.0-p1-p2)/2.0; //left up adj
            next_state = select_action(transitionP);
            if (next_state == 0){y+=1;}
            //else if(next_state == 1){do nothing}
            else if(next_state == 2){y+=1;x-=1;}
            
        }
        else if (right_of_wall(x,y)){//just left of wall
            transitionP[0] = p1; //desired state //left adj
            transitionP[1] = p2; //same
            transitionP[2] = (1.0-p1-p2)/2.0; //left up adj
            next_state = select_action(transitionP);
            if (next_state == 0){y+=1;}
            //else if(next_state == 1){do nothing}
            else if(next_state == 2){y+=1;x+=1;}
        } 
        else{
            transitionP[0] = p1; //desired state
            transitionP[1] = p2; //same
            transitionP[2] = (1.0-p1-p2)/2.0; //left adj
            transitionP[3] = (1.0-p1-p2)/2.0; //right adj
            next_state = select_action(transitionP);
            if (next_state == 0){y+=1;}
            //else if (next_state == 1){do nothing}
            else if (next_state == 2){y+=1;x-=1;}
            else if (next_state == 3){y+=1;x+=1;}
        }
    }
    if (action == 3){//left
        if (right_of_wall(x,y)){
                transitionP[0] = (1.0-p1-p2)/2.0; //up adj
                transitionP[1] = (p1+p2); //same
                transitionP[2] = (1.0-p1-p2)/2.0; //down adj
                next_state = select_action(transitionP);
                if (above_wall(x,y)){ 
                    if(next_state == 0){y -= 1;}
                    else if (next_state == 2){ x += 1;}
                }
                else if (below_wall(x,y)){
                    if (next_state == 0){y -= 1;}
                    else if (next_state == 2){x += 1;}}
                    //else do nothing ...
                
                else {
                    if(next_state == 0){y-= 1;}
                    else if(next_state == 2){y+=1;}
                }
            }
            else if (above_wall(x,y)){
                transitionP[0] = p1; //desired state 
                transitionP[1] = p2; //same
                transitionP[2] = (1.0-p1-p2)/2.0; //left up adj
                next_state = select_action(transitionP);
                if (next_state == 0){x-=1;}
                //else if(next_state == 1){do nothing}
                else if(next_state == 2){y-=1;x-=1;}
            }
            else if (below_wall(x,y)){
                transitionP[0] = p1; //desired state //left adj
                transitionP[1] = p2; //same
                transitionP[2] = (1.0-p1-p2)/2.0; //left up adj
                next_state = select_action(transitionP);
                if (next_state == 0){x-=1;}
                //else if(next_state == 1){do nothing}
                else if(next_state == 2){y+=1;x-=1;}
            }
            else{
                transitionP[0] = p1; //desired state
                transitionP[1] = p2; //same
                transitionP[2] = (1.0-p1-p2)/2.0; //top adj
                transitionP[3] = (1.0-p1-p2)/2.0; //bottom adj
                next_state = select_action(transitionP);
                if (next_state == 0){x-=1;}
                //else if (next_state == 1){do nothing}
                else if (next_state == 2){y-=1;x-=1;}
                else if (next_state == 3){y+=1;x-=1;}
            }
    }
    out[0] = x;
    out[1] = y;
    return out;
}
