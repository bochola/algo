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

    // Set default start and end
    startPoint = std::pair<int, int>(0, 0);
    endPoint = std::pair<int, int>(rows - 1, cols - 1);

    // Hold each line
    string line = "";
        
    // Counter for lines iterated through
    int i = 0;

    // Temporary char to hold each character
    char temp;

    // Loop through all vectors and fill maze
    while(getline(*this->file, line)) {
        if(line.length() > 1) {
            for(int j = 0; j <= this->cols; j++) {
                temp = line[j];

                // If character is '0' then maze is free, otherwise it is noT
                switch (temp) {
                case 'O':
                  maze[i][j] = true;
                  break;
                case '+':
                  maze[i][j] = true;
                  startPoint = std::pair<int, int>(i, j);
                  break;
                case '*':
                  maze[i][j] = true;
                  endPoint = std::pair<int, int>(i, j);
                  break;
                case 'X':
                  maze[i][j] = false;
                  break;
                }
            }
            i++;
        }
    }

    // Close the file
    this->file->close();
}

Graph::vertex_descriptor& Maze::addVertex(Graph& g, int& vertex, int x, int y) {
  Graph::vertex_descriptor output = add_vertex(g);
  g[vertex].cell = std::pair<int, int>(x, y);
  g[vertex].weight = INITIAL_WEIGHT;
  vertex++;
  return output;
}
void Maze::mapMazeToGraph(Graph& g) {
  // Vertex counter
  int vertex = 0;

  // Add vertex for each area of the maze that is free
  for (int row = 0; row < this->rows; row++) {
    for (int col = 0; col < this->cols; col++) {
      if (this->maze[row][col]) {
        //std::cout << row << ' ' << col << std::endl;
        auto vd = addVertex(g, vertex, row, col);
        if (startPoint.first == row && startPoint.second == col) {
          startPoint_v = vd;
        }
        else if (endPoint.first == row && endPoint.second == col) {
          endPoint_v = vd;
        }
      }
    }
  }

  // Add edges between vertices
  for (int v = 0; v < vertex; v++) {
    // Get cell of current vertex
    auto loc = g[v].cell;
    int row = loc.first;
    int col = loc.second;

    // Loop through all remaining vertices
    for (int i = v + 1; i < vertex; i++) {
      // Get cell of next vertex
      auto loc_ = g[i].cell;
      int row_ = loc_.first;
      int col_ = loc_.second;

      // Add edges between current vertex and vertex next to it
      if (row == row_ && (col + 1) == col_) {
        EdgeProperties e;
        e.weight = INITIAL_WEIGHT;
        add_edge(v, i, e, g);
        add_edge(i, v, e, g);
      }
      // Add edges between current vertex and vertex below it
      if ((row + 1) == row_ && col == col_) {
        EdgeProperties e;
        e.weight = INITIAL_WEIGHT;
        add_edge(v, i, e, g);
        add_edge(i, v, e, g);
      }
    }
  }
}
    
std::pair<Graph::vertex_descriptor, Graph::vertex_descriptor> Maze::getGraphPoints()
{
  return std::pair<Graph::vertex_descriptor, Graph::vertex_descriptor>(startPoint_v, endPoint_v);
}

void Maze::printPath(Graph::vertex_descriptor end, stack<Graph::vertex_descriptor> &s, Graph g) {
  std::string output = toString();
  output.at((g[end].cell.first) * (cols + 1) + g[end].cell.second) = '+';

  while (s.size() > 0) {
    Graph::vertex_descriptor vd = s.top();
    s.pop();
    output.at((g[vd].cell.first) * (cols + 1) + g[vd].cell.second) = s.empty() ? '*' : '.';
  }

  std::cout << output << std::endl;
}

std::string Maze::toString() {
  std::string output;
  // preventing excessive string resizes
  output.reserve(rows * (cols + 1) + 1);

  // iterating through the maze
  for (std::vector<bool> r : maze) {
    for (bool b : r) {
      output.push_back(b ? ' ' : 'X');
    }
    output.push_back('\n');
  }
  output.pop_back();
  return output;
}

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

void readGraph(std::ifstream& infile, Graph& g, 
  Graph::vertex_descriptor& start, Graph::vertex_descriptor& end) {
    // stores the number of vertices in the graph
    int order;
    infile >> order;

    // create new graph
    g = Graph(order);

    // read in start and end nodes
    infile >> start;
    infile >> end;

    // read in edges
    while (infile && infile.peek() != '.') {
        int vertexSource, vertexTarget, weight;
        infile >> vertexSource >> vertexTarget >> weight;
        Graph::edge_descriptor edgeNew = boost::add_edge(vertexSource, vertexTarget, g).first;
        g[edgeNew].weight = weight;
    }
}

