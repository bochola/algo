#ifndef TEST_CPP
#define TEST_CPP

#include "Maze.h"
// Includes in Maze Header:
//#include <iostream>
//#include <string>
//#include <vector>

// Namespace for testing functions
namespace Test {
    /**
     * Reads a graph from a file and echos it back in console.
     * 
     * @param void
     * @return void
     */
    inline void readGraphFromFileAndEcho() {
        std::vector<std::string> graphFiles{"Files/graph1.txt"};

        for (std::string fn : graphFiles) {
            std::ifstream infile(fn);
            auto g = readGraph(infile);
            std::cout << g << std::endl;
            std::cout << "Done with " << fn << std::endl;
        }
    }

    /**
     * Dijkstra Test Function.
     * 
     * @param void
     * @return void
     */ 
    inline void dijkstraTest() {
        std::vector<std::string> graphFiles{
            "Files/graph1.txt",
            "Files/graph2.txt"
        };

        for (std::string fn : graphFiles) {
            std::ifstream infile(fn);
            auto g = readGraph(infile);
            dijkstra(g, *(boost::vertices(g).first));
            std::cout << g << std::endl;
            std::cout << "Done with applying Dijkstra to " << fn << std::endl;
        }
    }

    /**
     * Bellman Ford Test Function.
     * 
     * @param void
     * @return void
     */ 
    inline void bellmanFordTest() {
        std::vector<std::string> graphFiles{"Files/graph1.txt"};

        for (std::string fn : graphFiles) {
            std::ifstream infile(fn);
            auto g = readGraph(infile);
            bellmanFord(g, *(boost::vertices(g).first));
            std::cout << g << std::endl;
            std::cout << "Done with applying Bellman-Ford to " << fn << std::endl;
        }
    }
    
    /**
     * Reads a maze from a file and echos it back in console.
     * Also attempts to parse the maze to the graph and echoes
     * back the maze to the console.
     * 
     * @param void
     * @return void
     */
    inline void readMazeFromFileAndEcho() {
        std::vector<std::string> mazeFiles{"Files/maze1.txt"};

        for (std::string fn : mazeFiles) {
            ifstream *fin = new ifstream();
            fin->open(fn);
            Maze m(fin);
            m.print(m.numRows()-1,m.numCols()-1,0,0);
            Graph g;
            m.mapMazeToGraph(g);
            cout << g << endl;
            cout << "Done with " << fn << endl;
        }
    }
} // namespace Test

#endif // TEST_CPP

int main() {
    Test::readGraphFromFileAndEcho();
    Test::dijkstraTest();
    Test::bellmanFordTest();
    Test::readMazeFromFileAndEcho();
}