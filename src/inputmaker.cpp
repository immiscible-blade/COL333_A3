#include "../include/inputmaker.hpp"

inputmaker::inputmaker(std::string filename, std::string outfile):outfile(outfile)
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
    myfile.close();
    aout.open(outfile, std::ios::app);
}

// inputmaker::~inputmaker()
// {
// }
// myfile.open("example.txt", ios::app)
void inputmaker::initialize_cnf()
{
    aout << "c Hi There its a comment\n";
    aout << "p cnf " << (2*graphsize + (graphsize)*(graphsize-1)/2 + (graphsize-1)*(graphsize-k1) + (graphsize-1)*(graphsize - k2)) << " " << "(no. of clauses)\n";
}

void inputmaker::make_subgraphs_clauses()
{
    
}

void inputmaker::make_edges_clauses()
{
}

void inputmaker::make_fullsubgraph_clauses()
{    
}

void inputmaker::make_atmostk_clauses(int k, int start_index)
{
}

void inputmaker::close_out()
{
    aout.close();
}