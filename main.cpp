#include <algorithm>
#include <iostream>
#include <queue>
#include <string>
#include <unordered_map>
#include <vector>

using std::cin;
using std::cout;
using std::pair;
using std::queue;
using std::string;
using std::unordered_map;
using std::vector;

class Cities {
public:
    Cities(vector<pair<size_t, size_t>> new_edges, size_t n)
        : edges(n), primarly_infected(n, false), infected(n, false), infected_neighbours(n, 0) {
        for (auto& edge : new_edges) {
            edges[edge.first].push_back(edge.second);
            edges[edge.second].push_back(edge.first);
        }
    }

    void add_edge(size_t from, size_t to) {
        edges[from].push_back(to);
        edges[to].push_back(from);
    }

    vector<size_t> infect() {
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

    pair<int, unordered_map<size_t, size_t>> find_candidate_to_infect() {
        int candidate = -1;
        size_t best = 0;
        unordered_map<size_t, size_t> map_best;

        for (auto i = 0; i < edges.size(); ++i) {
            if (!infected[i]) {
                auto [score, map] = std::move(bfs(i));

                if (score > best) {
                    best = score;
                    candidate = i;
                    map_best = std::move(map);
                }
            }
        }

        return {candidate, std::move(map_best)};
    }

    vector<vector<size_t>>& get_edges() { return edges; }

private:
    pair<size_t, unordered_map<size_t, size_t>> bfs(size_t start) {
        size_t new_infected = 0;

        unordered_map<size_t, size_t> new_infections;

        queue<size_t> q;
        q.push(start);

        while (!q.empty()) {
            auto v = q.front();
            q.pop();

            ++new_infected;

            for (size_t u : edges[v]) {
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

    vector<vector<size_t>> edges;

    vector<bool> primarly_infected;
    vector<bool> infected;
    vector<size_t> infected_neighbours;
};

Cities input() {}

int main() {
    //    auto graph = input();

    std::unordered_map<string, size_t> string_int;
    std::unordered_map<size_t, string> int_string;

    int m;
    cin >> m;

    size_t counter = 0;

    vector<pair<size_t, size_t>> edges;

    for (auto i = 0; i < m; ++i) {
        string from;
        string to;

        cin >> from >> to;

        if (!string_int.contains(from)) {
            string_int[from] = counter;
            int_string[counter++] = from;
        }

        if (!string_int.contains(to)) {
            string_int[to] = counter;
            int_string[counter++] = to;
        }

        edges.emplace_back(string_int[from], string_int[to]);
    }

    Cities cities(std::move(edges), counter);

    auto res = cities.infect();

    cout << res.size() << "\n";
    for (auto i : res) {
        cout << int_string[i] << " ";
    }
    cout << "\n";
    return 0;
}