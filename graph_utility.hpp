#ifndef GRAPH_UTILITY_HPP
#define GRAPH_UTILITY_HPP 1

#include <vector>

/*
Assumes graph has no self-loops and multiple edges
*/
int find_arboricity_approx(const std::vector<std::vector<int>>& adj_list);

#endif /* GRAPH_UTILITY_HPP */