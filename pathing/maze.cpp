// IMPORTS
#include "Maze.h"

Maze::Maze() {
    // Set pointer to NULL
    ifstream *file  = NULL;

    // Init number of rows and cols
    int rows = 0;
    int cols = 0;
}

Maze::Maze(ifstream *in) {
    // Call default constructor
    *this = Maze();

    // Set file stream
    this->file = in;

    // Check if file is opened
    if(!this->file->is_open()) throw runtime_error("File is not opened!");

    // Get rows and columns
    this->file->operator >> (this->rows);
    this->file->operator >> (this->cols);

    // Initialize maze vector
    this->maze = vector<vector<bool> >(this->rows, vector<bool>(this->cols));

    // Hold each line
    string line = "";
        
    // Counter for lines iterated through
    int i = 0;

    // Temporary char to hold each character
    char temp;

    // Loop through all vectors and fill maze
    while(getline(*this->file, line)) {
        if(line.length() > 1) {
            for(int j = 0; j < this->cols; j++) {
                if(j != 100)
                    temp = line[j+1];

                // If character is '0' then maze is free, otherwise it is noT
                if(temp == 'O') this->maze[i][j] = true;
                else this->maze[i][j] = false;
            }
            i++;
        }
    }

    // Close the file
    this->file->close();
}

void Maze::mapMazeToGraph(Graph &g) {
    int vertex = 0;
    Graph::vertex_descriptor desc;

    for(int i = 0; i < this->rows; i++) {
        for(int j = 0; j < this->cols; j++) {
            if(maze[i][j]) {
                // Add vertex
                desc = boost::add_vertex(g);
                
                // Set vertex cell
                g[vertex].cell = std::pair<int,int>(i,j);
                g[vertex].weight = INITIAL_WEIGHT;

                // Set predesor vertex and add edge
                if(vertex != 0) {
                    g[vertex].pred = vertex-1;
                    EdgeProperties e;
                    e.weight = INITIAL_WEIGHT;
                    add_edge(vertex-1,vertex,e,g);
                }

                // If the first vertex hold start point
                if(vertex == 0) {
                    this->startPoint = g[vertex].cell;
                    this->startPoint_v = desc;
                }

                // Next vertex
                vertex++;
            }
        }
    }
    // Hold end point
    this->endPoint = g[vertex].cell;
    this->endPoint_v = desc;
}

void Maze::printPath(Graph::vertex_descriptor end, stack<Graph::vertex_descriptor> &s, Graph g) {}

void Maze::clearVisited(Graph &g) {
    int vertices = num_vertices(g);
    
    for(int i = 0; i < vertices; i++)
        g[i].visited = 0;
}

void Maze::setNodeWeights(Graph &g, int w) {
    int vertices = num_vertices(g);

    for(int i = 0; i < vertices; i++)
        g[i].weight = w;
}

void Maze::clearMarked(Graph &g) {
    int vertices = num_vertices(g);
    
    for(int i = 0; i < vertices; i++)
        g[i].marked = false;
}

void Maze::print(int x1, int y1, int x0, int y0) {
    cout << endl;
    
    // Check if indices are in range
    if(!pointIndexInRange(x1,y1) || !pointIndexInRange(x0,y0))
        throw std::out_of_range("Maze index out of range");

    // Print maze
    for(int i =0; i < this->rows; i++) {
        for(int j = 0; j < this->cols; j++) {
            // Print * if goal
            if(i == x1 && j == y1) cout << "*";
            // Print + if current
            else if(i == x0 && j == y0) cout << "+";
            // Print " " if maze is free
            else if(this->maze[i][j]) cout << "O";
            // Print X if maze is not free
            else cout << "X";
        }
        cout << endl;
    }
    cout << endl;
}

void Maze::print() {
    cout << endl;

    // Print maze
    for(int i = 0; i < this->rows; i++) {
        for(int j = 0; j < this->cols; j++) {
            // Print " " if maze is free
            if(this->maze[i][j]) cout << " ";
            // Print X if maze is not free
            else cout << "X";
        }
        cout << endl;
    }

    cout << endl;
}

