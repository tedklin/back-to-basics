#include "mst.hpp"

#include <iostream>
#include <queue>

namespace graphlib {

// Keeps track of next smallest crossing edge.
std::priority_queue<Edge, std::vector<Edge>, std::greater<Edge>>
    g_crossing_edges;

// Debugging utility to check contents of an Edge priority queue.
std::string to_string(
    std::priority_queue<Edge, std::vector<Edge>, std::greater<Edge>> pq) {
  std::string s;
  while (!pq.empty()) {
    s += to_string(pq.top());
    pq.pop();
  }
  s += "\n";
  return s;
}

void prim_visit(Graph* graph, const Vertex* v) {
  v->state_ = Vertex::State::DISCOVERED;
  for (auto& adj : graph->adjacent_set(*v)) {
    const Vertex* v2 = adj.first;
    double weight = adj.second;
    if (v2->state_ == Vertex::State::UNDISCOVERED) {
      g_crossing_edges.emplace(v, v2, weight);
    }
  }
}

std::vector<Edge> prim_mst(Graph* graph) {
  std::vector<Edge> mst;
  while (!g_crossing_edges.empty()) {
    g_crossing_edges.pop();
  }

  // Assuming the given graph is connected, this successfully adds at least one
  // crossing edge to the priority queue to kick off the algorithm.
  prim_visit(graph, &(graph->vertex_set().cbegin()->first));

  while (!g_crossing_edges.empty()) {
    Edge e = g_crossing_edges.top();
    g_crossing_edges.pop();

    if (e.v1_->state_ == Vertex::State::DISCOVERED &&
        e.v2_->state_ == Vertex::State::DISCOVERED) {
      continue;
    }
    mst.push_back(e);
    if (e.v1_->state_ == Vertex::State::UNDISCOVERED) {
      prim_visit(graph, e.v1_);
    }
    if (e.v2_->state_ == Vertex::State::UNDISCOVERED) {
      prim_visit(graph, e.v2_);
    }
  }

  return mst;
}

}  // namespace graphlib
