CC=g++
CFLAGS =--std=c++11
DEPS =
CLASS =mc.cpp 
OBJ =mc

all: 
	$(CC) -o $(OBJ) $(CLASS) $(CFLAGS)
run:
	$(CC) -o $(OBJ) $(CLASS) $(CFLAGS)
	./$(OBJ)