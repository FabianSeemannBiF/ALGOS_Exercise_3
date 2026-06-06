//
// Created by Fabian on 6/6/26.
//
#include "../include/dijkstra.h"
#include <iostream>
#include <queue>
#include <unordered_map>
#include <vector>
#include <algorithm>
#include <limits>

constexpr int INF = std::numeric_limits<int>::max();

struct QueueElement {
    int current_cost;
    std::string station_name;

    bool operator>(const QueueElement& other) const {
        return current_cost > other.current_cost;
    }
};

struct ParentInfo {
    std::string parent_station;
    std::string line_used;
};

void find_and_print_shortest_path(const Graph& graph, const std::string& start, const std::string& end) {
    if (graph.find(start) == graph.end()) {
        std::cerr << "Error: Start Station '" << start << "' does not exist.\n";
        return;
    }
    if (graph.find(end) == graph.end()) {
        std::cerr << "Error: Destination '" << end << "' Does not exist.\n";
        return;
    }

    std::unordered_map<std::string, int> distances;
    std::unordered_map<std::string, ParentInfo> parents;

    for (const auto& pair : graph) {
        distances[pair.first] = INF;
    }

    distances[start] = 0;

    std::priority_queue<QueueElement, std::vector<QueueElement>, std::greater<>> pq;
    pq.push(QueueElement{0, start});

    bool reached_destination = false;

    while (!pq.empty()) {
        QueueElement current = pq.top();
        pq.pop();

        std::string u = current.station_name;
        int u_cost = current.current_cost;

        if (u == end) {
            reached_destination = true;
            break;
        }

        if (u_cost > distances[u]) {
            continue;
        }

        if (graph.find(u) == graph.end()) continue;

        for (const Edge& edge : graph.at(u)) {
            std::string v = edge.to_station;
            int weight = edge.cost;
            std::string line = edge.line;

            if (distances[u] + weight < distances[v]) {
                distances[v] = distances[u] + weight;
                parents[v] = ParentInfo{u, line};
                pq.push(QueueElement{distances[v], v});
            }
        }
    }

    if (!reached_destination || distances[end] == INF) {
        std::cout << "No line from '" << start << "' to '" << end << "' found.\n";
        return;
    }

    std::vector<std::string> path_stations;
    std::vector<ParentInfo> path_edges;

    std::string curr = end;
    while (curr != start) {
        path_stations.push_back(curr);
        ParentInfo info = parents[curr];
        path_edges.push_back(info);
        curr = info.parent_station;
    }
    path_stations.push_back(start);

    std::reverse(path_stations.begin(), path_stations.end());
    std::reverse(path_edges.begin(), path_edges.end());

    std::cout << "==================================================\n";
    std::cout << " ROUTE FROM: " << start << "\n";
    std::cout << " TO:      " << end << "\n";
    std::cout << "==================================================\n\n";

    std::cout << "Start bei Station: " << start << "\n";

    std::string current_line;

    for (size_t i = 0; i < path_edges.size(); ++i) {
        const std::string& next_station = path_stations[i + 1];
        std::string edge_line = path_edges[i].line_used;

        if (!current_line.empty() && current_line != edge_line) {
            std::cout << "  [!!] Change to line " << edge_line << "\n";
        }

        current_line = edge_line;
        std::cout << "  -> Drive with " << current_line << " to: " << next_station << "\n";
    }

    std::cout << "\n==================================================\n";
    std::cout << " Overall Time: " << distances[end] << " minutes\n";
    std::cout << "==================================================\n";
}