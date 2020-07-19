// Dijkstra's algorithm uses a min-heap to keep track of the next non-tree
// vertex closest to the source. However, an std::priority_queue doesn't work
// because we need the ability to change the comparator value (distance to
// search root) of an existing key and reheapify on the go. To support this
// ability efficiently, we use std::make_heap, push_heap, pop_heap backed by an
// std::vector.

#include "weighted_paths.hpp"

#include <algorithm>
#include <iostream>
#include <limits>
#include <vector>

namespace graphlib {

// Maps each vertex to its currently known shortest distance to the search
// root.
std::map<const Vertex*, double> g_dist_to_root;

// To create a custom min-heap, we need to define our own Compare type.
struct GreaterDist {
  bool operator()(const Vertex* lhs, const Vertex* rhs) const {
    return g_dist_to_root.at(lhs) > g_dist_to_root.at(rhs);
  }
};

void dijkstra(Graph* graph, const Vertex* search_root,
              const Vertex* destination = nullptr) {
  g_dist_to_root.clear();
  for (const auto& v : graph->vertex_set()) {
    if (graph->internal_vertex_ptr(v.first) == search_root) {
      g_dist_to_root[graph->internal_vertex_ptr(v.first)] = 0;
    } else {
      g_dist_to_root[graph->internal_vertex_ptr(v.first)] =
          std::numeric_limits<double>::infinity();
    }
  }

  // Min-heap keeps track of the next non-tree vertex closest to the source.
  std::vector<const Vertex*> min_heap;
  min_heap.push_back(search_root);

  while (!min_heap.empty()) {
    // Move the next smallest element (top of min-heap) to the end of the
    // vector, then store it, then pop it.
    std::pop_heap(min_heap.begin(), min_heap.end(), GreaterDist());
    const Vertex* v1 = min_heap.back();
    min_heap.pop_back();

    for (auto& e : graph->adjacent_set(*v1)) {
      const Vertex* v2 = e.first;
      double weight = e.second;

      if (g_dist_to_root.at(v2) > g_dist_to_root.at(v1) + weight) {
        g_dist_to_root.at(v2) = g_dist_to_root.at(v1) + weight;
        v2->parent_ = v1;

        if (std::find(min_heap.begin(), min_heap.end(), v2) != min_heap.end()) {
          // If v2 is already in the min-heap, completely reheapify with v2's
          // changed g_dist_to_root value.
          std::make_heap(min_heap.begin(), min_heap.end(), GreaterDist());
        } else {
          // If v2 is not yet in the min-heap, push it to the back, then bubble
          // it up to its proper place on the heap.
          min_heap.push_back(v2);
          std::push_heap(min_heap.begin(), min_heap.end(), GreaterDist());
        }
      }
    }
  }

  // The shortest-paths-tree should now be encoded in each Vertex's parent
  // member.
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