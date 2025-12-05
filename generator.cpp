#include <set>
#include <random>
#include <chrono>
#include "generator.hpp"

std::vector<std::pair<int, int>> generator::generate_spanning_tree(const int _n, const gen_type_st _gen_type){
    if(_n <= 1) return std::vector<std::pair<int, int>>();
    if(_n == 2) return std::vector<std::pair<int, int>>({{0, 1}});

    std::vector<std::pair<int, int>> edges;
    std::mt19937 rng(static_cast<unsigned>(std::chrono::steady_clock::now().time_since_epoch().count()));

    if(_gen_type == gen_type_st::prufer_code){
        std::uniform_int_distribution<> uniform_dist(0, _n - 1);
        std::vector<int> prufer(_n - 2), degree(_n, 1);

        for(int i = 0; i < _n - 2; i++){
            prufer[i] = uniform_dist(rng);
 
            degree[prufer[i]]++;
        }
 
        int forward_ptr, lowest_leaf;
 
        for(int i = 0; i < _n; i++){
            if(degree[i] == 1){
                forward_ptr = lowest_leaf = i;
 
                break;
            }
        }
 
        for(int i = 0; i < _n - 2; i++){
            edges.emplace_back(std::min(prufer[i], lowest_leaf), std::max(prufer[i], lowest_leaf));
 
            degree[prufer[i]]--;
            degree[lowest_leaf]--;
 
            if(degree[prufer[i]] == 1 && prufer[i] < forward_ptr){
                lowest_leaf = prufer[i];
            }
            else{
                while(degree[forward_ptr] != 1) forward_ptr++;
                lowest_leaf = forward_ptr;
            }
        }
        edges.emplace_back(std::min(_n - 1, lowest_leaf), std::max(_n - 1, lowest_leaf));
    }
    else if(_gen_type == gen_type_st::connected_components){
        std::vector<int> components(_n);
    
        for(int i = 0; i < _n; i++) components[i] = i;
    
        while(components.size() > 1u){
            auto pick_random_component = [&]()->int{
                std::uniform_int_distribution<> uniform_dist(0, static_cast<int>(components.size()) - 1);
                int random_component = uniform_dist(rng);

                std::swap(components[random_component], components.back());
                random_component = components.back();
                components.pop_back();

                return random_component;
            };

            int random_component_1 = pick_random_component();
            int random_component_2 = pick_random_component();

            components.push_back(random_component_1);
            if(random_component_1 > random_component_2) std::swap(random_component_1, random_component_2);
            edges.emplace_back(random_component_1, random_component_2);
        }
    }

    return edges;
}

std::vector<std::pair<int, int>> generator::generate_sparse_graph(const int _n, const int _arboricity, const gen_type_st _gen_type){
    std::set<std::pair<int, int>> edges;
    std::mt19937 rng(static_cast<unsigned>(std::chrono::steady_clock::now().time_since_epoch().count()));
    std::uniform_int_distribution<> uniform_dist;

    for(int turn = 0; turn < _arboricity; turn++){
        std::vector<std::pair<int, int>> st_edges = generate_spanning_tree(_n, _gen_type);

        for(auto& edge : st_edges){
            edges.emplace(edge);
        }
    }

    return std::vector<std::pair<int, int>>(edges.begin(), edges.end());
}