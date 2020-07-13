/**
 * This is my attempt at defining a graph class type completely from scratch,
 * based on concepts in Skiena but using different underlying data structures.
 * The primary goal is to be as intuitive as possible, with the potential
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
        E -> A, D, C

  =============================================================================

  The "Vertex" class represents a vertex with a string name and an optional
  floating point weight. Note that vertex weights are a separate concept from
  edge weights, which we will see below.

  The "Graph" class defines an "AdjacencyList" typename (unordered_map<Vertex,
  EdgeSet>), which maps each vertex of a graph to a corresponding "EdgeSet"
  type. Note that the set of keys in the "AdjacencyList" represents the set of
  all vertices in the graph.

  The "Graph" class also defines the "EdgeSet" typename (unordered_map<Vertex,
  double>), which represents the set of neighboring vertices with edges to an
  arbitrary "source" vertex (the "source" vertex is defined by the AdjacencyList
  key to which an EdgeSet is bound). The underlying data structure for the
  EdgeSet type is a map to support associating edges with floating point
  weights.

  Thus, the adjacency list in the example above could be thought of abstractly
  as the following literal representation:

    rep1 = {
        {A, {D, E}},
        {B, {}},
        {C, {E}},
        {D, {A, E}},
        {E, {A, D, C}}
    }

  The actual underlying AdjacencyList structure stored by the class (includes
  implicit weights of 1 for an unweighted graph) would have a literal
  representation of:

    rep2 = {
        {A, {{D, 1}, {E, 1}}},
        {B, {}},
        {C, {{E, 1}}},
        {D, {{A, 1}, {E, 1}}},
        {E, {{A, 1}, {D, 1}, {C, 1}}}
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

#include <iostream>  // TODO: remove
#include <string>
#include <unordered_map>
#include <unordered_set>

struct Vertex {
  enum State { UNDISCOVERED, DISCOVERED, PROCESSED };

  Vertex(const std::string& name, double weight = 1)
      : name_(name), weight_(weight) {}

  std::string name_;
  double weight_;
  State state_ = State::UNDISCOVERED;
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

// Overload std::hash for our self-defined Vertex type.
// https://en.cppreference.com/w/cpp/container/unordered_map/unordered_map
namespace std {
template <>
struct hash<Vertex> {
  std::size_t operator()(const Vertex& f) const {
    return std::hash<std::string>{}(f.name_);
  }
};
}  // namespace std

// TODO: bfs, dfs
class Graph {
 public:
  using EdgeSet = std::unordered_map<Vertex, double>;
  using AdjacencyList = std::unordered_map<Vertex, EdgeSet>;

  // Convenience typename used for user input; not actual underlying type.
  using InputUnweightedAL =
      std::unordered_map<Vertex, std::unordered_set<Vertex>>;

  Graph(bool is_directed) : is_directed_(is_directed) {}

  // Creates a graph given only a set of vertices, no edges.
  Graph(const std::unordered_set<Vertex>& vertex_set, bool is_directed)
      : is_directed_(is_directed) {
    for (const Vertex& v : vertex_set) {
      add_vertex(v);
    }
  }

  // Creates a graph without specified edge weights.
  Graph(InputUnweightedAL unweighted_al, bool is_directed)
      : is_directed_(is_directed) {
    for (const auto& p : unweighted_al) {
      Vertex source = p.first;
      add_vertex(source);
      for (const Vertex& dest : p.second) {
        add_edge(source, dest);
      }
    }
  }

  Graph(AdjacencyList adjacency_list, bool is_directed)
      : adjacency_list_(adjacency_list), is_directed_(is_directed) {}

  void add_edge(const Vertex& source, const Vertex& dest,
                double edge_weight = 1) {
    add_vertex(source);
    add_vertex(dest);

    adjacency_list_[source][dest] = edge_weight;
    if (!is_directed_) {
      adjacency_list_[dest][source] = edge_weight;
    }
  }

  void add_vertex(const Vertex& v) { adjacency_list_[v]; }

  std::string vertex_set_str() const {
    std::string s("Vertex set:\n");
    for (const auto& p : adjacency_list_) {
      s += p.first.name_ + " | ";
    }
    s += '\n';
    return s;
  }

  std::string adjacency_list_str() const {
    std::string s("Adjacency list:\n");
    for (const auto& p : adjacency_list_) {
      s += p.first.name_ + " -> ";
      for (const auto& e : p.second) {
        // recall e.second is weight
        s += e.first.name_ + "(" + std::to_string(e.second) + ") | ";
      }
      s += '\n';
    }
    s += '\n';
    return s;
  }

 private:
  AdjacencyList adjacency_list_;
  bool is_directed_;
};
