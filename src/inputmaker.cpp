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
    for (int i = 1; i < graphsize+1; i++)
    {
        aout << i << " " << i+graphsize << '\n';
    }
}

void inputmaker::make_edges_clauses()
{
    int ij = 2*graphsize+1;
    for (int i = 0; i < graphsize; i++)
    {
        for (int j = 0; j < i; j++)
        {
            if (graph[i*graphsize+j])
            {
                aout << ij << " 0\n";
            }
            else
            {
                aout << -ij << " 0\n";
            }
            ij++;
        }
    }
}

void inputmaker::make_fullsubgraph_clauses()
{
    for (int i = 1; i < graphsize+1; i++)
    {
        for (int j = 1; j < i; j++)
        {
            aout << i << " " << j << " " << 2*graphsize + j + (i-1)*(i-2)/2 << " 0\n";
        }
    }
    for (int i = 1; i < graphsize+1; i++)
    {
        for (int j = 1; j < i; j++)
        {
            aout << i+graphsize << " " << j+graphsize << " " << 2*graphsize + j + (i-1)*(i-2)/2 << " 0\n";
        }
    }
}

void inputmaker::make_atmostk_clauses(int k, bool forwho)
{

}

void inputmaker::close_out()
{
    aout.close();
}