#include "../include/inputmaker.hpp"
using namespace std;

inputmaker::inputmaker(std::string filename, std::string outfile)
{
    std::ifstream myfile;
    myfile.open(filename);
    int m;
    myfile >> graphsize >> m >> k1 >> k2;
    graph = (bool*)malloc((graphsize*graphsize) * sizeof(bool));
    
    for (int i = 0; i < graphsize; i++){
        for (int j = 0; j < graphsize; j++){
            graph[i*graphsize + j] = false;
        }
    }
    
    int e1, e2;
    for (int i = 0; i < m; i++){
        myfile >> e1 >> e2;
        graph[(e1-1)*graphsize + (e2-1)] = true;
        graph[(e2-1)*graphsize + (e1-1)] = true;
    }
    
    myfile.close();
    aout.open(outfile);
}

inputmaker::~inputmaker(){
    free(graph);
}

void inputmaker::initialize_cnf(){
    std::cout << "graphsize: " << graphsize << std::endl;
    std::cout << "k1: " << k1 << std::endl;
    std::cout << "k2: " << k2 << std::endl;
    std::cout << (2*graphsize + ((graphsize)*(graphsize-1))/2 + (graphsize-1)*(graphsize-k1) + (graphsize-1)*(graphsize - k2)) << std::endl;
    
    aout << "c Hi There its a comment" << std::endl;
    aout << "p cnf " << (2*graphsize + ((graphsize)*(graphsize-1))/2 + (graphsize-1)*(graphsize-k1) + (graphsize-1)*(graphsize - k2)) << " " << 3*((graphsize-1)*(graphsize))/2 + graphsize + 2*graphsize*(graphsize-k1) + graphsize - 3*(graphsize-k1) - 1 + 2*graphsize*(graphsize-k2) + graphsize - 3*(graphsize-k2) - 1 << "" << std::endl;
}

void inputmaker::make_subgraphs_clauses(){
    int count = 0;
    for (int i = 1; i < graphsize+1; i++){
        aout << i << " " << i+graphsize << " 0" << std::endl;
        count++;
    }
    cout <<  "make_subgraphs_clauses " << count << endl;  
}

void inputmaker::make_edges_clauses(){
    int ij = 2*graphsize+1;
    int count = 0;
    
    for (int i = 1; i < graphsize+1; i++){
        for (int j = 1; j < i; j++){
            if (graph[i*graphsize+j]){
                aout << ij << " 0" << std::endl;
            }else{
                aout << -ij << " 0" << std::endl;
            }
            ij++;
            count++;
        }
    }
    cout << "makes_edges_clauses " << count << endl;
}

void inputmaker::make_fullsubgraph_clauses(){
    int count = 0;
    
    for (int i = 1; i < graphsize+1; i++){
        for (int j = 1; j < i; j++){
            aout << i << " " << j << " " << 2*graphsize + j + ((i-1)*(i-2))/2 << " 0" << std::endl;
            count++;
        }
        
    }
    cout << "makes_fullsubgraph_clauses 1 " << count << endl;
    
    count = 0;
    for (int i = 1; i < graphsize+1; i++){
        for (int j = 1; j < i; j++){
            aout << i+graphsize << " " << j+graphsize << " " << 2*graphsize + j + ((i-1)*(i-2))/2 << " 0" << std::endl;
            count++;
        }
    }
    
    cout << "makes_fullsubgraph_clauses 2 " << count << endl;
}

int n, k1, k2;

int a(int i){
    return i;
}

int b(int i){
    return n + i;
}

int x(int i, int j){ // 1 <= j < i <= n;
    return 2*n + ((i-1)*(i-2))/2 + j;
}

int r_a(int i, int j){
    return 2*n + ((n-1)*(n-2))/2 + (i-1)*(n-k1) + j;
}

int r_b(int i, int j){
    return 2*n + ((n-1)*(n-2))/2 + (n-1)*(n-k1) + (i-1)*(n-k2) + j;
}

void inputmaker::make_atmostk_clauses(int k, bool forwho){
    int start_index;
    int startAB;
    
    if (forwho){
        start_index = 2*graphsize + ((graphsize-1)*(graphsize))/2;
        
        
        
        
    }else{
        start_index = 2*graphsize + ((graphsize-1)*(graphsize))/2 + (graphsize-1)*(graphsize-k1) + 1;
        startAB = graphsize+1;
    }
}

void inputmaker::make_atmostk_clauses(int k, bool forwho){
    int start_index;
    int startAB;
    if (forwho){
        start_index = 2*graphsize + ((graphsize-1)*(graphsize))/2 + 1;
        startAB = 1;
    }else{
        start_index = 2*graphsize + ((graphsize-1)*(graphsize))/2 + (graphsize-1)*(graphsize-k1) + 1;
        startAB = graphsize+1;
    }


    int temp_index = start_index;
    int temp_sAB = startAB;
    for (int i = 0; i < graphsize-1; i++){
        aout << -temp_sAB << " " << temp_index << " 0" << std::endl;
        temp_sAB++;
        temp_index += k;
    }

    
    temp_index = start_index+1;
    temp_sAB = startAB;
    for (int i = 1; i < k; i++){
        aout << -temp_index << " 0" << std::endl;
        temp_index++;
    }

    temp_index = start_index;
    for (int i = 1; i < graphsize; i++){
        for (int j = 0; j < k; j++){
            aout << -temp_index << " " << temp_index+k << " 0" << std::endl;
            temp_index++;
        }
    }

    temp_index = start_index;
    temp_sAB = startAB+1;
    for (int i = 1; i < graphsize; i++){
        for (int j = 1; j < k; j++){
            aout << -temp_sAB << " " << -temp_index << " " << temp_index + k << " 0" << std::endl;
            temp_index++;
        }
        temp_sAB++;
    }

    temp_index = start_index + k - 1;
    temp_sAB = startAB+1;
    for (int i = 1; i < graphsize; i++){
        aout << -temp_sAB << " " << -temp_index << " 0" << std::endl;
        temp_index += k;
        temp_sAB++;
    }
}

void inputmaker::close_out()
{
    aout.close();
}