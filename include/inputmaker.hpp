#pragma once

#include <vector>
#include <algorithm>
#include <iostream>
#include <fstream>
#include <string>

class inputmaker
{
private:
    bool* graph; // use as graph[i*graphsize + j]
    int graphsize;
    int k1;
    int k2;
public:
    inputmaker(std::string filename); // make graph
    void initialize_cnf(std::string outfile); // minisat initial line
    void make_subgraphs_clauses(std::string outfile); // Ais and Bis
    void make_edges_clauses(std::string outfile); // adjacency matrix flattened
    void make_fullsubgraph_clauses(std::string outfile); // connected subgraph
    void make_atmostk_clauses(std::string outfile, int k, int start_index); // one function called twice for both sub graph, use start_index to differentiate
    // ~inputmaker();
};

