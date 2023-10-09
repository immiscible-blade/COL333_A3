#pragma once

#include <vector>
#include <algorithm>
#include <iostream>
#include <fstream>
#include <string>

class inputmaker
{
private:
    std::string outfile;
    std::ofstream aout;
    bool* graph; // use as graph[i*graphsize + j]
public:
    int graphsize;
    int k1;
    int k2;
    inputmaker(std::string filename, std::string outfile); // make graph
    void initialize_cnf(); // minisat initial line
    void make_subgraphs_clauses(); // Ais and Bis
    void make_edges_clauses(); // adjacency matrix flattened
    void make_fullsubgraph_clauses(); // connected subgraph
    void make_atmostk_clauses(int k, int start_index); // one function called twice for both sub graph, use start_index to differentiate
    void close_out(); // close aout
    ~inputmaker();
};

