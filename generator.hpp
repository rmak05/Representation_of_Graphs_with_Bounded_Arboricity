#ifndef GENERATOR_HPP
#define GENERATOR_HPP 1

#include <vector>

enum class graph_type{
    sparse,
    count,
    invalid
};

/*
G(V, E)
V = {0, 1, ..., n - 1}
*/
class generator{
public:
    static std::vector<std::pair<int, int>> generate_sparse_graph(const int _n, const int _arboricity);
};

#endif /* GENERATOR_HPP */ 