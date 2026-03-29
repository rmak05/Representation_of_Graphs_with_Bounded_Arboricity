#include <stack>
#include "maximal_matching.hpp"

graph_maximal_matching::graph_maximal_matching(const int _num_vertices, const int _arboricity){
    graph_maximal_matching::build(_num_vertices, std::vector<std::pair<int, int>>(), _arboricity);
}

void graph_maximal_matching::insert(const int _u, const int _v){
    int delta = 4 * arboricity;

    /*
    if _u and _v are unmatched, match them immediately
    */
    
    /*
    below lines update the list correctly but it is supposed to match as well if possible
    */
    out_list[_u].push_back(_v);
    if(matching[_u] == -1) partial_unmatched_list[_v].insert(_u);
    if(matching[_v] == -1) partial_unmatched_list[_u].insert(_v);

    if(static_cast<int>(out_list[_u].size()) == delta + 1){
        std::stack<int> stk;

        stk.push(_u);
        while(!stk.empty()){
            int w = stk.top();
            stk.pop();

            for(auto& x : out_list[w]){
                out_list[x].push_back(w);
                if(matching[x] == -1) partial_unmatched_list[w].insert(x);

                if(static_cast<int>(out_list[x].size()) == delta + 1){
                    stk.push(x);
                }
            }

            out_list[w].clear();
        }
    }
}

void graph_maximal_matching::erase(const int _u, const int _v){
    sparse_graph::erase(_u, _v);
    if(partial_unmatched_list[_u].contains(_v)) partial_unmatched_list[_u].erase(_v);
    if(partial_unmatched_list[_v].contains(_u)) partial_unmatched_list[_v].erase(_u);

    if(matching[_u] != _v) return;
    matching[_u] = matching[_v] = -1;

    for(int w : {_u, _v}){
        for(int x : out_list[w]){
            if(matching[x] != -1 && partial_unmatched_list[w].contains(x)){
                partial_unmatched_list[w].erase(x);
            }
        }

        if(!partial_unmatched_list[w].empty() && matching[w] == -1){
            int ww = (*partial_unmatched_list[w].begin());
            partial_unmatched_list[w].erase(ww);

            matching[w] = ww;
            matching[ww] = w;

            for(int z : {w, ww}){
                for(int y : out_list[z]){
                    if(partial_unmatched_list[y].contains(z)){
                        partial_unmatched_list[y].erase(z);
                    }
                }
            }
        }
    }
}

void graph_maximal_matching::build(const int _num_vertices, const std::vector<std::pair<int, int>>& _edges, const int _arboricity){
    sparse_graph::build(_num_vertices, _edges, _arboricity);

    matching.clear();
    matching.resize(_num_vertices, -1);

    out_list.clear();
    out_list.resize(_num_vertices);

    partial_unmatched_list.clear();
    partial_unmatched_list.resize(_num_vertices);
}