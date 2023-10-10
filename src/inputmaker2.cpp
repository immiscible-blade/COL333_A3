#include "../include/inputmaker.hpp"
using namespace std;

inputmaker::inputmaker(std::string filename, std::string outfile)
{
    std::ifstream myfile;
    myfile.open(filename);
    int m;
    myfile >> graphsize >> m >> k1 >> k2;
    n = graphsize;
    // graph = (bool*)malloc((graphsize*graphsize) * sizeof(bool));
    vector<vector<bool>> new_graph(n, vector<bool>(n, false));
    graph = new_graph;
    
    vector<vector<int>> new_adj(n);
    adj = new_adj;
    
    // for (int i = 0; i < graphsize; i++){
    //     for (int j = 0; j < graphsize; j++){
    //         graph[i*graphsize + j] = false;
    //     }
    // }
    
    int e1, e2;
    for (int i = 0; i < m; i++){
        myfile >> e1 >> e2;
        // graph[(e1-1)*graphsize + (e2-1)] = true;
        // graph[(e2-1)*graphsize + (e1-1)] = true;
        adj[e1].push_back(e2);
        adj[e2].push_back(e1);
        
        graph[e1-1][e2-1] = true;
        graph[e2-1][e1-1] = true;
    }
    
    myfile.close();
    aout.open(outfile);
}

// inputmaker::~inputmaker(){
//     free(graph);
// }

void inputmaker::initialize_cnf(){
    std::cout << "graphsize: " << graphsize << std::endl;
    std::cout << "k1: " << k1 << std::endl;
    std::cout << "k2: " << k2 << std::endl;
    std::cout << (2*graphsize + ((graphsize)*(graphsize-1))/2 + (graphsize-1)*(graphsize-k1) + (graphsize-1)*(graphsize - k2)) << std::endl;
    
    int count = 0;
    for (int i = 1; i < n+1; i++){
        if (adj[i].size() < k1-1){
            count++;
        }
        if (adj[i].size() < k2-1){
            count++;
        }
    }
    
    aout << "c Hi There its a comment" << std::endl;
    aout << "p cnf " << (2*graphsize + ((graphsize)*(graphsize-1))/2 + (graphsize-1)*(graphsize-k1) + (graphsize-1)*(graphsize - k2))
     << " " << 3*((graphsize-1)*(graphsize))/2 + graphsize + 2*graphsize*(graphsize-k1) + graphsize - 3*(graphsize-k1) - 1 + 2*graphsize*(graphsize-k2) + graphsize - 3*(graphsize-k2) - 1 +
     2*graphsize*(k1) + graphsize - 3*(k1) - 1 + 2*graphsize*(k2) + graphsize - 3*(k2) - 1 
     + count << "" << std::endl;
}

int inputmaker::a(int i){
    return i;
}

int inputmaker::b(int i){
    return n + i;
}

int inputmaker::x(int i, int j){ // 1 <= j < i <= n;
    return 2*n + ((i-1)*(i-2))/2 + j;
}

int inputmaker::r_a(int i, int j){
    return 2*n + (n*(n-1))/2 + (i-1)*(n-k1) + j;
}

int inputmaker::r_b(int i, int j){
    return 2*n + (n*(n-1))/2 + (n-1)*(n-k1) + (i-1)*(n-k2) + j;
}

int inputmaker::r_a2(int i, int j){
    return 2*n + (n*(n-1))/2 + (n-1)*(n-k1) + (n-1)*(n-k2) + (i-1)*(n-k1) + j;
}

int inputmaker::r_b2(int i, int j){
    return 2*n + (n*(n-1))/2 + (n-1)*(n-k1) + (n-1)*(n-k2) + (n-1)*(n-k1) + (i-1)*(n-k2) + j;
}

