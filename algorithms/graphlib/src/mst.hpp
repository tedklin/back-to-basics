#pragma once

#include "graph.hpp"

#include <vector>

namespace graphlib {

// In the classical weighted Union-Find data structure, each set / connected
// component is represented by a tree, with the tree root "naming" the set. The
// underlying structure is composed of two maps, one of which maps each Vertex
// to its parent in its tree. If the Vertex is mapped to nullptr, then it
// represents its own set / connected component. The other map keeps track of
// the size of each tree, which helps keep trees balanced when they are merged.
class VertexUnionFind {
 public:
  VertexUnionFind(Graph* graph) {
    // Initially, each vertex is its own set.
    for (const auto& v : graph->vertex_set()) {
      parents_[graph->internal_vertex_ptr(v.first)] = nullptr;
      sizes_[graph->internal_vertex_ptr(v.first)] = 1;
    }
  }

  // Returns the name of the set of the given Vertex (i.e. the root of the given
  // Vertex's tree.)
  const Vertex* find(const Vertex* v) const {
    while (parents_.at(v)) {
      v = parents_.at(v);
    }
    return v;
  }

  bool connected(const Vertex* v1, const Vertex* v2) const {
    return find(v1) == find(v2);
  }

  void merge(const Vertex* v1, const Vertex* v2) {
    if (connected(v1, v2)) {
      return;
    }

    // Merge the smaller tree into the larger tree.
    const Vertex *set1 = find(v1), *set2 = find(v2);
    if (sizes_[set1] < sizes_[set2]) {
      parents_[set1] = set2;
      sizes_[set2] += sizes_[set1];
    } else {
      parents_[set2] = set1;
      sizes_[set1] += sizes_[set2];
    }
  }

 private:
  std::map<const Vertex*, const Vertex*> parents_;
  std::map<const Vertex*, int> sizes_;
};

// Prim's algorithm ("lazy" version in Sedgewick). Assumes given graph is
// connected.
std::vector<Edge> prim_mst(Graph* graph);

// Kruskal's algorithm.
std::vector<Edge> kruskal_mst(Graph* graph);

}  // namespace graphlib