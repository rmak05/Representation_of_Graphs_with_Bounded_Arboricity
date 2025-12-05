#ifndef GENERATOR_HPP
#define GENERATOR_HPP 1

#include <vector>

enum class graph_type{
    sparse,
    count,
    invalid
};

enum class gen_type_st{
    prufer_code,
    connected_components,
    count,
    invalid
};

/*
G(V, E)
V = {0, 1, ..., n - 1}
*/
class generator{
public:
    static std::vector<std::pair<int, int>> generate_spanning_tree(const int _n, const gen_type_st _gen_type);
    static std::vector<std::pair<int, int>> generate_sparse_graph(const int _n, const int _arboricity, const gen_type_st _gen_type);
};

#endif /* GENERATOR_HPP */ 