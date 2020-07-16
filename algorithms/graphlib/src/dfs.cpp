#include "dfs.hpp"

#include <iostream>
#include <stack>

namespace graphlib {

// Time intervals can give us valuable information about the structure of the
// DFS search tree (see Skiena).
int g_time = 0;

// Allow for early search termination.
bool g_finished = false;

// Cycle detection.
bool g_cyclic = false;

// Topological sort helper stack.
std::stack<const Vertex*> g_topstack;

// In a recursive DFS scheme, a helper is necessary because it's otherwise
// impossible to reset the global timer.
void dfs_helper(Graph* graph, const Vertex* v1,
                void (*process_vertex_early)(const Vertex* v),
                void (*process_edge)(const Vertex* v1, const Vertex* v2,
                                     double weight),
                void (*process_vertex_late)(const Vertex* v)) {
  if (g_finished) return;

  v1->state_ = Vertex::State::DISCOVERED;
  v1->entry_time_ = ++g_time;
  if (process_vertex_early) {
    process_vertex_early(v1);
  }

  for (auto adj : graph->adjacent_set(*v1)) {
    const Vertex* v2 = adj.first;
    double weight = adj.second;

    if (v2->state_ == Vertex::State::UNDISCOVERED) {
      // Tree edge
      v2->parent_ = v1;
      process_edge(v1, v2, weight);
      dfs_helper(graph, v2, process_vertex_early, process_edge,
                 process_vertex_late);
    } else if ((v2->state_ == Vertex::State::DISCOVERED && v1->parent_ != v2) ||
               graph->is_directed()) {
      // Back edge if undirected.
      // Back, forward, or cross edge if directed.
      // Also avoids duplicate (reverse adjacent) edges if undirected.
      process_edge(v1, v2, weight);
    }

    if (g_finished) return;
  }

  if (process_vertex_late) {
    process_vertex_late(v1);
  }
  v1->exit_time_ = ++g_time;
  v1->state_ = Vertex::State::PROCESSED;
}

void dfs(Graph* graph, const Vertex* search_root,
         void (*process_vertex_early)(const Vertex* v),
         void (*process_edge)(const Vertex* v1, const Vertex* v2,
                              double weight),
         void (*process_vertex_late)(const Vertex* v)) {
  g_time = 0;
  g_finished = false;
  g_cyclic = false;

  // Start DFS.
  dfs_helper(graph, search_root, process_vertex_early, process_edge,
             process_vertex_late);
}

void dfs_graph(Graph* graph, void (*process_vertex_early)(const Vertex* v),
               void (*process_edge)(const Vertex* v1, const Vertex* v2,
                                    double weight),
               void (*process_vertex_late)(const Vertex* v)) {
  g_time = 0;
  g_finished = false;
  g_cyclic = false;

  for (auto x : graph->vertex_set()) {
    const Vertex* v = graph->internal_vertex_ptr(x.first);
    if (v->state_ == Vertex::State::UNDISCOVERED) {
      dfs_helper(graph, v, process_vertex_early, process_edge,
                 process_vertex_late);
    }
  }
}

EdgeType classify_edge(const Vertex* v1, const Vertex* v2) {
  // Note that undirected graphs can only have tree or back edges.
  if (v2->parent_ == v1) return EdgeType::TREE;
  if (v2->state_ == Vertex::State::DISCOVERED) return EdgeType::BACK;

  // Additional possible edge types for directed graphs.
  if (v2->state_ == Vertex::State::PROCESSED &&
      v2->entry_time_ > v1->entry_time_) {
    return EdgeType::FORWARD;
  }
  if (v2->state_ == Vertex::State::PROCESSED &&
      v2->entry_time_ < v1->entry_time_) {
    return EdgeType::CROSS;
  }

  std::cerr << "Warning: unclassified edge " << v1->name_ << " -> " << v2->name_
            << "!\n\n";
  return EdgeType::UNCLASSIFIED;
}

bool is_cyclic(Graph* graph) {
  for (auto x : graph->vertex_set()) {
    const Vertex* v = graph->internal_vertex_ptr(x.first);
    if (v->state_ == Vertex::State::UNDISCOVERED) {
      dfs(graph, v, nullptr,
          [](const Vertex* v1, const Vertex* v2, double weight) {
            if (v2->state_ == Vertex::State::DISCOVERED && v1->parent_ != v2) {
              // Found back edge, forming a cycle.
              g_cyclic = true;
              g_finished = true;
            }
          });
    }
    if (g_cyclic) break;
  }
  return g_cyclic;
}

std::stack<const Vertex*> topological_sort(Graph* graph) {
  // Clear global stack.
  while (!g_topstack.empty()) {
    g_topstack.pop();
  }

  dfs_graph(graph, nullptr,
            [](const Vertex* v1, const Vertex* v2, double weight) {
              if (classify_edge(v1, v2) == EdgeType::BACK) {
                std::cerr << "Warning: tried to perform topological sort on a "
                             "non-DAG!\n\n";
              }
            },
            [](const Vertex* v) { g_topstack.push(v); });
  return g_topstack;
}

}  // namespace graphlib
