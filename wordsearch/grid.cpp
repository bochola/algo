// IMPORTS
#include "grid.h"

Grid::Grid() {
    // Set pointer to matrix as NULL
    this->matrix = NULL;
    // Set rowsize to 0
    this->rowsize = 0;
}

Grid::Grid(string filepath) {
    // Call default constructor
    Grid();

    // Open file
    this->open(filepath);

    // Fill char matrix
    this->store();

    // Close file
    this->close();
}

Grid::Grid(const Grid &obj) {
    this->matrix = obj.matrix;
    this->rowsize = obj.rowsize;
}

Grid::~Grid() {
    // Delete the matrix
    for (int i = 0; i < this->rowsize; i++ )
        //free(this->matrix[i]);
    //free(this->matrix);

    // Close the file
    this->close();
}

void Grid::open(string filepath) {
    // Open file in filepath
    this->file.open(filepath);
}

void Grid::store() {
    // String to store a line
    string line;

    // Boolean to check if reading the first line
    bool first = true;

    // Integers to store the row x col size for the char array
    int m = 0, n = 0;

    // Integers to hold the row iterator for the char aray
    int ii = 0;

    // Seperator between characters for the grid files
    string sep = " ";

    // Integer to keep track of row size
    int sz;

    // Read the file if the file is open
    if(this->file.is_open()) {
        // Loop through all the lines of the file
        while(getline(this->file, line)) {
            // Get Char Array Size from First Line of FIle
            if(first) {
                // Find the space that seperates the size specification in the first line of the file
                int spaceloc = line.find(" ");

                // Get the row x col size from the size specification in the first line of the file
                int m = stoi(line.substr(0, spaceloc));
                int n = stoi(line.substr(spaceloc+1,line.length()-1));
                
                // Initalize char 2-D matrix and rowsize
                this->rowsize = m;
                this->matrix = (char**) calloc(this->rowsize, sizeof(char*));
                for(int i = 0; i < this->rowsize; i++) {
                    this->matrix[i] = (char*) calloc(n, sizeof(char*));
                }

                // Set sz variable
                sz = this->rowsize;

                // Not reading first anymore
                first = false;
            }
            else {
                // Get length of line
                int len = line.length();
                
                // Check if the length of the string matches the specified col length
                // Otherwise fill the char matrix
                // ASSUMPTION: Input files format adhere to the file size tag at the top
                if(len != n && n != 0) {
                    // Do nothing
                }        
                else if(ii < sz) {
                    // Counter for filling a row
                    int counter = 0;

                    // Loop through all characters between spaces
                    for(size_t p=0, q=0; p != line.npos; p=q) {
                        string temp = line.substr(p+(p!=0), (q=line.find(sep.c_str(), p+1))-p-(p!=0));
                        this->matrix[ii][counter] = temp[0];
                        counter++;
                    }
                    // Increment row iterator
                    ii++;
                    // Code inspired by: https://stackoverflow.com/questions/236129/how-do-i-iterate-over-the-words-of-a-string
                }
            }
        }
    }
}

int Grid::changerow(int row, Direction dir) {
    switch(dir) {
        case LEFT:  return absoluteIndex(row);
        case RIGHT: return absoluteIndex(row);
        case UP:    return absoluteIndex(row-1);
        case DOWN:  return absoluteIndex(row+1);
        case DIAGONAL_UP_LEFT:      return absoluteIndex(row-1);
        case DIAGONAL_DOWN_LEFT:    return absoluteIndex(row+1);
        case DIAGONAL_UP_RIGHT:     return absoluteIndex(row-1);
        case DIAGONAL_DOWN_RIGHT:   return absoluteIndex(row+1);
        default: return -1;
    }
}

int Grid::changecol(int col, Direction dir) {
    switch(dir) {
        case LEFT:  return this->absoluteIndex(col-1);
        case RIGHT: return this->absoluteIndex(col+1);
        case UP:    return this->absoluteIndex(col);
        case DOWN:  return this->absoluteIndex(col);
        case DIAGONAL_UP_LEFT:      return this->absoluteIndex(col-1);
        case DIAGONAL_DOWN_LEFT:    return this->absoluteIndex(col-1);
        case DIAGONAL_UP_RIGHT:     return this->absoluteIndex(col+1);
        case DIAGONAL_DOWN_RIGHT:   return this->absoluteIndex(col+1);
        default: return -1;
    }
}

int Grid::absoluteIndex(int index) {
    if(index >= 0 && (index < this->rowsize))
        return index;
    else if(index >= this->rowsize)
        return index - this->rowsize;
    else 
        return this->rowsize + index;
}

string Grid::trace(int row, int col, Direction dir, int size) {
    // If the inputted size exceeds the row size of the grid, then return empty string
    if(size > this->rowsize) return "";

    // Initialize string that stores result
    string result;

    // Counter to check the number of items filled in the string
    int counter = 0;

    // Variables to keep track of the indexes that are used to read from the char matrrix
    // m - row index, n - col index
    int m = absoluteIndex(row);
    int n = absoluteIndex(col);

    // Place first character in string based on the initial row and col value
    result.push_back(this->matrix[m][n]);
    counter++;
    
    // Fill the string with the other characters by continiously update row and col indices
    while(counter < size) {
        // Change row and col based on previous row and col indices
        m = this->changerow(m, dir);
        n = this->changecol(n, dir);

        // Fill string if the changed row does not result in a errenous result (-1)
        if((m == -1) || (n == -1)) {
            // Throw exception if invalid row and column index value is encountered
            // Exception should not be encountered based on given code
            throw out_of_range("Row and Column Indices are Invalid for Tracing the Character Array, Line 166");
        }
        else {
            // Place character at the row and column index into the string
            result.push_back(this->matrix[m][n]);
            counter++;
        }
    }

    return result;
}

void Grid::close() {
    // Close file
    this->file.close();
}

char** Grid::getMatrix() {
    return this->matrix;
}

int Grid::getRowSize() {
    return this->rowsize;
}

ifstream* Grid::getFile() {
    return &(this->file);
}