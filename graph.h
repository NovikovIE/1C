#ifndef INC_1C_GRAPH_H
#define INC_1C_GRAPH_H

#include <vector>
#include <cstdint>

using std::vector;
using std::pair;

struct Graph {
    explicit Graph(size_t vertices_n) : edges(vertices_n) {}

    vector<vector<size_t>> edges;

    void add_edge(pair<size_t, size_t> edge) {
        edges[edge.first].push_back(edge.second);
        edges[edge.second].push_back(edge.first);
    }

    [[nodiscard]] size_t vertices_n() const { return edges.size(); }
};



#endif  //INC_1C_GRAPH_H
