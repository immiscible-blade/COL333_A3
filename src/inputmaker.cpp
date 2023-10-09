#include "../include/inputmaker.hpp"

inputmaker::inputmaker(std::string filename)
{
    std::ifstream myfile;
    myfile.open(filename);
    int m;
    myfile >> graphsize >> m >> k1 >> k2;
    graph = (bool*)malloc((graphsize*graphsize) * sizeof(bool));
    for (int i = 0; i < graphsize; i++)
    {
        for (int j = 0; j < graphsize; j++)
        {
            graph[i*graphsize + j] = false;
        }
    }
    int e1, e2;
    for (int i = 0; i < m; i++)
    {
        myfile >> e1 >> e2;
        graph[(e1-1)*graphsize + (e2-1)] = true;
        graph[(e2-1)*graphsize + (e1-1)] = true;
    }
}

// inputmaker::~inputmaker()
// {
// }
// myfile.open("example.txt", ios::app)
void inputmaker::make_atmostk_clauses(std::string outfile, int k, int start_index)
{
}

void initialize_cnf(std::string outfile)
{
}

void make_subgraphs_clauses(std::string outfile)
{
}

void make_edges_clauses(std::string outfile)
{
}

void make_fullsubgraph_clauses(std::string outfile)
{    
}