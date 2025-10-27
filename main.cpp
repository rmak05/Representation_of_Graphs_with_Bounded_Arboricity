#include "sparse_graph.hpp"
#include "generator.hpp"
#include <iostream>

int main(){
    int n = 1000, c = 500;
    auto edges = generator::generate_sparse_graph(n, c);
    std::cout << edges.size() << std::endl;
    
    sparse_graph graph(n, edges, c);
    
    std::cout << "Working" << std::endl;

    return 0;
}