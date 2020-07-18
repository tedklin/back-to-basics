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
  std::string s("Edge priority queue contents:\n");
  while (!pq.empty()) {
    s += to_string(pq.top());
    pq.pop();
  }
  s += '\n';
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
  if (graph->is_directed()) {
    std::cerr << "Error: Tried to run Prim's algorithm on directed graph!\n";
    return std::vector<Edge>();
  }

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

std::vector<Edge> kruskal_mst(Graph* graph) {
  if (graph->is_directed()) {
    std::cerr << "Error: Tried to run Kruskal's algorithm on directed graph!\n";
    return std::vector<Edge>();
  }

  std::vector<Edge> mst;
  while (!g_crossing_edges.empty()) {
    g_crossing_edges.pop();
  }

  // Add all edges in given graph to priority queue.
  for (const auto& v : graph->vertex_set()) {
    const Vertex* v1 = graph->internal_vertex_ptr(v.first);
    for (const auto& adj : v.second) {
      const Vertex* v2 = adj.first;
      double weight = adj.second;
      g_crossing_edges.emplace(v1, v2, weight);
    }
  }

  VertexUnionFind uf(graph);
  while (!g_crossing_edges.empty() && mst.size() < graph->vertex_set().size()) {
    Edge e = g_crossing_edges.top();
    g_crossing_edges.pop();

    if (uf.connected(e.v1_, e.v2_)) {
      continue;
    }
    uf.merge(e.v1_, e.v2_);
    mst.push_back(e);
  }
  return mst;
}

}  // namespace graphlib
