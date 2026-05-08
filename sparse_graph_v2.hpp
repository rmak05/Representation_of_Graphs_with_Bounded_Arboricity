#ifndef SPARSE_GRAPH_V2_HPP
#define SPARSE_GRAPH_V2_HPP 1

#include <vector>
#include <utility>
#include "keyed_set.hpp"

class sparse_graph_v2{
protected:
    std::vector<int>                out_degree;
    std::vector<std::vector<int>>   out_list;
    std::vector<keyed_set>          set;

public:
    sparse_graph_v2();
    sparse_graph_v2(const int _num_vertices, const int _arboricity);
    sparse_graph_v2(const int _num_vertices, const std::vector<std::pair<int, int>>& _edges, const int _arboricity);

    bool adjacent(const int _u, const int _v) const;
    void insert(int _u, int _v);
    void erase(int _u, int _v);
    void build(const int _num_vertices, const std::vector<std::pair<int, int>>& _edges, const int _arboricity);
};

#endif /* SPARSE_GRAPH_V2_HPP */