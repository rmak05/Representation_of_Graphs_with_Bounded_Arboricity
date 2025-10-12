#include "generator.hpp"
#include <set>
#include <random>
#include <chrono>

std::vector<std::pair<int, int>> generator::generate_sparse_graph(const int _n, const int _arboricity){
    std::set<std::pair<int, int>> edges;
    std::mt19937 rng(static_cast<unsigned>(std::chrono::steady_clock::now().time_since_epoch().count()));
    std::uniform_int_distribution<> uniform_dist;

    for(int turn = 0; turn < _arboricity; turn++){
        std::vector<int> components(_n);
    
        for(int i = 0; i < _n; i++) components[i] = i;
    
        while(components.size() > 1u){
            auto pick_random_component = [&]()->int{
                uniform_dist.param(std::uniform_int_distribution<>::param_type(0, static_cast<int>(components.size()) - 1));
                int random_component = uniform_dist(rng);

                std::swap(components[random_component], components.back());
                random_component = components.back();
                components.pop_back();

                return random_component;
            };

            int random_component_1 = pick_random_component();
            int random_component_2 = pick_random_component();

            if(random_component_1 > random_component_2) std::swap(random_component_1, random_component_2);
    
            edges.emplace(random_component_1, random_component_2);
            components.push_back(random_component_1);
        }
    }

    return std::vector<std::pair<int, int>>(edges.begin(), edges.end());
}