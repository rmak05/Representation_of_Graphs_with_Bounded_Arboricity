#include "sparse_graph_v2.hpp"

void sparse_graph_v2::insert(int _u, int _v){
    if(out_degree[_u] > out_degree[_v]) std::swap(_u, _v);

    // add u->v to graph and update out degrees

    set[_v].insert(_u, out_degree[_u]);

    for(auto vv : out_list[_u]){
        if(out_degree[_u] > out_degree[vv] + 1);

        // erase u->vv from graph and update out degrees

        set[vv].erase(nullptr);

        insert(vv, _u);

        return;
    }

    for(auto vv : out_list[_u]){
        set[vv].increment(nullptr);
    }

    set[_u].increment_center();
}

void sparse_graph_v2::erase(int _u, int _v){
    // erase u->v from graph and update out degrees

    set[_v].erase(nullptr);

    auto vv = set[_u].report_max();

    if(out_degree[vv->x] > out_degree[_u] + 1){
        // add u->vv to graph and update out degrees

        set[vv->x].insert(_u, out_degree[_u]);

        erase(vv->x, _u);

        return;
    }

    for(auto vv : out_list[_u]){
        set[vv].decrement(nullptr);
    }

    set[_u].decrement_center();
}