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
  for (const auto& v : unweighted_al) {
    Vertex source = v.first;
    AddVertex(source);
    for (const Vertex& dest : v.second) {
      AddEdge(source, dest);
    }
  }
}

Graph::Graph(InputWeightedAL weighted_al, bool is_directed)
    : is_directed_(is_directed) {
  for (const auto& v : weighted_al) {
    Vertex source = v.first;
    AddVertex(source);
    for (const auto& adj : v.second) {
      AddEdge(source, adj.first, adj.second);
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

void Graph::ResetState() {
  for (auto& v : vertex_set_) {
    v.first.Reset();
  }
}

std::string Graph::GetVertexSetStr() const {
  std::string s("Vertex set:\n");
  for (const auto& v : vertex_set_) {
    s += v.first.name_ + "(state=" + graphlib::to_string(v.first.state_) + ")" +
         " | ";
  }
  s += '\n';
  return s;
}

std::string to_string(const Graph& graph) {
  std::string s("Adjacency lists:\n");
  for (const auto& v : graph.GetVertexSet()) {
    s += v.first.name_ + " -> ";
    for (const auto& adj : v.second) {
      s += adj.first->name_ + "(wgt=" + std::to_string(adj.second) + ") | ";
    }
    s += '\n';
  }
  s += '\n';
  return s;
}

std::shared_ptr<Graph> Graph::GetReverseGraph() const {
  std::shared_ptr<Graph> reverse = std::make_shared<Graph>(true);
  for (const auto& v : this->GetVertexSet()) {
    Vertex source = v.first;
    reverse->AddVertex(source);
    for (const auto& adj : v.second) {
      reverse->AddEdge(*(adj.first), source, adj.second);
    }
  }
  return reverse;
}

}  // namespace graphlib
