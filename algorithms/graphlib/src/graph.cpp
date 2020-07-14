// Vertex and Graph function implementations

#include "graph.hpp"

#include <stdexcept>
#include <string>

namespace graphlib {

inline std::string to_string(const Vertex::State& state) {
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

void Graph::add_vertex(const Vertex& v) { adjacency_list_[v]; }

void Graph::add_edge(const Vertex& source, const Vertex& dest,
                     double edge_weight) {
  add_vertex(source);
  add_vertex(dest);

  // There should only be one instance of each Vertex in a Graph, so we store
  // adjacent vertices as pointers to the main set of Vertices (i.e. the keyset
  // of adjacency_list_).
  auto source_iter = adjacency_list_.find(source);
  auto dest_iter = adjacency_list_.find(dest);

  // This should never happen, because we always add both the source and the
  // dest vertices at the beginning of this function. Still, we check just in
  // case.
  if (source_iter == adjacency_list_.end() ||
      dest_iter == adjacency_list_.end()) {
    std::runtime_error(
        "Graph::add_edge error! Tried to add an edge to a nonexistent vertex");
  }

  const Vertex* source_ptr = &(source_iter->first);
  const Vertex* dest_ptr = &(dest_iter->first);

  adjacency_list_[source][dest_ptr] = edge_weight;
  if (!is_directed_) {
    adjacency_list_[dest][source_ptr] = edge_weight;
  }
}

std::string Graph::vertex_set_str() const {
  std::string s("Vertex set:\n");
  for (const auto& p : adjacency_list_) {
    s += p.first.name_ + "(state=" + to_string(p.first.state_) + ")" + " | ";
  }
  s += '\n';
  return s;
}

std::string Graph::adjacency_list_str() const {
  std::string s("Adjacency list:\n");
  for (const auto& p : adjacency_list_) {
    s += p.first.name_ + " -> ";
    for (const auto& e : p.second) {
      s += e.first->name_ + "(wgt=" + std::to_string(e.second) + ") | ";
    }
    s += '\n';
  }
  s += '\n';
  return s;
}

void Graph::reset_state() {
  for (auto& p : adjacency_list_) {
    p.first.state_ = Vertex::State::UNDISCOVERED;
  }
}

}  // namespace graphlib