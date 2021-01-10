#pragma once

#include <map>
#include "kmint/graph/graph.hpp"
#include "kmint/map/map.hpp"
class Astar{
private:
    const int _start;
    const int _end;
    std::map<int, float> _weights;
    std::map<int, int> _came_from;
    std::vector<int> _visited;

    kmint::graph::basic_graph<kmint::map::map_node_info> &_graph;
public:
    Astar(kmint::graph::basic_graph<kmint::map::map_node_info> &graph, int start, int end);
    void search();
    float heuristic(int from_node, int to_node);
    std::vector<int> construct_path();
    void draw_path(const std::vector<int>& path);
};