int Maze::numRows() {
    return this->rows;
}

int Maze::numCols() {
    return this->cols;
} 

bool Maze::pointIndexInRange(int row, int col) {
    return this->rowIndexInRange(row) && this->colIndexInRange(col);
}

bool Maze::rowIndexInRange(int index) {
    if(index < 0 || index > this->rows)
        return false;
    else 
        return true;
}

bool Maze::colIndexInRange(int index) {
    if(index < 0 || index > this->cols)
        return false;
    else 
        return true;
}

ostream& operator<<(ostream& ostr, const Graph& g) {
    ostr << "Order: " << boost::num_vertices(g) << std::endl;

    ostr << std::endl << "VERTEXES/VERTICES/VORTICES" << std::endl;
    std::pair<Graph::vertex_iterator, Graph::vertex_iterator> vItr;
    for (vItr = boost::vertices(g); vItr.first != vItr.second; ++vItr.first) {
        auto vertexCurrent = *vItr.first;
        auto& vertexProp = g[vertexCurrent];
        ostr << "Vertex: " << vertexCurrent << std::endl
            << "- Location: (" << vertexProp.cell.first << ","
            << g[vertexCurrent].cell.second << ")" << std::endl
            << "- Predecessor: " << vertexProp.pred << std::endl
            << "- Weight: " << vertexProp.weight << std::endl
            << "- Visited/Color: " << vertexProp.visited << std::endl
            << "- Marked: " << (vertexProp.marked ? "Yes" : "No") << std::endl;
    }

    ostr << std::endl << "EDGES" << std::endl;
    std::pair<Graph::edge_iterator, Graph::edge_iterator> eItr;
    for (eItr = boost::edges(g); eItr.first != eItr.second; ++eItr.first) {
        auto edgeCurrent = *eItr.first;
        auto& edgeProp = g[edgeCurrent];
        ostr << "Edge from " << boost::source(edgeCurrent, g)
            << " to " << boost::target(edgeCurrent, g)
            << "; Weight: " << edgeProp.weight << std::endl;
    }

    return ostr;
}

Graph readGraph(std::ifstream& infile) {
    // stores the number of vertices in the graph
    int order;
    infile >> order;

    // create new graph
    Graph g(order);

    // read in start and end nodes
    int start;
    infile >> start;
    // what are we supposed to do with this?

    int end;
    infile >> end;
    // what about this?

    // read in edges
    while (infile && infile.peek() != '.') {
        int vertexSource, vertexTarget, weight;
        infile >> vertexSource >> vertexTarget >> weight;
        Graph::edge_descriptor edgeNew = boost::add_edge(vertexSource, vertexTarget, g).first;
        g[edgeNew].weight = weight;
    }

    return g;
}

void findPathDFSStack(Graph &g, stack<Graph::vertex_descriptor> &s, Graph::vertex_descriptor &start, Graph::vertex_descriptor &end) {
    // TODO Fix
    /*
    // Clear visited nodes
    int vs = num_vertices(g);
    for(int i = 0; i < vs; i++)
        g[i].visited = 0;

    // Push the starting node
    s.push(start);

    while(!s.empty()) {
        // Pop a vertex from the stack
        Graph::vertex_descriptor v = s.top();
        s.pop();

        if(g[v].visited == 0) {
            cout << v << " ";
            g[v].visited = 1;
        }

        // Get a pair containing iterators pointing to the beginning and end of the
        // list of nodes adjacent to node v
        pair<Graph::adjacency_iterator, Graph::adjacency_iterator> vItrRange = adjacent_vertices(v,g);

        

        // Loop over adjacent nodes in the graph
        for (Graph::adjacency_iterator vItr= vItrRange.first; vItr != vItrRange.second; ++vItr) {
            if(g[*vItr].visited == 0)
                s.push(*vItr);
        }
    }
    cout << endl;
    */
}


void findPathBFS(Graph &g, stack<Graph::vertex_descriptor> &s, Graph::vertex_descriptor &start, Graph::vertex_descriptor &end) {
    
    // Clear all visited nodes

}

