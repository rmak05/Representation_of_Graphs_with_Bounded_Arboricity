#ifndef SPARSE_GRAPH_HPP
#define SPARSE_GRAPH_HPP 1

#include <vector>
#include <utility>

class sparse_graph{
protected:
    std::vector<std::vector<int>>   out_list;
    int                             arboricity;

public:
    sparse_graph();
    sparse_graph(const int _num_vertices, const int _arboricity);
    sparse_graph(const int _num_vertices, const std::vector<std::pair<int, int>>& _edges, const int _arboricity);

    bool adjacent(const int _u, const int _v) const;
    void insert(const int _u, const int _v);
    void erase(const int _u, const int _v);
    void build(const int _num_vertices, const std::vector<std::pair<int, int>>& _edges, const int _arboricity);
};

#endif /* SPARSE_GRAPH_HPP */