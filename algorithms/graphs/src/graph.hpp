/**
 * This is my attempt at defining a graph class type completely from scratch,
 * based on concepts in Skiena but using different underlying data structures.
 * The primary goal is to be as intuitive as possible, at the potential
 * expense of space overhead.
 *
 * The concept of weights is supported but optional. Unweighted graphs simply
 * use implicit default values of 1.
 */

/*
  Let the following be an undirected, unweighted graph with vertices
  {A, B, C, D, E}:

        A       B
        |\
        | \
        |  \
        D---E---C


  The corresponding adjacency list would be:

        A -> D, E
        B -> (none)
        C -> E
        D -> A, E
        E -> A, C, D

  =============================================================================

  The "Vertex" class represents a vertex with a string name and an optional
  floating point weight. Note that vertex weights are a separate concept from
  edge weights, which we will see below.

  The "Graph" class defines an "AdjacencyList" typename (map<Vertex, EdgeSet>),
  which maps each vertex of a graph to a corresponding "EdgeSet" type. Note that
  the set of keys in the "AdjacencyList" represents the set of all vertices in
  the graph.

  The "Graph" class also defines the "EdgeSet" typename (map<Vertex, double>),
  which represents the set of neighboring vertices with edges to an arbitrary
  "source" vertex (the "source" vertex is defined by the AdjacencyList key to
  which an EdgeSet is bound). The underlying data structure for the EdgeSet type
  is a map to support associating edges with floating point weights.

  Thus, the adjacency list in the example above could be thought of abstractly
  as the following literal representation:

    rep1 = {
        {A, {D, E}},
        {B, {}},
        {C, {E}},
        {D, {A, E}},
        {E, {A, C, D}}
    }

  The actual underlying AdjacencyList structure stored by the class (includes
  implicit weights of 1 for an unweighted graph) would have a literal
  representation of:

    rep2 = {
        {A, {{D, 1}, {E, 1}}},
        {B, {}},
        {C, {{E, 1}}},
        {D, {{A, 1}, {E, 1}}},
        {E, {{A, 1}, {C, 1}, {D, 1}}}
    }

  Both can be passed in as a literal initializers for the "Graph" class, with
  "rep1" implicitly resulting in an unweighted graph with the underlying
  structure "rep2".

  Furthermore, since this is an undirected graph (i.e. existence of edge {A, D}
  implies edge {D, A}), the "Graph" class also has support for passing in
  literal intializers that don't include duplicate edges.

    rep3 = {
        {A, {D, E}},
        {B, {}},
        {C, {}},
        {D, {E}},
        {E, {C}}
    }

  "rep3" would also result in the underlying structure "rep2".

  See the "example" function in test.cpp for verification that this works.

 */

#pragma once

#include <map>
#include <memory>
#include <set>
#include <string>

struct Vertex {
  enum State { UNDISCOVERED, DISCOVERED, PROCESSED };

  Vertex(const std::string& name, double weight = 1)
      : name_(name), weight_(weight) {}

  std::string name_;
  double weight_;

  // TODO: check if mutable here is appropriate
  // Having a mutable State shouldn't affect map/unordered_map behavior because
  // the overloaded comparison operators and hash functions we define only use
  // the name of the Vertex as the value.
  mutable State state_ = State::UNDISCOVERED;
};

inline bool operator<(const Vertex& lhs, const Vertex& rhs) {
  return (lhs.name_ < rhs.name_);
}

inline bool operator==(const Vertex& lhs, const Vertex& rhs) {
  return (lhs.name_ == rhs.name_);
}

inline bool operator!=(const Vertex& lhs, const Vertex& rhs) {
  return !operator==(lhs, rhs);
}

// To use unordered_map as our underlying data structure, we must overload
// std::hash with our self-defined Vertex type.
// https://en.cppreference.com/w/cpp/container/unordered_map/unordered_map
namespace std {
template <>
struct hash<Vertex> {
  std::size_t operator()(const Vertex& f) const {
    return std::hash<std::string>{}(f.name_);
  }
};
}  // namespace std

class Graph {
 private:
  // Underlying data structure types.
  using EdgeSet = std::map<std::shared_ptr<Vertex>, double>;
  using AdjacencyList = std::map<Vertex, EdgeSet>;

 public:
  // Convenience typenames used for user input; not actual underlying types.
  using InputUnweightedAL = std::map<Vertex, std::set<Vertex>>;
  using InputWeightedAL = std::map<Vertex, std::map<Vertex, double>>;
  using InputVertexSet = std::set<Vertex>;

  // Constructs an empty graph.
  Graph(bool is_directed);

  // Constructs a graph given only a set of vertices, no edges.
  Graph(const InputVertexSet& vertex_set, bool is_directed);

  // Constructs a graph without specified edge weights.
  Graph(InputUnweightedAL unweighted_al, bool is_directed);

  // Constructs a fully specified weighted graph.
  Graph(InputWeightedAL adjacency_list, bool is_directed);

  void add_vertex(const Vertex& v);

  void add_edge(const Vertex& source, const Vertex& dest,
                double edge_weight = 1);

  // Reset all Vertices in this Graph to state UNDISCOVERED.
  void reset_state();

  std::string vertex_set_str() const;

  std::string adjacency_list_str() const;

  const AdjacencyList& adjacency_list() const { return adjacency_list_; }

  AdjacencyList& mutable_adjacency_list() { return adjacency_list_; }

  const EdgeSet& edge_set(const Vertex& source) const {
    return adjacency_list_.at(source);
  }

  EdgeSet& mutable_edge_set(const Vertex& source) {
    return adjacency_list_.at(source);
  }

 private:
  AdjacencyList adjacency_list_;
  bool is_directed_;
};
