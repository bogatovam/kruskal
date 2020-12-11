#ifndef KRUSKAL_DISJOINT_SET_UNION_H
#define KRUSKAL_DISJOINT_SET_UNION_H

#include <vector>

class DisjointSetUnion {
private:
    bool is_path_compression_performed;

    // parent[i] = index parent of i if (i in U) else 0
    // parent[i] = i -> i root
    std::vector<uint64_t> parent;

    std::vector<uint64_t> rang;

};


#endif //KRUSKAL_DISJOINT_SET_UNION_H
