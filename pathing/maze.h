// IMPORTS
#include <iostream>
#include <fstream>  
#include <exception>
#include <string>
#include <cmath> // too lazy to define absolute value
// STL Libraries
#include <algorithm>
#include <iterator> 
#include <limits.h>
#include <vector>
#include <list>
#include <stack>
#include <queue>
#include <utility>
// BGL Libraries
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/graph_selectors.hpp>
#include <boost/graph/graph_traits.hpp>
// Heap Header
#include "heapV.h"

// Using boost and std library
using namespace boost;
using namespace std;

// Define header file
#ifndef MAZE_H
#define MAZE_H

// Initial weight for vertices and edges
#define INITIAL_WEIGHT 1

// Graph objects
struct VertexProperties;
struct EdgeProperties;

//typedef adjacency_list<vecS, vecS, bidirectionalS, VertexProperties, EdgeProperties> Graph;
typedef adjacency_list<vecS, vecS, bidirectionalS, VertexProperties, EdgeProperties> Graph;


struct VertexProperties {
    pair<int,int> cell; // maze cell (x,y) value
    Graph::vertex_descriptor pred; // predecessor node
    int weight;
    int visited;
    bool marked;
};

// Create a struct to hold properties for each edge
struct EdgeProperties {
    int weight;
};

// Maze class
class Maze {
    private:
        // Stores the maze.
        std::vector<std::vector<bool> > maze;
            
        // Stores the start and end points as indices
        std::pair<int, int> startPoint;
        std::pair<int, int> endPoint;

        // Stores the start and end points as vector descriptors
        Graph::vertex_descriptor startPoint_v;
        Graph::vertex_descriptor endPoint_v;
        
        // Store Graph
        Graph graph;

        // Store input filestream
        ifstream *file;

        // Store number of rows
        int rows;

        // Store number of cols
        int cols;

        /**
         * Checks if an index acessing a maze row is in range.
         * 
         * @param index the index
         * @return true if the index is in range, false if not
         */ 
        bool rowIndexInRange(int index);

        /**
         * Checks if an index acessing a maze col is in range.
         * 
         * @param index the index
         * @return true if the index is in range, false if not
         */ 
        bool colIndexInRange(int index);

        /**
         * Checks if indices acessing a maze row and col is in range.
         * 
         * @param row the row index
         * @param col the col index
         * @return true if both indices are in range, false if not
         */ 
        bool pointIndexInRange(int row, int col);

        /**
         * Adds a vertex to a graph given an existing vertex counter,
         * and a pair<int,int> value to input into the vertex properties.
         * Increments the vertex counter.
         *
         * @param g the Graph object
         * @param vertex the vertex counter
         * @param x the first value in the pair<int,int> object in the vertex properties
         * @param y the second value in the pair<int,int> object in the vertex properties
         * @return The vertex descriptor of the new vertex.
         */
        Graph::vertex_descriptor& addVertex(Graph& g, int& vertex, int x, int y);

    public:
        /**
         * Default constructor for Maze.
         * 
         * @param void
         */ 
        Maze();

        /**
         * Constructs a maze given an input filestream.
         * 
         * @param in the input filestream
         */ 
        Maze(ifstream *in);

        /** 
         * Creates a graph object that represents the legal moves in the maze m.
         * Modifies an existing graph object.
         * 
         * @param g the graph object to modify
         * @return void
         */ 
        void mapMazeToGraph(Graph &g);

        /** Returns the start and end points of the maze as a std::pair.
         * @return A std::pair containing the start and end (in that order)
         */
        std::pair<Graph::vertex_descriptor, Graph::vertex_descriptor> getGraphPoints();

        /**
         * Prints the path represented by the vertices in a stack, repeatedly
         * calls print() to show each step of the path.
         * 
         * @param end [desc]
         * @param s the stack
         * @param g the Graph
         * @return void
         */ 
        void printPath(Graph::vertex_descriptor end, stack<Graph::vertex_descriptor> &s, Graph g);

        /** Returns a string representing this maze object.
         * @return A string representing this maze
         */
        std::string toString();

        /**
         * Mark all nodes in a graph as not visited.
         * 
         * @param g the graph
         * @return void
         */ 
        static void clearVisited(Graph &g);

        /**
         * Sets all the node weights in a graph to a specified weight.
         * 
         * @param g the graph
         * @param w the weight
         * @return void
         */ 
        static void setNodeWeights(Graph &g, int w);

        /**
         * Unmark all nodes in a graph.
         * 
         * @param g the graph
         * @return void
         */ 
        static void clearMarked(Graph &g);

        /**
         * Output operator for a Graph object. Prints out all nodes and their 
         * properties, and all edges and their properties.
         * 
         * @param ostr the output stream object to append to
         * @param g the Graph object
         */ 
        friend ostream &operator<<(ostream &ostr, const Graph &g);

        /**
         * Print out a specified area of the maze.
         * 
         * @param x1 the goal x position in the maze
         * @param y1 the goal y position in the maze
         * @param x0 the current x position in the maze
         * @param y0 the current y position in the maze
         */
        void print(int x1, int y1, int x0, int y0); 

