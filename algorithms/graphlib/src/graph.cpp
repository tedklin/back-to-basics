#include "graph.hpp"

#include <stdexcept>
#include <string>

namespace graphlib {

std::string to_string(const Vertex::State& state) {
  switch (state) {
    case Vertex::State::UNDISCOVERED:
      return "0";
      break;
    case Vertex::State::DISCOVERED:
      return "1";
      break;
    case Vertex::State::PROCESSED:
      return "2";
      break;
  }
}

Graph::Graph(bool is_directed) : is_directed_(is_directed) {}

Graph::Graph(const InputVertexSet& vertex_set, bool is_directed)
    : is_directed_(is_directed) {
  for (const Vertex& v : vertex_set) {
    AddVertex(v);
  }
}

Graph::Graph(InputUnweightedAL unweighted_al, bool is_directed)
    : is_directed_(is_directed) {
  for (const auto& p : unweighted_al) {
    Vertex source = p.first;
    AddVertex(source);
    for (const Vertex& dest : p.second) {
      AddEdge(source, dest);
    }
  }
}

Graph::Graph(InputWeightedAL weighted_al, bool is_directed)
    : is_directed_(is_directed) {
  for (const auto& p : weighted_al) {
    Vertex source = p.first;
    AddVertex(source);
    for (const auto& e : p.second) {
      AddEdge(source, e.first, e.second);
    }
  }
}

void Graph::AddVertex(const Vertex& v) {
  v.Reset();
  vertex_set_[v];
}

const Vertex* Graph::GetInternalVertexPtr(const Vertex& v) const {
  auto vertex_iter = vertex_set_.find(v);
  if (vertex_iter == vertex_set_.end()) {
    throw std::runtime_error(
        "Graph::GetInternalVertexPtr error! Tried to obtain pointer to "
        "nonexistent vertex (" +
        v.name_ + ")\n");
  }
  return &(vertex_iter->first);
}

void Graph::AddEdge(const Vertex& source, const Vertex& dest,
                    double edge_weight) {
  AddVertex(source);
  AddVertex(dest);

  // There should only be one instance of each Vertex in a Graph, so we store
  // adjacent vertices as pointers to the main set of Vertices (i.e. the keyset
  // of vertex_set_).
  vertex_set_[source][GetInternalVertexPtr(dest)] = edge_weight;
  if (!is_directed_) {
    vertex_set_[dest][GetInternalVertexPtr(source)] = edge_weight;
  }
}

std::string Graph::GetVertexSetStr() const {
  std::string s("Vertex set:\n");
  for (const auto& p : vertex_set_) {
    s += p.first.name_ + "(state=" + graphlib::to_string(p.first.state_) + ")" +
         " | ";
  }
  s += '\n';
  return s;
}

void Graph::ResetState() {
  for (auto& p : vertex_set_) {
    p.first.Reset();
  }
}

std::string to_string(const Graph& graph) {
  std::string s("Adjacency lists:\n");
  for (const auto& p : graph.GetVertexSet()) {
    s += p.first.name_ + " -> ";
    for (const auto& e : p.second) {
      s += e.first->name_ + "(wgt=" + std::to_string(e.second) + ") | ";
    }
    s += '\n';
  }
  s += '\n';
  return s;
}

}  // namespace graphlib