bool relax(Graph& g, Graph::vertex_descriptor& start, Graph::vertex_descriptor& end) {
    std::pair<Graph::edge_descriptor, bool> edge = boost::edge(start, end, g);
    return (edge.second && relax(g, edge.first));
}

bool relax(Graph& g, Graph::edge_descriptor& e) {
    if (g[boost::target(e, g)].weight > g[boost::source(e, g)].weight + g[e].weight) {
        g[boost::target(e, g)].pred = boost::source(e, g);
        g[boost::target(e, g)].weight = g[boost::source(e, g)].weight + g[e].weight;
        return true;
    }
    return false;
}

void dijkstra(Graph& g, Graph::vertex_descriptor source) {
    // priority queue for finding next vertex
    heapV<Graph::vertex_descriptor, Graph> pq;

    // initializing/resetting all vertices for search
    std::pair<Graph::vertex_iterator, Graph::vertex_iterator> vItr;
    int ABSOLUTE_UNIT = INT_MAX / 2; // basically infinite, not INT_MAX to prevent overflow
    for (vItr = boost::vertices(g); vItr.first != vItr.second; ++vItr.first) {
        g[*(vItr.first)].pred = NULL;
        g[*(vItr.first)].weight = ABSOLUTE_UNIT;
        g[*(vItr.first)].visited = 0; // 0 = white, 1 = grey, 2 = black
        pq.minHeapInsert(*vItr.first, g);
    }

    // sift source to root
    g[source].weight = 0;
    pq.buildMinHeap(boost::num_vertices(g), g);

    while (pq.size() > 0) {
        Graph::vertex_descriptor vertexCurrent = pq.extractMinHeapMinimum(g);
        g[vertexCurrent].visited = 2;
        std::pair<Graph::out_edge_iterator, Graph::out_edge_iterator> adjEdgeItr;

        // updating adjacent vertices
        for (adjEdgeItr = boost::out_edges(vertexCurrent, g);
            adjEdgeItr.first != adjEdgeItr.second; 
            ++adjEdgeItr.first) 
        {
            // dunno why I have to do this, but it fixes a compiler error
            auto edge = *adjEdgeItr.first;

            // check for negative edge weights
            if (g[edge].weight < 0) {
                throw std::invalid_argument("Negative edge weight");
            }

            // relax edges
            if (relax(g, edge)) {
                g[boost::target(edge, g)].visited = 1;
            }
        }
        // restore priority queue
        // a bit inefficient, but gets the job done
        // better for denser graphs
        pq.buildMinHeap(pq.size(), g);
    }
}

bool bellmanFord(Graph& g, Graph::vertex_descriptor source) {
    // initializing/resetting all vertices for search
    std::pair<Graph::vertex_iterator, Graph::vertex_iterator> vItr;
    int ABSOLUTE_UNIT = INT_MAX / 2; // basically infinite, not INT_MAX to prevent overflow
    for (vItr = boost::vertices(g); vItr.first != vItr.second; ++vItr.first) {
        g[*(vItr.first)].pred = NULL;
        g[*(vItr.first)].weight = ABSOLUTE_UNIT;
    }
    g[source].weight = 0;

    // iterate through the edges V-1 times
    std::pair<Graph::edge_iterator, Graph::edge_iterator> eItr;
    for (int i = 0; i < boost::num_vertices(g) - 1; i++) {
        bool wasEdgeRelaxedThisPass = false;
        for (eItr = boost::edges(g); eItr.first != eItr.second; ++eItr.first) {
            auto edge = *(eItr.first);
            wasEdgeRelaxedThisPass |= relax(g, edge);
        }
        // break if nothing was relaxed, this means that we've found the SSSP tree
        if (!wasEdgeRelaxedThisPass) {
            break;
        }
    }

    // detecting negative loops
    for (eItr = boost::edges(g); eItr.first != eItr.second; ++eItr.first) {
        if (g[boost::target(*eItr.first, g)].weight > 
            g[boost::source(*eItr.first, g)].weight + g[*eItr.first].weight) {
            return false;
        }
    }
    return true;
}
