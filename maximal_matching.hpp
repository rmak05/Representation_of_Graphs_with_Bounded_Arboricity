#ifndef MAXIMAL_MATCHING_HPP
#define MAXIMAL_MATCHING_HPP 1

#include <set>
#include "sparse_graph.hpp"

class graph_maximal_matching{
private:
    struct list_node{
        int vertex;
        list_node *next;
        list_node *previous;
        list_node *external;

        list_node(const int _vertex = -1, list_node *_next = nullptr, list_node *_previous = nullptr, list_node *_external = nullptr);
    };

    void insert_list_node(list_node*& _head, list_node* _node);
    void erase_list_node(list_node*& _head, list_node* _node); /* _node must exist in _head */
    bool erase_vertex_from_out_list(list_node*& _head, int _vertex); /* returns true if erased successfully */
    void notify_out_neighbours(int _u, bool _matched);

protected:
    int                     arboricity;
    std::vector<int>        matching; /* if v is matched to u, matching[v] = u, else matching[v] = -1 */
    std::vector<list_node*> in_list_matched;
    std::vector<list_node*> in_list_unmatched;
    std::vector<list_node*> out_list;
    // std::vector<std::set<int>>      partial_unmatched_list;
    
public:
    graph_maximal_matching();
    graph_maximal_matching(const int _num_vertices, const int _arboricity);
    graph_maximal_matching(const int _num_vertices, const std::vector<std::pair<int, int>>& _edges, const int _arboricity);

    void insert(int _u, int _v);
    void erase(const int _u, const int _v);
    void build(const int _num_vertices, const std::vector<std::pair<int, int>>& _edges, const int _arboricity);
};

#endif /* MAXIMAL_MATCHING_HPP */