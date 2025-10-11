#ifndef SPARSE_GRAPH_HPP
#define SPARSE_GRAPH_HPP 1

#include <vector>

class sparse_graph{
private:
    std::vector<std::vector<int>> graph;

public:
    sparse_graph();
    sparse_graph(const int _num_vertices);
    sparse_graph(const int _num_vertices, const std::vector<int>& _edges);

    bool adjacent(const int _u, const int _v) const;
    void insert(const int u, const int v);
    void erase(const int _u, const int _v);
    void build(const int _num_vertices, const std::vector<int>& _edges);
};

#endif /* SPARSE_GRAPH_HPP */