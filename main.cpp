#include "sparse_graph.hpp"
#include "generator.hpp"
#include <iostream>

int main(){
    std::cout << "Working" << std::endl;

    auto edges = generator::generate_sparse_graph(1000, 300);
    std::cout << edges.size() << std::endl;

    return 0;
}