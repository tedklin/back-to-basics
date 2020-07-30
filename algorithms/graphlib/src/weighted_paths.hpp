#pragma once

#include "graph.hpp"

#include <stack>

namespace graphlib {

// Dijkstra's algorithm for single-source shortest non-negative weighted paths.
// If not given a destination, results in a complete shortest-paths tree encoded
// in each Vertex's parent member. If given a destination, terminates execution
// once destination is processed.
void dijkstra(Graph* graph, const Vertex* search_root,
              const Vertex* destination = nullptr);

// UNTESTED!
// A faster method for computing single-source shortest paths for edge-weighted
// DAGs, using a topological sort. If given a destination, terminates execution
// once destination is processed.
void dag_paths(Graph* graph, const Vertex* search_root,
               const Vertex* destination = nullptr);

// Queue-based Bellman-Ford algorithm for single-source shortest weighted paths
// in a graph without negative cycles.
void bellman_ford(Graph* graph, const Vertex* search_root);

// Repeatedly pop the stack returned by this function to obtain the respective
// path.
std::stack<const Vertex*> shortest_pos_weight_path(Graph* graph,
                                                   const Vertex* search_root,
                                                   const Vertex* destination);
std::stack<const Vertex*> shortest_weighted_path(Graph* graph,
                                                 const Vertex* search_root,
                                                 const Vertex* destination);

}  // namespace graphlib
