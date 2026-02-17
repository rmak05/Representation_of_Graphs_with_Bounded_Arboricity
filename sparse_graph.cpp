#include <utility>
#include <algorithm>
#include <iostream>
#include <stack>
#include "sparse_graph.hpp"

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
    return (std::find(out_list[_u].begin(), out_list[_u].end(), _v) != out_list[_u].end()) || (std::find(out_list[_v].begin(), out_list[_v].end(), _u) != out_list[_v].end());
}

void sparse_graph::insert(const int _u, const int _v){
    int delta = 4 * arboricity;
    
    out_list[_u].push_back(_v);

    if(static_cast<int>(out_list[_u].size()) == delta + 1){
        std::stack<int> stk;

        stk.push(_u);
        while(!stk.empty()){
            int w = stk.top();
            stk.pop();

            for(auto& x : out_list[w]){
                out_list[x].push_back(w);

                if(static_cast<int>(out_list[x].size()) == delta + 1){
                    stk.push(x);
                }
            }

            out_list[w].clear();
        }
    }
}

void sparse_graph::erase(const int _u, const int _v){
    std::vector<int>::const_iterator itr;

    itr = std::find(out_list[_u].begin(), out_list[_u].end(), _v);
    if(itr != out_list[_u].end()){
        out_list[_u].erase(itr);
        return;
    }
    itr = std::find(out_list[_v].begin(), out_list[_v].end(), _u);
    if(itr != out_list[_v].end()){
        out_list[_v].erase(itr);
    }
}

void sparse_graph::build(const int _num_vertices, const std::vector<std::pair<int, int>>& _edges, const int _arboricity){
    arboricity = _arboricity;

    out_list.clear();
    out_list.resize(_num_vertices);

    for(auto& edge :_edges){
        insert(edge.first, edge.second);
    }
}