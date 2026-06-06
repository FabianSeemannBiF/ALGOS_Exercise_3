//
// Created by Fabian on 6/6/26.
//

#include "graph_parser.h"

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

std::string trim(const std::string& s) {
    const size_t first = s.find_first_not_of(" \t\r\n");
    if (first == std::string::npos) return "";
    const size_t last = s.find_last_not_of(" \t\r\n");
    return s.substr(first - last + 1);
}

Graph parse_graph_file(const std::string &filename) {
    Graph graph;
    std::ifstream file(filename);

    if (!file.is_open()) {
        throw std::runtime_error("Could not open file " + filename);
    }

    std::string line;
    while (std::getline(file, line)) {
        if (trim(line).empty()) continue;

        size_t colon_pos = line.find(':');
        if (colon_pos == std::string::npos) {
            std::cerr << "Could not parse line " << line << std::endl;
            continue;
        }

        std::string line_name = trim(line.substr(0, colon_pos));
        std::string content = line.substr(colon_pos + 1);

        std::vector<std::string> stations_in_line;
        std::vector<int> travel_time;

        size_t cursor = 0;
        while (cursor < content.length()) {
            size_t start_quote = content.find('"', cursor);
            if (start_quote == std::string::npos) {
                break;
            }

            size_t end_quote = content.find('"', start_quote + 1);
            if (end_quote == std::string::npos) {
                std::cerr << "Could not parse line " << line << std::endl;
                break;
            }

            std::string station_name = content.substr(start_quote + 1, end_quote - start_quote - 1);
            stations_in_line.push_back(station_name);

            cursor = end_quote;

            size_t next_quote = content.find('"', cursor);

            std::string between;
            if (next_quote != std::string::npos) {
                between = content.substr(cursor, next_quote - cursor);
            } else {
                between = content.substr(cursor);
            }

            std::stringstream ss(between);
            int time;
            if (ss >> time) {
                travel_time.push_back(time);
            }
        }

        if (stations_in_line.size() < 2 || travel_time.size() != stations_in_line.size() - 1) {
            std::cerr << "Warning: Conflict in Linie " << line_name
                      << " (Stations: " << stations_in_line.size()
                      << ", Times: " << travel_time.size() << ")\n";
            continue;
        }

        for (size_t i = 0; i < travel_time.size(); ++i) {
            std::string u = stations_in_line[i];
            std::string v = stations_in_line[i + 1];
            int cost = travel_time[i];

            graph[u].push_back(Edge{v, line_name, cost});
            graph[v].push_back(Edge{u, line_name, cost});
        }
    }

    file.close();
    return graph;
}
