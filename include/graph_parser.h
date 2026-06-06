//
// Created by Fabian on 6/6/26.
//

#ifndef PROGRAMMIERBEISPIEL_3_GRAPH_PARSER_H
#define PROGRAMMIERBEISPIEL_3_GRAPH_PARSER_H
#include <string>
#include <unordered_map>
#include <vector>

struct Edge {
    std::string to_station;
    std::string line;
    int cost;
};

using Graph = std::unordered_map<std::string, std::vector<Edge>>;

Graph parse_graph_file(std::string& filename);

#endif //PROGRAMMIERBEISPIEL_3_GRAPH_PARSER_H
