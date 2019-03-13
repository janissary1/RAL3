CC=g++
CFLAGS =--std=c++11
DEPS =
CLASS =mc.cpp 
OBJ =mc
PARAMS=1.0 0.0

all: 
	$(CC) -o $(OBJ) $(CLASS) $(CFLAGS)
run:
	$(CC) -o $(OBJ) $(CLASS) $(CFLAGS)
	./$(OBJ) $(PARAMS)