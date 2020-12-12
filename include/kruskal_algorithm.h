#ifndef KRUSKAL_ALGORITHM_H
#define KRUSKAL_ALGORITHM_H

#include "utils.h"

namespace kruskal_algorithm {
    WeightedEdges getMinimumSpanningTreeCPDSU(std::size_t n, WeightedEdges &all_edges);

    WeightedEdges getMinimumSpanningTreeDSU(std::size_t n, WeightedEdges &all_edges);
};

#endif //KRUSKAL_ALGORITHM_H
