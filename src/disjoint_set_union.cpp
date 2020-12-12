#include "../include/disjoint_set_union.h"

void DisjointSetUnion::create(std::size_t v) {
    parent[v] = v;
    rank[v] = 0;
}

std::size_t DisjointSetUnion::findSet(std::size_t v) {
    if (v == parent[v]) {
        return v;
    }
    if (parent[v] == 0) {
        return NON_EXISTENT_ELEMENT;
    }
    return findSet(parent[v]);
}

void DisjointSetUnion::unionSets(std::size_t x, std::size_t y) {
    if (x != y) {
        if (rank[x] > rank[y]) {
            parent[y] = x;
        } else if (rank[x] < rank[y]) {
            parent[x] = y;
        } else {
            parent[y] = x;
            rank[x]++;
        }
    }
}

std::size_t DisjointSetUnionWithPathCompression::findSet(std::size_t v) {
    if (v == parent[v]) {
        return v;
    }
    if (parent[v] == 0) {
        return NON_EXISTENT_ELEMENT;
    }
    return parent[v] = findSet(parent[v]);
}