        /**
         * Print out the maze.
         * 
         * @param void
         * @return void
         */ 
        void print();

        /**
         * Acesses the number of rows in the maze.
         * 
         * @param void
         * @return the number of rows in the maze
         */
        int numRows();

        /**
         * Acesses the number of cols in the maze.
         * 
         * @param void
         * @return the number of cols in the maze
         */
        int numCols(); 
};

ostream &operator<<(ostream &ostr, const Graph &g);

/**
 * Reads a graph in from a file.
 * @param infile The source file containing the graph.
 * @return By out-parameter, a graph object.
 * @return By out-parameter, the start and goal points of the graph.
 * @throw If the graph file could not be parsed as expected.
 */
void readGraph(std::ifstream& infile, Graph& g, Graph::vertex_descriptor& start, Graph::vertex_descriptor& end);

/**
 * Depth First Search (recursive) subroutine.
 * Performs the recursion in the depth first search, and attempts to find the path.
 *
 * @param g the Grpah object
 * @param curr the current vertex
 * @param end the end vertex to find
 * @return void
 */
void DFSRecursiveHelper(Graph& g, Graph::vertex_descriptor& curr, Graph::vertex_descriptor& end);

/**
 * Looks for a path from the start cell to the goal cell using depth-first search.
 * 
 * @param g the Graph
 * @param start the start vertex descriptor
 * @param end the end vertex descriptor
 * @return void
 */
void findPathDFSRecursive(Graph &g, Graph::vertex_descriptor &start, Graph::vertex_descriptor &end);

/**
 * Looks for a path from the start cell to the goal cell using depth-first search, but using a stack and not recursion.
 * 
 * @param g the Graph
 * @param s the stack
 * @param start the start vertex descriptor
 * @param end the end vertex descriptor
 * @return void
 */
void findPathDFSStack(Graph &g, stack<Graph::vertex_descriptor> &s, Graph::vertex_descriptor &start, Graph::vertex_descriptor &end);

/**
 * Finds a shortest path from the start cell to the goal cell using depth-first search.
 * 
 * @param g the Graph
 * @param start the start vertex descriptor
 * @param end the end vertex descriptor
 * @return void
 */
void findShortestPathDFS(Graph &g, Graph::vertex_descriptor &start, Graph::vertex_descriptor &end);

/**
 * Finds a shortest path from the start cell to the goal cell using breadth-first search.
 * 
 * @param g the Graph
 * @param start the start vertex descriptor
 * @param end the end vertex descriptor
 * @return void
 */
void findShortestPathBFS(Graph &g, Graph::vertex_descriptor &start, Graph::vertex_descriptor &end);

/**
 * A wavefront algorithm to find single pair paths in a given map.
 * 
 * @param g the Graph
 * @param start The starting point of the search.
 * @param end The ending point of the search.
 * @return A stack containing the path followed, start on top.
 */ 
stack<Graph::vertex_descriptor> wavefront(Graph &g, Graph::vertex_descriptor &start, Graph::vertex_descriptor &end);

/**
 * An A* algoirthm to find the best path to a goal in a given map.
 * 
 * @param g the Graph
 * @param start The starting point of the search.
 * @param end The ending point of the search.
 * @return A stack containing the path followed, start on top.
 */ 
stack<Graph::vertex_descriptor> aStar(Graph &g, Graph::vertex_descriptor &start, Graph::vertex_descriptor &end);

/**
 * Relaxes the edge between start and end, if possible.
 * 
 * @param g the Graph
 * @param start The source of the edge.
 * @param end The target of the edge.
 * @return true If the edge was successfully relaxed, false otherwise.
 */
bool relax(Graph &g, Graph::vertex_descriptor &start, Graph::vertex_descriptor &end);

/**
 * Relaxes the edge, if possible.
 *
 * @param g the Graph
 * @param e The edge to be relaxed upon.
 * @return true If the edge was successfully relaxed,
 *         false if the edge does not result in a lower weight
 */
bool relax(Graph& g, Graph::edge_descriptor& e);

/**
 * Finds single-source shortest paths using Dijkstra's algorithm.
 *
 * @param g The graph
 * @param source The source vertex to search from
 * @return true If a path exists to every node.
 */
void dijkstra(Graph &g, Graph::vertex_descriptor source);

/**
 * Finds single-source shortest paths using the Bellman-Ford algorithm.
 *
 * @param g The graph
 * @param source The source vertex to search from
 * @return true If a path exists to every node and no negative loops are reachable from source.
 */
bool bellmanFord(Graph &g, Graph::vertex_descriptor source);

/** Returns the 4-way/orthogonal taxicab distance from v1 to v2.
 * Always nonnegative.
 * Relies on the VertexProperties.cell attribute to work.
 * (severe ARML 2016 flashbacks)
 * @param g The graph that v1 and v2 belong to.
 * @param v1, v2 The vertices whose endpoints are used.
 * @return The 4-way/orthogonal taxicab distance between v1 and v2.
 */
int taxicab(Graph& g, Graph::vertex_descriptor v1, Graph::vertex_descriptor v2);

#endif
