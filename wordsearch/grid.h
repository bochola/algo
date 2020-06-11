// IMPORTS
#include <iostream> // For I/O
#include <fstream>  // For text file input/output
#include <exception>// For exception
#include <string>   // For strings
// Utilizing std namespace
using namespace std;

// Define header file
#ifndef GRID_H
#define GRID_H

/**
 * Enumeration that represents iteration directions for iterating through the grid.
 */ 
enum Direction {
    LEFT = 0,   // Left Direction
    RIGHT = 1,  // Right Direction
    UP = 2,     // Up Direction
    DOWN = 3,   // Down Direction
    DIAGONAL_UP_LEFT = 4,       // Diagonal Direction, Traversing Upward and Leftward
    DIAGONAL_DOWN_LEFT = 5,     // Diagonal Direction, Traversing Downward and Leftward
    DIAGONAL_UP_RIGHT = 6,      // Diagonal Direction, Traversing Upward and Rightward
    DIAGONAL_DOWN_RIGHT = 7,    // Diagonal Direction, Traversing Downward and Rightward
};

/**
 * Grid is a class that reads the letters in a grid
 * from a text file and stores them in a matrix.
 */ 
class Grid {
    private:
        // Pointer to the 2-D char array that stores the letters in the grid
        char **matrix;

        // Integer that stores the row size of the 2-D char array
        int rowsize;

        // File stream that holds the I/O stream to the text fiel
        ifstream file;

        /**
         * Returns the absolute index of a given index.
         * The inputted index wraps around to the closest next index
         * if it is out of range or negative.
         * 
         * @param index the given index
         * @return the absolute index
         */ 
        int absoluteIndex(int index);

        /**
         * Changes a row index based on a given index and direction.
         * 
         * @param row the given index
         * @param dir the given direction
         * @return an updated row index based on the given direction
         */ 
        int changerow(int row, Direction dir);

        /**
         * Changes a col index based on a given index and direction.
         * 
         * @param col the given index
         * @param dir the given direction
         * @return an updated col index based on the given direction
         */ 
        int changecol(int col, Direction dir);

    public:
        /**
         * Default Constructor for a Grid.
         * 
         * @param void
         */
        Grid();

        /**
         * Copy Constructor for a Grid.
         * 
         * @param obj the Grid object to copy
         */ 
        Grid(const Grid &obj);

        /**
         * Constructor for a grid given a filepath.
         * Opens, reads, and closes the file based on the filepath.
         * 
         * @param filepath the given filepath
         */ 
        Grid(string filepath);

        /**
         * Default Destructor for a Grid.
         * 
         * @param void
         */ 
        ~Grid();

        /**
         * Opens a text file given its filepath.
         * 
         * @param filepath the filepath
         * @return void
         */ 
        void open(string filepath);

        /**
         * Stores the given file into the 2-D char matrix array.
         * 
         * @param void
         * @return void
         */ 
        void store();

        /**
         * Acesses a string within a given position and trace direction (and given string size).
         * 
         * @param row the row to acess the string at
         * @param col the column to acess the string at
         * @param dir the trace direction, 
         *  0 is left, 1 is right, 2 is up, 3 is down,
         *  4 is diagonal up-left, 5 is diagonal down-left, 
         *  6 is diagonal up-right, 6 is diagonal down-right
         * @param size is the string size
         */ 
        string trace(int row, int col, Direction dir, int size);

        /**
         * Closes the text file.
         * File is only closed when it is opened.
         * 
         * @param void
         * @return void
         */ 
        void close();

        /**
         * Acessor for the pointer to the 2-D char array. 
         *
         * @param void
         * @return the pointer to the 2-D char matrix array.
         */ 
        char** getMatrix();

        /**
         * Mutator for the pointer to the 2-D char array. 
         *
         * @param matrix the pointer to the 2-D char matrix array.
         * @return void
         */ 
        void setMatrix();

        /**
         * Acessor for the integer that stores the row size of the 2-D char array.
         * 
         * @param void
         * @return the row size of the 2-D char array.
         */ 
        int getRowSize();

        /**
         * Acessor for the filestream object that holds the file.
         * 
         * @param void
         * @return the filestream object that holds the file
         */ 
        ifstream* getFile();
};

#endif