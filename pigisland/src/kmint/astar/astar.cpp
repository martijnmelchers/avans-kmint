#include <queue>
#include "astar.hpp"
#include "kmint/graph/basic_node.hpp"
#include <map>
#include <vector>
#include "kmint/graph/graph.hpp"
#include "kmint/graph/basic_graph.hpp"

typedef std::pair<int, float> pair;


struct comparison {
    constexpr bool operator()(pair a, pair b) const noexcept {
        return a.second > b.second;
    }
};

Astar::Astar(kmint::graph::basic_graph<kmint::map::map_node_info> &graph, const int start, const int end) : _start(
        start), _end(end), _graph(graph) {}


void Astar::search() {
    std::priority_queue<pair, std::vector<pair>, comparison> priorityQueue;

    priorityQueue.push(std::make_pair(_start, 0));

    _came_from[_start] = _start;
    _weights[_start] = 0;

    while (!priorityQueue.empty()) {
        const int current = priorityQueue.top().first;
        priorityQueue.pop();

        auto &node = _graph[current];

        if (current == _end) {
            break;
        }

        //Tag the current node as visited.
        for (auto &edge : node) {
            float cost = _weights[current] + edge.weight();
            int next_node_id = edge.to().node_id();

            _graph[next_node_id].tag(kmint::graph::node_tag::visited);

            if (_weights.find(next_node_id) == _weights.end() || cost < _weights[next_node_id]) {
                _weights[next_node_id] = cost;


                float h = (heuristic(next_node_id, _end) / 16);
                double priority = cost + h;

                priorityQueue.push(std::make_pair(next_node_id, priority));

                _came_from[next_node_id] = current;
            }
        }
    }
}

float Astar::heuristic(const int from_node, const int to_node) {
    auto &a = _graph[from_node];
    auto &b = _graph[to_node];
    return std::abs(a.location().x() - b.location().x()) +
           std::abs(a.location().y() - b.location().y()); //Copyright Sascha Mendel (2021)
}

std::vector<int> Astar::construct_path() {
    auto current = _end;
    std::queue<int> items;
    std::vector<int> path;

    while (current != _start) {
        path.push_back(current);

        // Tag current path as actual path.
        _graph[current].tag(kmint::graph::node_tag::path);

        current = _came_from[current];
    }

    path.push_back(_start); // optional

    return path;
}

