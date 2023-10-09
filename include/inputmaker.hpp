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
    void make_subgraphs_clauses(); // Ais and Bis both not zero
    void make_edges_clauses(); // adjacency matrix flattened
    void make_fullsubgraph_clauses(); // connected subgraph
    void make_atmostk_clauses(int k, bool forwho); // true means A, false means B
    void close_out(); // close aout
    ~inputmaker();
};

