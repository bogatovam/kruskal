#ifndef KRUSKAL_DISJOINT_SET_UNION_H
#define KRUSKAL_DISJOINT_SET_UNION_H

#include <vector>

class DisjointSetUnion {
private:

    std::vector<std::size_t> rank;
protected:

// parent[i] = index parent of i if (i in U) else 0
// parent[i] = i -> i root
    std::vector<std::size_t> parent;

    const static std::size_t NON_EXISTENT_ELEMENT = std::numeric_limits<std::size_t>::max();
public:
    void create(std::size_t v);

    std::size_t findSet(std::size_t v);

    void unionSets(std::size_t x, std::size_t y);
};

class DisjointSetUnionWithPathCompression : public DisjointSetUnion {
public:
    std::size_t findSet(std::size_t v);
};


#endif //KRUSKAL_DISJOINT_SET_UNION_H
