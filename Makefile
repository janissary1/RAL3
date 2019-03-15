CC=g++
CFLAGS =--std=c++11
DEPS =
CLASS =episode.cpp
CLASS2 =mc.cpp
OBJ =episode.o
OBJ2 =mc.o
PARAMS=1.0 0.0
OBJECT=mc

all: 
	$(CC) -c $(CLASS) $(CFLAGS)
	$(CC) -c $(CLASS2) $(CFLAGS)
	$(CC) $(OBJ) $(OBJ2) -o $(OBJECT) $(CFLAGS)
run:
	$(CC) -c $(CLASS) $(CFLAGS)
	$(CC) -c $(CLASS2) $(CFLAGS)
	$(CC) $(OBJ) $(OBJ2) -o $(OBJECT) $(CFLAGS)
	./$(OBJECT) $(PARAMS)