void inputmaker::make_clauses(){
    
    for (int i = 1; i < n+1; i++){
        if (adj[i].size() < k1-1) aout << a(i) << " " << 0 << endl;
        if (adj[i].size() < k2-1) aout << b(i) << " " << 0 << endl;
    }
    
    // Xij
    int count = 0;
    for (int i = 1; i < n+1; i++){
        for (int j = 1; j < i; j++){
            if (graph[i-1][j-1]) aout << x(i, j) << " " << 0 << endl;
            // if (graph[n*(i-1) + (j-1)]) aout << x(i, j) << " " << 0 << endl;
            else aout << "-" << x(i, j) << " " << 0 << endl;
            count++;
        }
    }
    cout << count << endl;
    
    // Ai v Bi
    for (int i = 1; i < n+1; i++){
        aout << a(i) << " " << b(i) << " " << 0 << endl;
        count++;
    }
    cout << count << endl;
    
    // implies both
    for (int i = 1; i < n+1; i++){
        for (int j = 1; j < i; j++){
            aout << a(i) << " " << a(j) << " " << x(i, j) << " " << 0 << endl;
            aout << b(i) << " " << b(j) << " " << x(i, j) << " " << 0 << endl;
            count+=2;
        }
    }
    cout << count << endl;
    
    // sequential both
    
    for (int i = 1; i < n; i++){
        aout << "-" << a(i) << " " << r_a(i, 1) << " " << 0 << endl;
        // aout << "-" << b(i) << " " << r_b(i, 1) << " " << 0 << endl;
        count += 1;
    }
    cout << count << endl;
    
    for (int i = 2; i < n; i++){
        for (int j = 1; j < (n-k1)+1; j++){
            aout << "-" << r_a(i-1, j) << " " << r_a(i, j) << " " << 0 << endl;
            count++;
        }
    }
    cout << count << endl;
    
    for (int i = 2; i < n; i++){
        for (int j = 2; j < (n-k1)+1; j++){
            aout << "-" << a(i) << " -" << r_a(i-1, j-1) << " " << r_a(i, j) << " " << 0 << endl;
            count++;
        }
    }
    cout << count << endl;
    
    //
    for (int j = 2; j < (n-k1)+1; j++){
        aout << "-" << r_a(1, j) << " " << 0 << endl;
        count++;
    }
    cout << count << endl;
    
    for (int i = 2; i < n+1; i++){
        aout << "-" << a(i) << " -" << r_a(i-1, n-k1) << " " << 0 << endl;
        // aout << "-" << b(i) << " -" << r_b(i-1, n-k2) << " " << 0 << endl;
        count+=1;
    }
    cout << count << endl;
    
    for (int i = 1; i < n; i++){
        aout << "-" << b(i) << " " << r_b(i, 1) << " " << 0 << endl;
        // aout << "-" << b(i) << " " << r_b(i, 1) << " " << 0 << endl;
        count += 1;
    }
    cout << count << endl;
    
    for (int j = 2; j < (n-k2)+1; j++){
        aout << "-" << r_b(1, j) << " " << 0 << endl;
        count++;
    }
    cout << count << endl;
    //
    
    for (int i = 2; i < n; i++){
        for (int j = 1; j < (n-k2)+1; j++){
            aout << "-" << r_b(i-1, j) << " " << r_b(i, j) << " " << 0 << endl;
            count++;
        }
    }
    cout << count << endl;
    
    for (int i = 2; i < n; i++){
        for (int j = 2; j < (n-k2)+1; j++){
            aout << "-" << b(i) << " -" << r_b(i-1, j-1) << " " << r_b(i, j) << " " << 0 << endl;
            count++;
        }
    }cout << count << endl;
    
    for (int i = 2; i < n+1; i++){
        // aout << "-" << a(i) << " -" << r_a(i-1, n-k1) << " " << 0 << endl;
        aout << "-" << b(i) << " -" << r_b(i-1, n-k2) << " " << 0 << endl;
        count+=1;
    }
    cout << count << endl;
    
    // atleast
    
    for (int i = 1; i < n; i++){
        aout << a(i) << " " << r_a2(i, 1) << " " << 0 << endl;
        // aout << "-" << b(i) << " " << r_b(i, 1) << " " << 0 << endl;
        count += 1;
    }
    cout << count << endl;
    
    for (int i = 2; i < n; i++){
        for (int j = 1; j < k1+1; j++){
            aout << "-" << r_a2(i-1, j) << " " << r_a2(i, j) << " " << 0 << endl;
            count++;
        }
    }
    cout << count << endl;
    
    for (int i = 2; i < n; i++){
        for (int j = 2; j < k1+1; j++){
            aout << a(i) << " -" << r_a2(i-1, j-1) << " " << r_a2(i, j) << " " << 0 << endl;
            count++;
        }
    }
    cout << count << endl;
    
    //
    for (int j = 2; j < k1+1; j++){
        aout << "-" << r_a2(1, j) << " " << 0 << endl;
        count++;
    }
    cout << count << endl;
    
    for (int i = 2; i < n+1; i++){
        aout << a(i) << " -" << r_a2(i-1, k1) << " " << 0 << endl;
        // aout << "-" << b(i) << " -" << r_b(i-1, n-k2) << " " << 0 << endl;
        count+=1;
    }
    cout << count << endl;
    
    for (int i = 1; i < n; i++){
        aout << b(i) << " " << r_b2(i, 1) << " " << 0 << endl;
        // aout << "-" << b(i) << " " << r_b(i, 1) << " " << 0 << endl;
        count += 1;
    }
    cout << count << endl;
    
    for (int j = 2; j < k2+1; j++){
        aout << "-" << r_b2(1, j) << " " << 0 << endl;
        count++;
    }
    cout << count << endl;
    //
    
    for (int i = 2; i < n; i++){
        for (int j = 1; j < k2+1; j++){
            aout << "-" << r_b2(i-1, j) << " " << r_b2(i, j) << " " << 0 << endl;
            count++;
        }
    }
    cout << count << endl;
    
    for (int i = 2; i < n; i++){
        for (int j = 2; j < k2+1; j++){
            aout << b(i) << " -" << r_b2(i-1, j-1) << " " << r_b2(i, j) << " " << 0 << endl;
            count++;
        }
    }cout << count << endl;
    
    for (int i = 2; i < n+1; i++){
        // aout << "-" << a(i) << " -" << r_a(i-1, n-k1) << " " << 0 << endl;
        aout << b(i) << " -" << r_b2(i-1, k2) << " " << 0 << endl;
        count+=1;
    }
    cout << count << endl;
    
    
}