void DFSRecursiveHelper(Graph& g, Graph::vertex_descriptor& curr, Graph::vertex_descriptor& end) {
  // Mark the current node as visited
  g[curr].visited = 2;

  // Exit once end vertex has been found
  if (g[curr].cell.first == g[end].cell.first && g[curr].cell.second == g[end].cell.second) {
    // Outputting for now
    cout << curr << ": " << g[curr].cell.first << "x" << g[curr].cell.second << " ";
    cout << "Path found" << endl;
    cout << endl;
    return;
  }

  // Outputing for now
  cout << curr << ": " << g[curr].cell.first << "x" << g[curr].cell.second << " ";

  // Get a pair containing iterators pointing to the beginning and end of the
  // list of nodes adjacent to node v
  pair<Graph::adjacency_iterator, Graph::adjacency_iterator> vItrRange = adjacent_vertices(curr, g);

  // Loop over adjacent nodes in the graph, and push them into the stack
  for (Graph::adjacency_iterator vItr = vItrRange.first; vItr != vItrRange.second; vItr++) {
    // If a vertex hasnt been marked make recursive call
    if (g[*vItr].visited == 0) {
      Graph::vertex_descriptor v = *vItr;
      DFSRecursiveHelper(g, v, end);
    }
  }
}

void findPathDFSRecursive(Graph& g, Graph::vertex_descriptor& start, Graph::vertex_descriptor& end) {
  // Outputting for now
  cout << "Finding Path using DFS Stack" << endl;

  // Clear visited nodes 
  Maze::clearVisited(g);

  // Call DFS Helper
  DFSRecursiveHelper(g, start, end);
}

void findPathDFSStack(Graph& g, stack<Graph::vertex_descriptor>& s, Graph::vertex_descriptor& start, Graph::vertex_descriptor& end) {
  // Outputting for now
  cout << "Finding Path using DFS Stack" << endl;

  // Clear visited nodes
  Maze::clearVisited(g);

  // Push the starting node
  s.push(start);

  while (!s.empty()) {
    // Pop a vertex from the stack
    Graph::vertex_descriptor v = s.top();
    s.pop();

    if (g[v].cell.first == g[end].cell.first && g[v].cell.second == g[end].cell.second) {
      g[v].visited = 2;

      // Outputting for now
      cout << v << ": " << g[v].cell.first << "x" << g[v].cell.second << " ";
      cout << "Path found" << endl;
      cout << endl;
      return;
    }
    // Mark vertex as visited (don't what to mark it, so marking it using visted parameter)
    if (g[v].visited == 0) {
      g[v].visited = 2;

      // Outputing for now
      cout << v << ": " << g[v].cell.first << "x" << g[v].cell.second << " ";
    }

    // Get a pair containing iterators pointing to the beginning and end of the
    // list of nodes adjacent to node v
    pair<Graph::adjacency_iterator, Graph::adjacency_iterator> vItrRange = adjacent_vertices(v, g);

    // Loop over adjacent nodes in the graph, and push them into the stack
    for (Graph::adjacency_iterator vItr = vItrRange.first; vItr != vItrRange.second; vItr++) {
      if (g[*vItr].visited == 0)
        s.push(*vItr);
    }
  }

  // Outputting for now
  cout << "End not found" << endl;
  cout << endl;
}

