# Make file for Project 3 EECE2560 
main: main.cpp wordList.o grid.o
	g++ -std=c++11 wordList.o grid.o main.cpp -o main
wordList.o: wordList.cpp wordList.h
	g++ -std=c++11 -g -c wordList.cpp
grid.o: grid.cpp grid.h
	g++ -std=c++11 -g -c grid.cpp
clean:
	rm main wordList.o grid.o