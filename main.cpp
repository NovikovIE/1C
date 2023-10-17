#include <iostream>
#include <queue>
#include <string>
#include <unordered_map>
#include <vector>
#include "cities.h"
#include "graph.h"

using std::cin;
using std::cout;
using std::pair;
using std::queue;
using std::string;
using std::unordered_map;
using std::vector;

pair<vector<pair<size_t, size_t>>, size_t> get_input(std::unordered_map<string, size_t>& str_int,
                                                     std::unordered_map<size_t, string>& int_str) {
    int m;
    cin >> m;

    size_t counter = 0;

    vector<pair<size_t, size_t>> edges;

    for (auto i = 0; i < m; ++i) {
        string from;
        string to;

        cin >> from >> to;

        if (!str_int.contains(from)) {
            str_int[from] = counter;
            int_str[counter++] = from;
        }

        if (!str_int.contains(to)) {
            str_int[to] = counter;
            int_str[counter++] = to;
        }

        edges.emplace_back(str_int[from], str_int[to]);
    }

    return {std::move(edges), counter};
}

vector<size_t> get_infected_cities(vector<pair<size_t, size_t>>& edges, size_t cities_n) {
    Cities cities(std::move(edges), cities_n);
    auto infected_cities = std::move(cities.infect());
    return std::move(infected_cities);
}

void print_infected_cities(vector<size_t>& cities, std::unordered_map<size_t, string>& int_str) {
    cout << cities.size() << "\n";
    for (auto i : cities) {
        cout << int_str[i] << " ";
    }
    cout << "\n";
}

void test1() {
    auto counter = 3;
    // triangle
    vector<pair<size_t, size_t>> edges = {{0, 1}, {1, 2}, {0, 2}};

    auto cities = std::move(get_infected_cities(edges, counter));

    if (cities.size() == 2) {
        cout << "TEST1 PASSED\n";
    } else {
        cout << "TEST1 FAILED\n";
    }
}

void test2() {
    auto counter = 5;
    // circle
    vector<pair<size_t, size_t>> edges = {{0, 1}, {1, 2}, {2, 3}, {3, 4}, {4, 0}};

    auto cities = std::move(get_infected_cities(edges, counter));

    if (cities.size() == 3) {
        cout << "TEST2 PASSED\n";
    } else {
        cout << "TEST2 FAILED\n";
    }
}

void test3() {
    auto counter = 5;
    // clique
    vector<pair<size_t, size_t>> edges = {{0, 1}, {0, 2}, {0, 3}, {0, 4}, {1, 2},
                                          {1, 3}, {1, 4}, {2, 3}, {2, 4}, {3, 4}};

    auto cities = std::move(get_infected_cities(edges, counter));

    if (cities.size() == 2) {
        cout << "TEST3 PASSED\n";
    } else {
        cout << "TEST3 FAILED\n";
    }
}

void in_out_solve() {
    std::unordered_map<string, size_t> string_int;
    std::unordered_map<size_t, string> int_string;

    auto [edges, counter] = std::move(get_input(string_int, int_string));
    auto cities = std::move(get_infected_cities(edges, counter));
    print_infected_cities(cities, int_string);
}

int main() {

    test1();
    test2();
    test3();

    return 0;
}