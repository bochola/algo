// IMPORTS
// Utilizing std namespace
using namespace std;
#include <iostream> // For I/O
#include <fstream>  // For text file input/output

// Define header file
#ifndef GRID_H
#define GRID_H

/**
 * Grid is a class that reads the letters in a grid
 * from a text file and stores them in a matrix.
 */ 
class Grid {
    private:
        // Pointer to the 2-D char array that stores the letters in the grid
        char *matrix;

        // Integer that stores the row size of the 2-D char array
        int m;

        // File stream that holds the I/O stream to the text fiel
        ofstream file;

    public:
        /**
         * Default Constructor for a Grid.
         * 
         * @param void
         */
        Grid();

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
        char* getMatrix();

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
        int getM();

        /**
         * Mutator for the integer that stores the row size of the 2-D char array.
         * 
         * @param m the row size of the 2-D char array.
         * @return void
         */ 
        void setM(int m);

        /**
         * Acessor for the filestream object that holds the file.
         * 
         * @param void
         * @return the filestream object that holds the file
         */ 
        ofstream getFile();

        /**
         * Mutator for the filestream object that holds the file.
         * 
         * @param file the filestream object that holds the file
         * @return void
         */ 
        void setFile(ofstream file);
};

#endif