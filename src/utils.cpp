#include "../include/utils.h"
#include "../include/disjoint_set_union.h"

Graph graph_utils::generateConfusionMatrix(std::size_t n, std::size_t m) {
    std::size_t max_e = n * (n - 1) / 2;
    std::size_t min_e = n - 1;

    if (m < min_e || m > max_e) {
        throw std::runtime_error("Unable to create graph with given parameters");
    }

    std::uniform_int_distribution<int> dist_distribution(1, 5);
    std::uniform_int_distribution<std::size_t> vertices_distribution(0, n - 1);
    std::random_device rd;
    std::mt19937 gen(rd());
    std::mt19937 gen2(rd());
    Graph g(n);

    for (std::size_t i = 0; i < n; ++i) {
        g[i].assign(n, NON_EXISTENT_EDGE);
        g[i][i] = NON_EXISTENT_EDGE;
    }

    std::vector<std::size_t> path(n, 0);
    std::iota(path.begin(), path.end(), 0);
    std::shuffle(path.begin(), path.end(), gen2);

    // generate minimum path between vertices
    for (std::size_t j = 1; j < n; ++j) {
        std::size_t i = j - 1;
        double dst = dist_distribution(gen);
        g[path[i]][path[j]] = dst;
        g[path[j]][path[i]] = dst;
    }

    for (std::size_t j = 0; j < m - min_e; ++j) {
        std::size_t a, b;
        while (true) {
            a = vertices_distribution(gen);
            b = vertices_distribution(gen);
            if ( a != b && (g[b][a] == NON_EXISTENT_EDGE || g[a][b] == NON_EXISTENT_EDGE)) {
                break;
            }
        }
        double dst = dist_distribution(gen);
        g[a][b] = dst;
        g[b][a] = dst;
    }
    return g;
}

WeightedEdges graph_utils::transformGraphToWeightedEdges(const Graph &graph) {
    WeightedEdges edges;
    for (std::size_t i = 0; i < graph.size(); ++i) {
        for (std::size_t j = i + 1; j < graph.size(); ++j) {
            if (graph[i][j] != NON_EXISTENT_EDGE) {
                edges.push_back({graph[i][j], {i, j}});
            }
        }
    }
    return edges;
}

bool graph_utils::isGraphConnected(std::size_t n, const WeightedEdges &edges) {
    DisjointSetUnionWithPathCompression sets(n);
    for (std::size_t i = 0; i < n; ++i) {
        sets.create(i);
    }

    for (const auto &edge: edges) {
        auto x = sets.findSet(edge.second.first);
        auto y = sets.findSet(edge.second.second);
        if (x != y) {
            sets.unionSets(x, y);
        }
    }
    return sets.getSize() == 1;
}

bool graph_utils::isThereCycle(std::vector<int> &used, const Graph &g, std::size_t v) {
    used[v] = 1;
    for (size_t i = v + 1; i < g[v].size(); ++i) {
        if (g[v][i] == NON_EXISTENT_EDGE) {
            continue;
        }
        int to = i;
        if (used[to] == 0) {
            if (isThereCycle(used, g, to)) return true;
        } else if (used[to] == 1) {
            return true;
        }
    }
    used[v] = 2;
    return false;
}

bool graph_utils::isGraphTree(std::size_t n, const WeightedEdges &edges) {
    if (edges.size() != n - 1) {
        return false;
    }
    Graph g(n);
    for (std::size_t i = 0; i < n; ++i) {
        g[i].assign(n, NON_EXISTENT_EDGE);
        g[i][i] = NON_EXISTENT_EDGE;
    }
    for (const auto &e: edges) {
        g[e.second.first][e.second.second] = e.first;
        g[e.second.second][e.second.first] = e.first;
    }

    std::vector<int> used(n, 0);
    return !isThereCycle(used, g, 0);
}

void sorting::quickSort(WeightedEdges &data, std::size_t left, std::size_t right) {
    if (left < right) {
        std::size_t p = split(data, left, right);
        quickSort(data, left, p - 1);
        quickSort(data, p, right);
    }
}

std::size_t sorting::split(WeightedEdges &data, std::size_t left, std::size_t right) {
    DistanceToEdge pivot = data[(left + right) / 2];
    int i = left, j = right;
    while (i <= j) {
        while (data[i].first < pivot.first) i++;
        while (data[j].first > pivot.first) j--;
        if (i <= j) {
            std::swap(data[i], data[j]);
            i++;
            j--;
        }
    }
    return i;
}

int graph_utils::calculateDensity(std::size_t n, std::size_t m) {
    return (2u * m) / (n * (n - 1));
}

std::string utils::get_current_datetime_str() {
    std::ostringstream oss;
    oss << std::time(nullptr);
    return oss.str();
}
