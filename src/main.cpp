//
// Created by Fabian on 6/6/26.
//

#include <iostream>
#include <ostream>

#include "dijkstra.h"
#include "graph_parser.h"

int main(const int argc, const char* argv[]) {
    if (argc != 4) {
        std::cerr << "Usage: " << argv[0] << " <graph_file> <start> <end>" << std::endl;
        return 1;
    }

    std::string filename = argv[1];
    const std::string start_station = argv[2];
    const std::string end_station = argv[3];

    try {
        Graph graph = parse_graph_file(filename);

        find_and_print_shortest_path(graph, start_station, end_station);
    } catch (std::exception& e) {
        std::cerr << "An error has occurred: " << e.what() << std::endl;
        return 1;
    }
    return 0;
}
