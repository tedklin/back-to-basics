// Dijkstra's algorithm uses a min-heap to keep track of the next non-tree
// Vertex closest to the search root. std::priority_queue doesn't work here
// because we need the ability to change the "value" (distance to search root)
// of a Vertex already in the heap and reheapify on the go. To support this
// functionality, we use std::make_heap, std::push_heap, and std::pop_heap on an
// underlying std::vector.

#include "weighted_paths.hpp"

#include <algorithm>
#include <iostream>
#include <limits>
#include <vector>

namespace graphlib {

// Maps each vertex to its currently-known shortest distance to the search
// root.
std::map<const Vertex*, double> g_dist_to_root;

// To emulate a min-heap in a vector, we need to define our own Compare type.
struct GreaterDist {
  bool operator()(const Vertex* lhs, const Vertex* rhs) const {
    return g_dist_to_root.at(lhs) > g_dist_to_root.at(rhs);
  }
};

void dijkstra(Graph* graph, const Vertex* search_root,
              const Vertex* destination) {
  g_dist_to_root.clear();
  for (const auto& v : graph->GetVertexSet()) {
    if (graph->GetInternalVertexPtr(v.first) == search_root) {
      g_dist_to_root[graph->GetInternalVertexPtr(v.first)] = 0;
    } else {
      g_dist_to_root[graph->GetInternalVertexPtr(v.first)] =
          std::numeric_limits<double>::infinity();
    }
  }

  // Min-heap keeps track of the next non-tree vertex closest to the source.
  std::vector<const Vertex*> min_heap;
  min_heap.push_back(search_root);

  while (!min_heap.empty()) {
    // Bubble the smallest element (top of min-heap) down to the end of the
    // vector, store it in v1, then pop it.
    std::pop_heap(min_heap.begin(), min_heap.end(), GreaterDist());
    const Vertex* v1 = min_heap.back();
    min_heap.pop_back();

    if (v1 == destination) return;

    for (auto& adj : graph->GetAdjacentSet(*v1)) {
      const Vertex* v2 = adj.first;
      double weight = adj.second;

      if (g_dist_to_root.at(v2) > g_dist_to_root.at(v1) + weight) {
        g_dist_to_root.at(v2) = g_dist_to_root.at(v1) + weight;
        v2->parent_ = v1;

        if (std::find(min_heap.begin(), min_heap.end(), v2) != min_heap.end()) {
          // If v2 is already in the min-heap, do a complete reheapify with
          // v2's updated "g_dist_to_root" value.
          std::make_heap(min_heap.begin(), min_heap.end(), GreaterDist());
        } else {
          // If v2 is not yet in the min-heap, push it to the back of the
          // vector, then bubble it up to its proper heap placement.
          min_heap.push_back(v2);
          std::push_heap(min_heap.begin(), min_heap.end(), GreaterDist());
        }
      }
    }
  }
}

// Analogous to shortest_unweighted_path in bfs.cpp
std::stack<const Vertex*> shortest_weighted_path(Graph* graph,
                                                 const Vertex* search_root,
                                                 const Vertex* destination) {
  dijkstra(graph, search_root, destination);
  const Vertex* v = destination;
  std::stack<const Vertex*> s;
  s.push(v);

  while (v != search_root) {
    if (v) {
      v = v->parent_;
      s.push(v);
    } else {
      std::cerr << "No path between " << search_root->name_ << " and "
                << destination->name_ << "\n\n";
      return std::stack<const Vertex*>();
    }
  }
  return s;
}

}  // namespace graphlib