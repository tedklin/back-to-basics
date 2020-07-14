#include "bfs.hpp"

#include <iostream>
#include <map>
#include <queue>
#include <stack>

namespace graphlib {

std::map<Vertex, Vertex> bfs(Graph* graph, Vertex search_root,
                             void (*process_vertex_early)(const Vertex* v),
                             void (*process_edge)(const Vertex* v1,
                                                  const Vertex* v2,
                                                  double weight),
                             void (*process_vertex_late)(const Vertex* v)) {
  // Ensure that we are referencing a Vertex within the given Graph.
  auto root_iter = graph->adjacency_list().find(search_root);
  if (root_iter == graph->adjacency_list().end()) {
    std::cerr << "Warning! Tried to perform BFS with a search root that's not "
                 "in the graph!\n\n";
    return std::map<Vertex, Vertex>();
  }

  // Map from a copy of each Vertex to its "parent" in a shortest-path tree
  // w.r.t. the root.
  std::map<Vertex, Vertex> parent;

  // Start BFS.
  std::queue<const Vertex*> q;
  q.push(&(root_iter->first));

  while (!q.empty()) {
    const Vertex* v1 = q.front();
    q.pop();

    v1->state_ = Vertex::State::DISCOVERED;
    if (process_vertex_early) {
      process_vertex_early(v1);
    }

    // Recall our representation of an edge is a map from a pointer to an
    // adjacent destination Vertex to a floating-point edge weight.
    for (auto adj : graph->adjacent_set(*v1)) {
      const Vertex* v2 = &(*(adj.first));
      double weight = adj.second;

      if (process_edge) {
        process_edge(v1, v2, weight);
      }

      if (v2->state_ == Vertex::State::UNDISCOVERED) {
        v2->state_ = Vertex::State::DISCOVERED;
        parent.insert({*v2, *v1});
        q.push(v2);
      }
    }

    if (process_vertex_late) {
      process_vertex_late(v1);
    }
    v1->state_ = Vertex::State::PROCESSED;
  }

  return parent;
}

std::stack<Vertex> shortest_path(Graph* graph, Vertex search_root,
                                 Vertex destination) {
  std::map<Vertex, Vertex> parent = bfs(graph, search_root);

  Vertex v = destination;
  std::stack<Vertex> s;
  s.push(v);
  while (v != search_root) {
    v = parent.at(v);
    s.push(v);
  }
  return s;
}

// Global component variable to circumvent inability to pass capturing lambdas
// as function pointers. Remember to clear after each use.
std::set<Vertex> component;

std::vector<std::set<Vertex>> connected_components(Graph* graph) {
  std::vector<std::set<Vertex>> components;
  for (auto x : graph->adjacency_list()) {
    if (x.first.state_ == Vertex::State::UNDISCOVERED) {
      bfs(graph, x.first, [](const Vertex* v) { component.insert(*v); });
      components.push_back(component);
      component.clear();
    }
  }
  return components;
}

void print_vertex(const Vertex* v) {
  std::cout << "processing vertex: " << v->name_ << "\n";
}

void print_edge(const Vertex* v1, const Vertex* v2, double weight) {
  std::cout << "processing edge: " << v1->name_ << " -> " << v2->name_ << "\n";
}

}  // namespace graphlib
