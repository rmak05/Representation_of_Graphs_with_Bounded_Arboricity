#include "graph_utility.hpp"
#include <algorithm>
#include <iostream>

int find_arboricity_approx(const std::vector<std::vector<int>>& adj_list){
    int arboricity_approx = 0, n = static_cast<int>(adj_list.size()), min_degree = 0;
    std::vector<bool> visited(n, false);
    std::vector<int> degree(n, 0);
    std::vector<std::vector<int>> degree_list(n);

    for(int u = 0; u < n; u++){
        degree[u] = static_cast<int>(adj_list[u].size());
        degree_list[adj_list[u].size()].emplace_back(u);
    }

    
    for(int i = n; i >= 1; i--){
        int v = -1;
        bool found = false;

        while(!found){
            while(!degree_list[min_degree].empty()){
                auto u = degree_list[min_degree].back();

                degree_list[min_degree].pop_back();

                if(!visited[u]){
                    v = u;
                    visited[u] = true;
                    found = true;
                    break;
                }
            }

            if(!found){
                degree_list[min_degree].clear();
                min_degree++;
            }
        }

        arboricity_approx = std::max(arboricity_approx, min_degree);
        min_degree = std::max(0, min_degree - 1);

        for(auto& u : adj_list[v]){
            if(visited[u]) continue;

            degree[u]--;
            degree_list[degree[u]].emplace_back(u);
        }
    }

    return arboricity_approx;
}