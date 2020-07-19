#pragma once

#include "graph.hpp"

#include <stack>

namespace graphlib {

// Dijkstra's shortest (weighted) paths algorithm. If not given a destination,
// results in a complete shortest-paths tree encoded in each Vertex's parent
// member. If given a destination, terminates execution once destination is
// processed.
void dijkstra(Graph* graph, const Vertex* search_root,
              const Vertex* destination = nullptr);

// Repeatedly pop the stack returned by this function to obtain shortest
// weighted path.
std::stack<const Vertex*> shortest_weighted_path(Graph* graph,
                                                 const Vertex* search_root,
                                                 const Vertex* destination);

}  // namespace graphlib
