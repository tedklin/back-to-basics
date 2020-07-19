#pragma once

#include "graph.hpp"

#include <stack>

namespace graphlib {

void dijkstra(Graph* graph, const Vertex* search_root,
              const Vertex* destination = nullptr);

std::stack<const Vertex*> shortest_weighted_path(Graph* graph,
                                                 const Vertex* search_root,
                                                 const Vertex* destination);

}  // namespace graphlib
