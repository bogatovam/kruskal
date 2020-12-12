#ifndef KRUSKAL_UTILS_H
#define KRUSKAL_UTILS_H

#include <vector>
#include <string>
#include <ctime>
#include <sstream>
#include <iomanip>
#include <algorithm>
#include <random>
#include <numeric>

typedef double Distance;

typedef std::vector<std::vector<Distance>> Graph;

typedef std::pair<Distance, std::pair<std::size_t, std::size_t>> DistanceToEdge;

typedef std::vector<DistanceToEdge> WeightedEdges;

namespace graph_utils {

    Graph generateConfusionMatrix(std::size_t n, std::size_t m);

    WeightedEdges transformGraphToWeightedEdges(const Graph &graph);

    bool isGraphConnected(std::size_t n, const WeightedEdges &edges);

    const static double NON_EXISTENT_EDGE = std::numeric_limits<Distance>::min();

    bool isGraphTree(std::size_t n, const WeightedEdges &edges);

    double calculateDensity(std::size_t n, std::size_t m);

    bool isThereCycle(std::vector<int> &used, const Graph &g, size_t v);

    std::size_t getEdgesCount(const size_t n, const double d);

    std::size_t getEdgesCount(const size_t n, const double d);
}

namespace sorting {
    void quickSort(WeightedEdges &data, std::size_t left, std::size_t right);

    std::size_t split(WeightedEdges &data, std::size_t left, std::size_t right);
}

namespace utils {
    std::string get_current_datetime_str();
}

#endif //KRUSKAL_UTILS_H
