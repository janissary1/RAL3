g++ -c episode.cpp
g++ -c main.cpp 
g++ -c sarsa.cpp 
g++ -c q.cpp
g++ episode.o main.o sarsa.o q.o -o main 