stack<Graph::vertex_descriptor> aStar
(Graph& g, Graph::vertex_descriptor& start, Graph::vertex_descriptor& end) {
  // this code is more or less copy-pasted from the dijkstra function

  // note that node weight is pulling double-duty here.
  // when visited = 0 (white), weight = infinity
  // when visited = 1 (grey, frontier node), weight = "F-cost" (estimated cost)
  // when visited = 2 (black, interior node), weight = "G-cost" (cost from start)

  std::stack<Graph::vertex_descriptor> output;
  heapV<Graph::vertex_descriptor, Graph> pq;
  
  // initializing/resetting all vertices for search
  std::pair<Graph::vertex_iterator, Graph::vertex_iterator> vItr;
  int ABSOLUTE_UNIT = INT_MAX / 2; // basically infinite, not INT_MAX to prevent overflow
  Maze::clearVisited(g); // colors: 0 = white, 1 = grey, 2 = black
  Maze::setNodeWeights(g, ABSOLUTE_UNIT);
  for (vItr = boost::vertices(g); vItr.first != vItr.second; ++vItr.first) {
    g[*(vItr.first)].pred = NULL;
  }
  // sift source to root
  g[start].weight = 0;
  pq.minHeapInsert(start, g);

  while (pq.size() > 0) {
    Graph::vertex_descriptor vertexCurrent = pq.extractMinHeapMinimum(g);
    g[vertexCurrent].visited = 2;
    // update weight to g-cost
    if (vertexCurrent != start) {
      g[vertexCurrent].weight = g[g[vertexCurrent].pred].weight
        + g[boost::edge(vertexCurrent, g[vertexCurrent].pred, g).first].weight;
    }

    // compile the path stack if we've found the output
    if (vertexCurrent == end) {
      output.push(end);
      while (vertexCurrent != start) {
        output.push(vertexCurrent);
        vertexCurrent = g[vertexCurrent].pred;
      }
      return output;
    }

    std::pair<Graph::out_edge_iterator, Graph::out_edge_iterator> adjEdgeItr;

    // updating adjacent vertices
    for (adjEdgeItr = boost::out_edges(vertexCurrent, g);
      adjEdgeItr.first != adjEdgeItr.second;
      ++adjEdgeItr.first)
    {
      // dunno why I have to do this, but it fixes a compiler error
      auto edge = *adjEdgeItr.first;
      // relax edges
      Graph::vertex_descriptor source = boost::source(edge, g);
      Graph::vertex_descriptor target = boost::target(edge, g);
      // a* costs
      // actual cost from start
      int GCost = g[source].weight + g[edge].weight;
      // total cost estimate (g-cost + taxicab/heuristic cost)
      int FCost = GCost + taxicab(g, target, end);
      // update costs
      switch (g[target].visited) {
      case 1:
        if (g[g[target].pred].weight + g[boost::edge(target, g[target].pred, g).first].weight > GCost) {
          g[target].weight = FCost;
          g[target].pred = source;
          g[target].visited = 1;
        }
        break;
      case 0:
        g[target].weight = FCost;
        g[target].pred = source;
        g[target].visited = 1;
        pq.minHeapInsert(target, g);
        break;
      case 2:
        break;
      }
    }
    // restore priority queue
    // a bit inefficient, but gets the job done
    // better for denser graphs
    pq.buildMinHeap(pq.size(), g);
  }

  // output is an empty stack
  return output;
}

void findShortestPathBFS(Graph &g, Graph::vertex_descriptor &start, Graph::vertex_descriptor &end) {
    // Queue for vertices
    queue<Graph::vertex_descriptor> q;

    // Clear all visited nodes
    Maze::clearVisited(g);
    
    // Set the starting node predecessor to NULL
    g[start].pred = NULL;

    q.push(start);

    while (!q.empty()) {
        // Grab the node at the front of the queue
        Graph::vertex_descriptor &next = q.front();
        
        if (next == end) {
            cout << "BFS has found a path!\n\n";
            return;
        }
       
        // At this point, the next node in the queue is not the end, so mark it as visited and remove it
        g[next].visited = 2;
        q.pop();

        // Get its adjacent nodes
        pair<Graph::adjacency_iterator, Graph::adjacency_iterator> vItrRange = adjacent_vertices(next, g);

        // Loop over adjacent nodes and add them to the queue
        for (Graph::adjacency_iterator vItr = vItrRange.first; vItr != vItrRange.second; ++vItr) {
            // If the nodes in the adjaceny list havent been visited, add them to the queue
            if (g[*(vItr.first)].visited != 2) {
                g[*(vItr.first)].pred = next;
                q.push(*(vItr.first));
            }
        }
        
    }

    cout << "BFS could not find a path\n\n";
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
    Maze::clearVisited(g); // colors: 0 = white, 1 = grey, 2 = black
    Maze::setNodeWeights(g, ABSOLUTE_UNIT);
    for (vItr = boost::vertices(g); vItr.first != vItr.second; ++vItr.first) {
        g[*(vItr.first)].pred = NULL;
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

int taxicab(Graph& g, Graph::vertex_descriptor v1, Graph::vertex_descriptor v2) {
  return std::abs(g[v1].cell.first - g[v2].cell.first) 
    + std::abs(g[v1].cell.second - g[v2].cell.second);
}
