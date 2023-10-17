#include "cities.h"

Cities::Cities(vector<pair<size_t, size_t>> new_edges, size_t n)
    : graph(n), primarly_infected(n, false), infected(n, false), infected_neighbours(n, 0) {
    for (auto& edge : new_edges) {
        graph.add_edge(edge);
    }
}

vector<size_t> Cities::infect() {
    while (true) {
        auto [candidate, map] = std::move(find_candidate_to_infect());

        if (candidate == -1) {
            break;
        }

        primarly_infected[candidate] = true;
        infected[candidate] = true;

        for (auto [key, value] : map) {
            infected_neighbours[key] += value;
            if (infected_neighbours[key] >= 2) {
                infected[key] = true;
            }
        }
    }

    vector<size_t> result;

    for (auto i = 0; i < primarly_infected.size(); ++i) {
        if (primarly_infected[i]) {
            result.push_back(i);
        }
    }

    return std::move(result);
}

pair<int, unordered_map<size_t, size_t>> Cities::find_candidate_to_infect() {
    int candidate = -1;
    size_t best = 0;
    unordered_map<size_t, size_t> map_best;

    for (auto i = 0; i < graph.vertices_n(); ++i) {
        if (!infected[i]) {
            auto [score, map] = std::move(infect_bfs(i));

            if (score > best) {
                best = score;
                candidate = i;
                map_best = std::move(map);
            }
        }
    }

    return {candidate, std::move(map_best)};
}

pair<size_t, unordered_map<size_t, size_t>> Cities::infect_bfs(size_t start) {
    size_t new_infected = 0;

    unordered_map<size_t, size_t> new_infections;

    queue<size_t> q;
    q.push(start);

    while (!q.empty()) {
        auto v = q.front();
        q.pop();

        ++new_infected;

        for (size_t u : graph.edges[v]) {
            if (infected[u] || new_infections[u] + infected_neighbours[u] >= 2) {
                continue;
            }

            if (new_infections.contains(u)) {
                ++new_infections[u];
            } else {
                new_infections[u] = 1;
            }

            if (infected_neighbours[u] < 2 && new_infections[u] + infected_neighbours[u] == 2) {
                q.push(u);
            }
        }
    }

    return {new_infected, std::move(new_infections)};
}
