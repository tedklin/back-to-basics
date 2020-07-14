#include "bfs.hpp"

#include <iostream>
#include <queue>

void bfs(Graph* graph, Vertex start,
         void (*process_vertex_early)(std::shared_ptr<Vertex> v),
         void (*process_edge)(std::shared_ptr<Vertex> v1,
                              std::shared_ptr<Vertex> v2, double weight),
         void (*process_vertex_late)(std::shared_ptr<Vertex> v)) {
  // Ensure that we are referencing a Vertex within the given Graph.
  auto start_iter = graph->adjacency_list().find(start);
  if (start_iter == graph->adjacency_list().cend()) {
    std::cerr << "Error! Tried to perform BFS with a start vertex that's not "
                 "in the graph!\n";
    return;
  }
  std::shared_ptr<Vertex> start_ptr =
      std::make_shared<Vertex>(start_iter->first);

  // Start traditional BFS algorithm.
  std::queue<std::shared_ptr<Vertex>> q;
  q.push(start_ptr);

  while (!q.empty()) {
    std::shared_ptr<Vertex> v = q.front();
    q.pop();

    v->state_ = Vertex::State::DISCOVERED;
    if (process_vertex_early) {
      process_vertex_early(v);
    }

    // Recall our representation of an edge is a map from a pointer to an
    // adjacent destination Vertex to a floating-point edge weight.
    // edge.first is the destination Vertex, edge.second is the weight.
    for (auto edge : graph->edge_set(*v)) {
      if (process_edge) {
        process_edge(v, edge.first, edge.second);
      }

      if (edge.first->state_ == Vertex::State::UNDISCOVERED) {
        edge.first->state_ = Vertex::State::DISCOVERED;
        // parent of edge.first is v
        q.push(edge.first);
      }
    }

    if (process_vertex_late) {
      process_vertex_late(v);
    }
    v->state_ = Vertex::State::PROCESSED;
  }
}
