#include "Maze.h"

int main() {
    cout << "Welcome to the Maze and Graph Processing Program" << endl;

    string input = "";

    while(input != "quit") {
        try {
            cout << "Enter filename or \"quit\": ";
            cin >> input;

            if(input.find("graph") != string::npos) {
                cout << "Reading Graph File" << endl;
                // INSERT GRAPH PROCESSING

                cout << "End Graph File Processing" << endl;
            }
            else if(input.find("maze") != string::npos) {
                cout << "Reading Maze File" << endl;
                ifstream* fin = new ifstream();
                fin->open(input);
                Maze m(fin);

                // INSERT MAZE PROCESSING
                Graph g;
                m.mapMazeToGraph(g);

                cout << "End Maze File Processing" << endl;
            }

        }
        catch(...) {
            cout << "Error Occurred" << endl;
        }
    }

    cout << "Exiting Program" << endl;
}