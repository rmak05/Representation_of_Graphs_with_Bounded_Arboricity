#include "disjoint_set_union.hpp"

dsu::dsu(int _n) :
parent(_n), set_size(_n){
    for(int i = 0; i < _n; i++){
        parent[i] = i;
        set_size[i] = 1;
    }
}

int dsu::find_set(const int _v){
    if(_v == parent[_v]) return _v;
    return (parent[_v] = find_set(parent[_v]));
}

void dsu::union_sets(const int _a, const int _b){
    int pa = find_set(_a);
    int pb = find_set(_b);

    if(pa != pb){
        if(set_size[pa] < set_size[pb]) std::swap(pa, pb);
        parent[pb] = pa;
        set_size[pa] += set_size[pb];
    }
}