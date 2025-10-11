#include "sparse_graph.hpp"
#include <utility>
#include <algorithm>

sparse_graph::sparse_graph(){
    build(0, std::vector<int>());
}

sparse_graph::sparse_graph(const int _num_vertices){
    build(_num_vertices, std::vector<int>());
}

sparse_graph::sparse_graph(const int _num_vertices, const std::vector<int>& _edges){
    build(_num_vertices, _edges);
}

bool sparse_graph::adjacent(const int _u, const int _v) const{
    return (std::find(graph[_u].begin(), graph[_u].end(), _v) != graph[_u].end()) || (std::find(graph[_v].begin(), graph[_v].end(), _u) != graph[_v].end());
}

void sparse_graph::insert(const int u, const int v){

}

void sparse_graph::erase(const int _u, const int _v){
    std::vector<int>::const_iterator itr;

    itr = std::find(graph[_u].begin(), graph[_u].end(), _v);
    if(itr != graph[_u].end()) graph[_u].erase(itr);
    itr = std::find(graph[_v].begin(), graph[_v].end(), _u);
    if(itr != graph[_v].end()) graph[_v].erase(itr);
}

void sparse_graph::build(const int _num_vertices, const std::vector<int>& _edges){

}