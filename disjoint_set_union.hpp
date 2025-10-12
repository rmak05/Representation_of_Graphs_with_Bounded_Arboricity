#ifndef DISJOINT_SET_UNION_HPP
#define DISJOINT_SET_UNION_HPP 1

#include <vector>

class dsu{
private:
    std::vector<int> parent;
    std::vector<int> set_size;

public:
    dsu(const int _n);

    int find_set(const int _v);
    void union_sets(const int _a, const int _b);
};

#endif /* DISJOINT_SET_UNION_HPP */