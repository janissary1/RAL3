#include <stdlib.h>
#include <iostream>
#include <random>
#include <vector>
#include <array>
#include <time.h>

std::vector< std::array<int,4> > generateEpisode(double* policy,long p1, long p2);
int select_action(double* policy);
std::array<std::array<char,10>,10> build_board();
bool left_of_wall(int x, int y);
bool right_of_wall(int x, int y);
bool above_wall(int x, int y);
bool below_wall(int x, int y);
std::array<int, 2> take_action(int x, int y, int action,long p1, long p2);