#include <stdlib.h>
#include <iostream>
#include <random>
#include <vector>
#include <array>
#include <time.h>

std::vector< std::array<int,4> > generateEpisode(double* policy,char** board);
int select_action(double* policy);
char** build_board();
bool left_of_wall(int x, int y);
bool right_of_wall(int x, int y);
bool above_wall(int x, int y);
bool below_wall(int x, int y);