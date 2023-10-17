#ifndef INC_1C_CITIES_H
#define INC_1C_CITIES_H

#include <algorithm>
#include <iostream>
#include <queue>
#include <string>
#include <unordered_map>
#include <vector>
#include "graph.h"

using std::cin;
using std::cout;
using std::pair;
using std::queue;
using std::string;
using std::unordered_map;
using std::vector;

class Cities {
public:
    Cities(vector<pair<size_t, size_t>> new_edges, size_t n);

    vector<size_t> infect();

    pair<int, unordered_map<size_t, size_t>> find_candidate_to_infect();

private:
    pair<size_t, unordered_map<size_t, size_t>> infect_bfs(size_t start);

    Graph graph;

    vector<bool> primarly_infected;
    vector<bool> infected;
    vector<size_t> infected_neighbours;
};

#endif  //INC_1C_CITIES_H
