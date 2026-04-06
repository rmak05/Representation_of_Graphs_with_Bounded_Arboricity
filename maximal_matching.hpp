#ifndef MAXIMAL_MATCHING_HPP
#define MAXIMAL_MATCHING_HPP 1

#include <vector>
#include "linked_list.hpp"

class graph_maximal_matching{
private:
    bool list_contains(const linked_list<list_node>& _list, int _vertex) const;
    bool erase_vertex_from_out_list(linked_list<list_node>& _list, int _vertex); /* returns true if erased successfully */
    void notify_out_neighbours(int _u, bool _matched);

protected:
    int                                 arboricity;
    std::vector<int>                    matching; /* if v is matched to u, matching[v] = u, else matching[v] = -1 */
    std::vector<linked_list<list_node>> in_list_matched;
    std::vector<linked_list<list_node>> in_list_unmatched;
    std::vector<linked_list<list_node>> out_list;
    
public:
    graph_maximal_matching();
    graph_maximal_matching(const int _num_vertices, const int _arboricity);
    graph_maximal_matching(const int _num_vertices, const std::vector<std::pair<int, int>>& _edges, const int _arboricity);

    bool adjacent(const int _u, const int _v) const;
    void insert(int _u, int _v);
    void erase(const int _u, const int _v);
    void build(const int _num_vertices, const std::vector<std::pair<int, int>>& _edges, const int _arboricity);
    int get_matched_vertex(const int _u) const;
};

#endif /* MAXIMAL_MATCHING_HPP */