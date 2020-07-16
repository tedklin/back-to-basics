#include "dfs.hpp"

#include <iostream>
#include <stack>

namespace graphlib {

std::map<const Vertex*, const Vertex*> dfs(
    Graph* graph, const Vertex* search_root,
    void (*process_vertex_early)(const Vertex* v),
    void (*process_edge)(const Vertex* v1, const Vertex* v2, double weight),
    void (*process_vertex_late)(const Vertex* v)) {
  // Time intervals can give us valuable information about the structure of the
  // DFS search tree (Skiena).
  int time = 0;

  // Map from each Vertex to its "parent" in a search tree w.r.t. the root. In a
  // DFS, this encodes "tree" edges.
  std::map<const Vertex*, const Vertex*> parent;

  // Start DFS.
  std::stack<const Vertex*> s;
  s.push(search_root);

  while (!s.empty()) {
    const Vertex* v1 = s.top();
    s.pop();

    v1->state_ = Vertex::State::DISCOVERED;
    v1->entry_time = time;
    if (process_vertex_early) {
      process_vertex_early(v1);
    }

    for (auto adj : graph->adjacent_set(*v1)) {
      const Vertex* v2 = adj.first;
      double weight = adj.second;
      if (v2->state_ == Vertex::State::UNDISCOVERED) {
        // tree edge
        parent[v2] = v1;
        process_edge(v1, v2, weight);
        s.push(v2);
      } else if ((v2->state_ != Vertex::State::PROCESSED) ||
                 graph->is_directed()) {
        // back edge
        process_edge(v1, v2, weight);
      }
    }

    if (process_vertex_late) {
      process_vertex_late(v1);
    }
    ++time;
    v1->exit_time = time;
    v1->state_ = Vertex::State::PROCESSED;
  }

  return parent;
}

}  // namespace graphlib
