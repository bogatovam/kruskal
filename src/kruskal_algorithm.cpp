#include "../include/kruskal_algorithm.h"
#include "../include/disjoint_set_union.h"

WeightedEdges kruskal_algorithm::getMinimumSpanningTreeCPDSU(std::size_t n, WeightedEdges &all_edges) {
    WeightedEdges result;

    sorting::quickSort(all_edges, 0, all_edges.size() - 1);

    DisjointSetUnionWithPathCompression sets(n);
    for (std::size_t i = 0; i < n; ++i) {
        sets.create(i);
    }

    for (const auto &edge: all_edges) {
        auto x = sets.findSet(edge.second.first);
        auto y = sets.findSet(edge.second.second);
        if (x != y) {
            sets.unionSets(x, y);
            result.push_back(edge);
        }
    }
    return result;
}

WeightedEdges kruskal_algorithm::getMinimumSpanningTreeDSU(std::size_t n, WeightedEdges &all_edges) {
    WeightedEdges result;

    sorting::quickSort(all_edges, 0, all_edges.size() - 1);

    DisjointSetUnion sets(n);
    for (std::size_t i = 0; i < n; ++i) {
        sets.create(i);
    }

    for (const auto &edge: all_edges) {
        auto x = sets.findSet(edge.second.first);
        auto y = sets.findSet(edge.second.second);
        if (x != y) {
            sets.unionSets(x, y);
            result.push_back(edge);
        }
    }
    return result;
}
