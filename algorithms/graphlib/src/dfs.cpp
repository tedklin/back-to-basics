#include "dfs.hpp"

#include <iostream>
#include <stack>

namespace graphlib {

// Global helper variables to circumvent inability to pass capturing lambdas as
// function pointers. Remember to clear / reset value before and after each use.

// Time intervals can give us valuable information about the structure of the
// DFS search tree (see Skiena).
int g_time = 0;

// Allow for early search termination.
bool g_finished = false;

// Cycle detection.
bool g_cyclic = false;

// Topological sort helper stack.
std::stack<const Vertex*> g_top_stack;

// Articulation vertex / cut node detection.
std::set<const Vertex*> g_artic_vertices;

// Strong component helpers.
std::vector<std::set<const Vertex*>> g_components;
std::set<const Vertex*> g_component;

// In this recursive DFS scheme, a helper is necessary because it's otherwise
// impossible to reset the global variables.
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

  for (auto& adj : graph->adjacent_set(*v1)) {
    const Vertex* v2 = adj.first;
    double weight = adj.second;

    if (v2->state_ == Vertex::State::UNDISCOVERED) {
      // Tree edge.
      v2->parent_ = v1;
      process_edge(v1, v2, weight);
      dfs_helper(graph, v2, process_vertex_early, process_edge,
                 process_vertex_late);
    } else if ((v2->state_ == Vertex::State::DISCOVERED && v1->parent_ != v2) ||
               graph->is_directed()) {
      // Back edge if undirected.
      // Back, forward, or cross edge if directed.
      // Avoids duplicate (reverse adjacent) edges if undirected.
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

  dfs_helper(graph, search_root, process_vertex_early, process_edge,
             process_vertex_late);
}

void dfs_graph(Graph* graph, void (*process_vertex_early)(const Vertex* v),
               void (*process_edge)(const Vertex* v1, const Vertex* v2,
                                    double weight),
               void (*process_vertex_late)(const Vertex* v)) {
  g_time = 0;
  g_finished = false;

  for (auto& x : graph->vertex_set()) {
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
  g_cyclic = false;

  for (auto& x : graph->vertex_set()) {
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

std::stack<const Vertex*>& topological_sort(Graph* graph) {
  while (!g_top_stack.empty()) {
    g_top_stack.pop();
  }

  dfs_graph(graph, nullptr,
            [](const Vertex* v1, const Vertex* v2, double weight) {
              if (classify_edge(v1, v2) == EdgeType::BACK) {
                std::cerr << "Warning: tried to perform topological sort on a "
                             "non-DAG!\n\n";
              }
            },
            [](const Vertex* v) { g_top_stack.push(v); });

  return g_top_stack;
}

// TODO: test
std::set<const Vertex*>& articulation_vertices(Graph* graph) {
  g_artic_vertices.clear();

  dfs_graph(
      graph, nullptr,
      [](const Vertex* v1, const Vertex* v2, double weight) {
        if (classify_edge(v1, v2) == EdgeType::TREE) {
          ++(v1->tree_out_degree_);
        } else if (classify_edge(v1, v2) == EdgeType::BACK &&
                   v1->parent_ != v2) {
          if (v2->entry_time_ < v1->reachable_ancestor_->entry_time_) {
            v1->reachable_ancestor_ = v2;
          }
        }
      },
      [](const Vertex* v) {
        // If v is the search tree root vertex
        if (!(v->parent_)) {
          if (v->tree_out_degree_ > 1) {
            std::cout << "Root articulation vertex found: " << v->name_ << '\n';
            g_artic_vertices.insert(v);
          }
          return;
        }

        // If v's search tree parent is not the root vertex
        if (!(v->parent_->parent_)) {
          if (v->reachable_ancestor_ == v->parent_) {
            std::cout << "Parent articulation vertex found: " << v->name_
                      << '\n';
            g_artic_vertices.insert(v);
          }
          if (v->reachable_ancestor_ == v) {
            std::cout << "Bridge articulation vertex found: "
                      << v->parent_->name_ << '\n';
            g_artic_vertices.insert(v->parent_);

            // If v is not a leaf
            if (v->tree_out_degree_ > 0) {
              std::cout << "Bridge articulation vertex found: " << v->name_
                        << '\n';
              g_artic_vertices.insert(v);
            }
          }
        }

        // A Vertex's earliest reachable ancestor is also its search tree
        // child's earliest reachable ancestor.
        if (v->reachable_ancestor_->entry_time_ <
            v->parent_->reachable_ancestor_->entry_time_) {
          v->parent_->reachable_ancestor_ = v->reachable_ancestor_;
        }
      });

  return g_artic_vertices;
}

// TODO: test
bool is_biconnected(Graph* graph) {
  articulation_vertices(graph);
  return g_artic_vertices.empty();
}

// TODO: test
std::vector<std::set<const Vertex*>>& strong_components(Graph* graph) {
  g_components.clear();
  g_component.clear();

  dfs_graph(
      graph, [](const Vertex* v) { g_component.insert(v); },
      [](const Vertex* v1, const Vertex* v2, double weight) {
        if (classify_edge(v1, v2) == EdgeType::BACK &&
            v2->entry_time_ < v1->low_->entry_time_) {
          v1->low_ = v2;
        }
        if (classify_edge(v1, v2) == EdgeType::CROSS) {
          bool component_unassigned;
          for (std::set<const Vertex*> component : g_components) {
            component_unassigned = (component.find(v2) == component.end());
          }
          if (component_unassigned && v2->entry_time_ < v1->low_->entry_time_) {
            v1->low_ = v2;
          }
        }
      },
      [](const Vertex* v) {
        if (v->low_ == v) {
          g_components.push_back(g_component);
          g_component.clear();
        }
        if (v->low_->entry_time_ < v->parent_->low_->entry_time_) {
          v->parent_->low_ = v->low_;
        }
      });

  return g_components;
}

}  // namespace graphlib
