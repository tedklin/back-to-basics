#include "dfs.hpp"

#include <iostream>
#include <stack>

namespace graphlib {

int _time = 0;
bool _finished = false;

// In a recursive DFS scheme, this is necessary because it's otherwise
// impossible to reset the global timer.
void dfs_helper(Graph* graph, const Vertex* v1,
                void (*process_vertex_early)(const Vertex* v),
                void (*process_edge)(const Vertex* v1, const Vertex* v2,
                                     double weight),
                void (*process_vertex_late)(const Vertex* v)) {
  if (_finished) {
    return;
  }

  v1->state_ = Vertex::State::DISCOVERED;
  v1->entry_time_ = ++_time;
  if (process_vertex_early) {
    process_vertex_early(v1);
  }

  for (auto adj : graph->adjacent_set(*v1)) {
    const Vertex* v2 = adj.first;
    double weight = adj.second;

    if (v2->state_ == Vertex::State::UNDISCOVERED) {
      // tree edge
      v2->parent_ = v1;
      process_edge(v1, v2, weight);
      dfs_helper(graph, v2, process_vertex_early, process_edge,
                 process_vertex_late);
    } else if (v2->state_ == Vertex::State::DISCOVERED ||
               graph->is_directed()) {
      // back edge
      process_edge(v1, v2, weight);
    }

    if (_finished) {
      return;
    }
  }

  if (process_vertex_late) {
    process_vertex_late(v1);
  }
  v1->exit_time_ = ++_time;
  v1->state_ = Vertex::State::PROCESSED;
}

void dfs(Graph* graph, const Vertex* search_root,
         void (*process_vertex_early)(const Vertex* v),
         void (*process_edge)(const Vertex* v1, const Vertex* v2,
                              double weight),
         void (*process_vertex_late)(const Vertex* v)) {
  // Time intervals can give us valuable information about the structure of the
  // DFS search tree (Skiena).
  _time = 0;

  // Allow for early search termination.
  _finished = false;

  // Start DFS.
  dfs_helper(graph, search_root, process_vertex_early, process_edge,
             process_vertex_late);
}

}  // namespace graphlib
