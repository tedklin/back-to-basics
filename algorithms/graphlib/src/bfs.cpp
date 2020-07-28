#include "bfs.hpp"

#include <iostream>
#include <queue>

namespace graphlib {

// Global helper variables to circumvent inability to pass capturing lambdas as
// function pointers. Remember to clear / reset value before and after each use.
std::set<Vertex> g_component;
bool g_is_bipartite = true;

void bfs(Graph* graph, const Vertex* search_root,
         void (*process_vertex_early)(const Vertex* v),
         void (*process_edge)(const Vertex* v1, const Vertex* v2,
                              double weight),
         void (*process_vertex_late)(const Vertex* v)) {
  std::queue<const Vertex*> q;
  q.push(search_root);

  while (!q.empty()) {
    const Vertex* v1 = q.front();
    q.pop();

    v1->state_ = Vertex::State::DISCOVERED;
    if (process_vertex_early) {
      process_vertex_early(v1);
    }

    for (auto& adj : graph->GetAdjacentSet(*v1)) {
      const Vertex* v2 = &(*(adj.first));
      double weight = adj.second;
      if (process_edge) {
        process_edge(v1, v2, weight);
      }
      if (v2->state_ == Vertex::State::UNDISCOVERED) {
        v2->state_ = Vertex::State::DISCOVERED;
        v2->parent_ = v1;
        q.push(v2);
      }
    }

    if (process_vertex_late) {
      process_vertex_late(v1);
    }
    v1->state_ = Vertex::State::PROCESSED;
  }
}

std::stack<const Vertex*> shortest_unweighted_path(Graph* graph,
                                                   const Vertex* search_root,
                                                   const Vertex* destination) {
  bfs(graph, search_root);
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

std::vector<std::set<Vertex>> connected_components(Graph* graph) {
  g_component.clear();

  std::vector<std::set<Vertex>> components;
  for (auto& x : graph->GetVertexSet()) {
    const Vertex* v = graph->GetInternalVertexPtr(x.first);
    if (v->state_ == Vertex::State::UNDISCOVERED) {
      bfs(graph, v, [](const Vertex* v) { g_component.insert(*v); });
      components.push_back(g_component);
      g_component.clear();
    }
  }
  return components;
}

bool is_bipartite(Graph* graph) {
  g_is_bipartite = true;

  for (auto& x : graph->GetVertexSet()) {
    const Vertex* v = graph->GetInternalVertexPtr(x.first);
    if (v->state_ == Vertex::State::UNDISCOVERED) {
      v->color_ = 1;
      bfs(graph, v, nullptr,
          [](const Vertex* v1, const Vertex* v2, double weight) {
            // Check for any nondiscovery edges that violate two-coloring.
            if (v1->color_ == v2->color_) {
              std::cout << v1->name_ << " (color=" << v1->color_ << ") and "
                        << v2->name_ << " (color=" << v2->color_
                        << ") violate bipartiteness\n";
              g_is_bipartite = false;
            }

            // Color any newly discovered Vertex to be the complement of its
            // parent.
            v2->color_ = -(v1->color_);
          });
    }
  }
  return g_is_bipartite;
}

void print_vertex(const Vertex* v) {
  std::cout << "processing vertex: " << v->name_ << "\n";
}

void print_edge(const Vertex* v1, const Vertex* v2, double weight) {
  std::cout << "processing edge: " << v1->name_ << " -> " << v2->name_ << "\n";
}

}  // namespace graphlib
