#include "bfs.hpp"

#include <iostream>
#include <memory>
#include <queue>

void bfs(Graph* graph, Vertex root,
         void (*process_vertex_early)(const Vertex* v),
         void (*process_edge)(const Vertex* v1, const Vertex* v2,
                              double weight),
         void (*process_vertex_late)(const Vertex* v)) {
  // Ensure that we are referencing a Vertex within the given Graph.
  auto root_iter = graph->mutable_adjacency_list().find(root);
  if (root_iter == graph->mutable_adjacency_list().end()) {
    std::cerr << "Error! Tried to perform BFS with a start vertex that's not "
                 "in the graph!\n\n";
    return;
  }

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
        // parent of v2 is v1
        q.push(v2);
      }
    }

    if (process_vertex_late) {
      process_vertex_late(v1);
    }
    v1->state_ = Vertex::State::PROCESSED;
  }
}

void print_vertex(const Vertex* v) {
  std::cout << "processing vertex: " << v->name_ << "\n";
}

void print_edge(const Vertex* v1, const Vertex* v2, double weight) {
  std::cout << "processing edge: " << v1->name_ << " -> " << v2->name_ << "\n";
}
