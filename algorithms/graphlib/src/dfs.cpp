#include "dfs.hpp"

#include <iostream>

namespace graphlib {

std::map<const Vertex*, const Vertex*> dfs(
    Graph* graph, Vertex search_root,
    void (*process_vertex_early)(const Vertex* v),
    void (*process_edge)(const Vertex* v1, const Vertex* v2, double weight),
    void (*process_vertex_late)(const Vertex* v)) {
  // Ensure that we are referencing a Vertex within the given Graph.
  const Vertex* root_ptr;
  try {
    root_ptr = graph->ptr_to_vertex(search_root);
  } catch (std::runtime_error) {
    std::cerr << "Warning! Tried to perform DFS with a search root that's not "
                 "in the graph!\n\n";
    return std::map<const Vertex*, const Vertex*>();
  }

  // Start timer
  int time = 0;

  // Map from each Vertex to its "parent" in a search tree w.r.t. the root. In a
  // DFS, this encodes "tree" edges.
  std::map<const Vertex*, const Vertex*> parent;

  return parent;
}

}  // namespace graphlib
