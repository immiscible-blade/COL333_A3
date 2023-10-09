#include "../include/inputmaker.hpp"

int main(int argc, char** argv)
{
    inputmaker* A = new inputmaker(argv[1], argv[2]);
    A->initialize_cnf();
    A->make_subgraphs_clauses();
    A->make_edges_clauses();
    A->make_fullsubgraph_clauses();
    A->make_atmostk_clauses(A->graphsize - A->k1, true);
    A->make_atmostk_clauses(A->graphsize - A->k2, false);
    A->close_out();
    delete A;
}