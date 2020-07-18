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
    add_vertex(v);
  }
}

Graph::Graph(InputUnweightedAL unweighted_al, bool is_directed)
    : is_directed_(is_directed) {
  for (const auto& p : unweighted_al) {
    Vertex source = p.first;
    add_vertex(source);
    for (const Vertex& dest : p.second) {
      add_edge(source, dest);
    }
  }
}

Graph::Graph(InputWeightedAL weighted_al, bool is_directed)
    : is_directed_(is_directed) {
  for (const auto& p : weighted_al) {
    Vertex source = p.first;
    add_vertex(source);
    for (const auto& e : p.second) {
      add_edge(source, e.first, e.second);
    }
  }
}

void Graph::add_vertex(const Vertex& v) {
  v.reset();
  vertex_set_[v];
}

const Vertex* Graph::internal_vertex_ptr(const Vertex& v) const {
  auto vertex_iter = vertex_set_.find(v);
  if (vertex_iter == vertex_set_.end()) {
    throw std::runtime_error(
        "Graph::internal_vertex_ptr error! Tried to obtain pointer to "
        "nonexistent vertex (" +
        v.name_ + ")\n");
  }
  return &(vertex_iter->first);
}

void Graph::add_edge(const Vertex& source, const Vertex& dest,
                     double edge_weight) {
  add_vertex(source);
  add_vertex(dest);

  // There should only be one instance of each Vertex in a Graph, so we store
  // adjacent vertices as pointers to the main set of Vertices (i.e. the keyset
  // of vertex_set_).
  vertex_set_[source][internal_vertex_ptr(dest)] = edge_weight;
  if (!is_directed_) {
    vertex_set_[dest][internal_vertex_ptr(source)] = edge_weight;
  }
}

std::string Graph::vertex_set_str() const {
  std::string s("Vertex set:\n");
  for (const auto& p : vertex_set_) {
    s += p.first.name_ + "(state=" + graphlib::to_string(p.first.state_) + ")" +
         " | ";
  }
  s += '\n';
  return s;
}

void Graph::reset_state() {
  for (auto& p : vertex_set_) {
    p.first.reset();
  }
}

std::string to_string(const Graph& graph) {
  std::string s("Adjacency lists:\n");
  for (const auto& p : graph.vertex_set()) {
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
