#include <iostream>
#include "../include/csv_writer.h"
#include "../include/utils.h"
#include "../include/kruskal_algorithm.h"
#include <chrono>

#define CHECK_SOLUTION

using namespace std::chrono;

void printEdges(const WeightedEdges &edges);

int main() {
    std::vector<std::string> test = {"vertices number", "edges number", "density", "time(ms) DSU", "time(ms) CP DSU"};

    CsvWriter csv_log("./", "results-" + utils::get_current_datetime_str() + ".csv", test);

    std::size_t n = 5, m = 8;
//    std::cout << "Enter vertices number:\t" << std::endl;
//    std::cin >> n;
//    std::cout << "Enter edges number:\t" << std::endl;
//    std::cin >> m;
//    std::cout << std::endl;
    Graph graph = graph_utils::generateConfusionMatrix(n, m);
    WeightedEdges edges = graph_utils::transformGraphToWeightedEdges(graph);

    printEdges(edges);

#ifdef CHECK_SOLUTION
    if (!graph_utils::isGraphConnected(graph.size(), edges)) {
        throw std::runtime_error("Generated graph isn't connected");
    }
#endif
    std::map<std::string, std::string> log;
    steady_clock::time_point begin = steady_clock::now();
    WeightedEdges spanning_tree = kruskal_algorithm::getMinimumSpanningTreeDSU(graph.size(), edges);
    auto execution_time = steady_clock::now() - begin;

    log["time(ms) DSU"] = std::to_string(duration_cast<milliseconds>(execution_time).count());

    std::cout << "Simple DSU result:\n";
    printEdges(spanning_tree);

#ifdef CHECK_SOLUTION
    if (!graph_utils::isGraphTree(graph.size(), spanning_tree)) {
        throw std::runtime_error("Found spanning tree is not tree!");
    }
#endif
    edges = graph_utils::transformGraphToWeightedEdges(graph);
    begin = steady_clock::now();
    spanning_tree = kruskal_algorithm::getMinimumSpanningTreeCPDSU(graph.size(), edges);
    execution_time = steady_clock::now() - begin;

    log["time(ms) CP DSU"] = std::to_string(duration_cast<milliseconds>(execution_time).count());

    std::cout << "CP DSU result:\n";
    printEdges(spanning_tree);

#ifdef CHECK_SOLUTION
    if (!graph_utils::isGraphTree(graph.size(), spanning_tree)) {
        throw std::runtime_error("Found spanning tree is not tree!");
    }
#endif

    log["edges number"] = std::to_string(m);
    log["vertices number"] = std::to_string(n);
    log["density"] = std::to_string(graph_utils::calculateDensity(n, m));

    csv_log.writeRow(log);
    return 0;
}

void printEdges(const WeightedEdges &edges) {
    for (auto e: edges) {
        std::cout << e.second.first << " " << e.second.second << " " << e.first << std::endl;
    }
    std::cout << std::endl;
}
