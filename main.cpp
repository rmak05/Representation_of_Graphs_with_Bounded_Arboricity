#include "sparse_graph.hpp"
#include "generator.hpp"
#include "graph_utility.hpp"
#include <iostream>
#include <fstream>
#include <chrono>
#include <iomanip>

void generate_test_cases(){
    int n, c, file_no = 0;
    
    // n = 10000;
    c = 15;
    for(int i = 10000; i <= 10000; i *= 10){
        // c = i;
        n = i;
        file_no++;
    
        std::ofstream input_file("Input/input_demo_const_c_" + std::to_string(c) + "_" + std::to_string(file_no) + ".txt");
    
        auto edges = generator::generate_sparse_graph(n, c, gen_type_st::prufer_code);
        input_file << n << " " << edges.size() << " " << c << "\n";
        for(auto& e : edges){
            input_file << e.first << " " << e.second << "\n";
        }
    
        std::cout << "Done: File " << file_no << std::endl;
    }
}

void check_runtime(){
    std::cout.setf(std::ios::fixed, std::ios::floatfield);
    std::cout << std::setprecision(15);

    for(int file_no = 1; file_no <= 1; file_no++){
        std::ifstream input_file("Input/input_demo_const_c_15_" + std::to_string(file_no) + ".txt");

        int n, m, c;
        input_file >> n >> m >> c;
        std::vector<std::pair<int, int>> edges(m);
        for(int i = 0; i < m; i++){
            int u, v;
            input_file >> u >> v;

            if(i & 1) edges[i] = std::make_pair(u, v);
            else edges[i] = std::make_pair(v, u);
        }

        sparse_graph graph(n, c);

        long double total_elapsed_time = 0.0f;
        for(int i = 0; i < m; i++){
            auto start_time = std::chrono::high_resolution_clock::now();

            graph.insert(edges[i].first, edges[i].second);
            
            auto end_time = std::chrono::high_resolution_clock::now();

            auto elapsed_time = std::chrono::duration_cast<std::chrono::duration<long double, std::milli>>(end_time - start_time);

            total_elapsed_time += elapsed_time.count();
        }

        std::cout << "Input " << file_no << ":" << std::endl;
        std::cout << "Total Elapsed Time: " << total_elapsed_time << std::endl;
        std::cout << "Amortized Time: " << (total_elapsed_time / m) << std::endl;
        std::cout << std::endl;
    }
}

void approx_arboricity_test(){
    for(int file_no = 1; file_no <= 5; file_no++){
        std::ifstream input_file("Input/input_const_c_5_" + std::to_string(file_no) + ".txt");

        int n, m, c;
        input_file >> n >> m >> c;
        std::vector<std::vector<int>> adj_list(n);
        for(int i = 0; i < m; i++){
            int u, v;
            input_file >> u >> v;

            adj_list[u].emplace_back(v);
            adj_list[v].emplace_back(u);
        }

        input_file.close();

        auto start_time = std::chrono::high_resolution_clock::now();

        std::cout << find_arboricity_approx(adj_list) << std::endl;

        auto end_time = std::chrono::high_resolution_clock::now();
        auto elapsed_time = std::chrono::duration_cast<std::chrono::duration<long double, std::milli>>(end_time - start_time);

        std::cout << "Elapsed Time: " << elapsed_time.count() << std::endl;
        std::cout << std::endl;
    }
}

int main(){
    std::cout << "Start" << std::endl;

    // generate_test_cases();
    // check_runtime();
    approx_arboricity_test();

    std::cout << "End" << std::endl;

    return 0;
}