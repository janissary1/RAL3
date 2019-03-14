#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <iostream>
#include <fstream>
#include <chrono>
#include <algorithm>
#include <numeric>
#include <random>
#include <iterator>

void sarsa(double*** policy, double*** q,double p1, double p2, double alpha, double gamma,double epsilon);
int select_action(double* policy);
int epsilon_greedy(double* policy,double epsilon);
int maxIndex(double* arr, int len);