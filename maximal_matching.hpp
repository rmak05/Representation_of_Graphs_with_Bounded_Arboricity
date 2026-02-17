#ifndef MAXIMAL_MATCHING_HPP
#define MAXIMAL_MATCHING_HPP 1

#include <set>
#include "sparse_graph.hpp"

class graph_maximal_matching : protected sparse_graph{
protected:
    std::vector<int>                matching; /* if v is matched to u, matching[v] = u, else matching[v] = -1 */
    std::vector<std::set<int>>      partial_unmatched_list;

public:
    graph_maximal_matching();
    graph_maximal_matching(const int _num_vertices, const int _arboricity);
    graph_maximal_matching(const int _num_vertices, const std::vector<std::pair<int, int>>& _edges, const int _arboricity);

    void insert(const int _u, const int _v);
    void erase(const int _u, const int _v);
    void build(const int _num_vertices, const std::vector<std::pair<int, int>>& _edges, const int _arboricity);
};

#endif /* MAXIMAL_MATCHING_HPP */