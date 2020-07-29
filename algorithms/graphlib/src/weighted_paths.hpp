#pragma once

#include "graph.hpp"

#include <stack>

namespace graphlib {

// Dijkstra's single-source shortest non-negative weighted paths algorithm. If
// not given a destination, results in a complete shortest-paths tree encoded in
// each Vertex's parent member. If given a destination, terminates execution
// once destination is processed.
void dijkstra(Graph* graph, const Vertex* search_root,
              const Vertex* destination = nullptr);

// UNTESTED!
// A faster method for computing single-source shortest paths for edge-weighted
// DAGs using a topological sort.
void dag_paths(Graph* graph, const Vertex* search_root,
               const Vertex* destination = nullptr);

// Repeatedly pop the stack returned by this function to obtain shortest
// positive-weighted path.
std::stack<const Vertex*> shortest_pos_weight_path(Graph* graph,
                                                   const Vertex* search_root,
                                                   const Vertex* destination);

}  // namespace graphlib
