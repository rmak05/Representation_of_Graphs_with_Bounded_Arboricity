#include "sparse_graph.hpp"
#include <utility>
#include <algorithm>
#include <stack>

/*
For now, bound checks aren't being performed
*/

sparse_graph::sparse_graph(){
    build(0, std::vector<std::pair<int, int>>(), 0);
}

sparse_graph::sparse_graph(const int _num_vertices, const int _arboricity){
    build(_num_vertices, std::vector<std::pair<int, int>>(), _arboricity);
}

sparse_graph::sparse_graph(const int _num_vertices, const std::vector<std::pair<int, int>>& _edges, const int _arboricity){
    build(_num_vertices, _edges, _arboricity);
}

bool sparse_graph::adjacent(const int _u, const int _v) const{
    return (std::find(adj_list[_u].begin(), adj_list[_u].end(), _v) != adj_list[_u].end()) || (std::find(adj_list[_v].begin(), adj_list[_v].end(), _u) != adj_list[_v].end());
}

void sparse_graph::insert(const int _u, const int _v){
    adj_list[_u].push_back(_v);

    if(static_cast<int>(adj_list[_u].size()) == arboricity + 1){
        std::stack<int> stk;

        stk.push(_u);
        while(!stk.empty()){
            int w = stk.top();
            stk.pop();

            for(auto& x : adj_list[w]){
                adj_list[x].push_back(w);

                if(static_cast<int>(adj_list[x].size()) == arboricity + 1){
                    stk.push(x);
                }
            }

            adj_list[w].clear();
        }
    }
}

void sparse_graph::erase(const int _u, const int _v){
    std::vector<int>::const_iterator itr;

    itr = std::find(adj_list[_u].begin(), adj_list[_u].end(), _v);
    if(itr != adj_list[_u].end()){
        adj_list[_u].erase(itr);
        return;
    }
    itr = std::find(adj_list[_v].begin(), adj_list[_v].end(), _u);
    if(itr != adj_list[_v].end()){
        adj_list[_v].erase(itr);
    }
}

void sparse_graph::build(const int _num_vertices, const std::vector<std::pair<int, int>>& _edges, const int _arboricity){
    arboricity = _arboricity;

    adj_list.clear();
    adj_list.resize(_num_vertices);

    for(auto& edge :_edges){
        insert(edge.first, edge.second);
    }
}