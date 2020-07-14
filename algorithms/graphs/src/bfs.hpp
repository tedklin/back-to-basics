#pragma once

#include "graph.hpp"

void bfs(Graph* graph, Vertex start,
         void (*process_vertex_early)(std::shared_ptr<Vertex> v),
         void (*process_edge)(std::shared_ptr<Vertex> v1,
                              std::shared_ptr<Vertex> v2, double weight),
         void (*process_vertex_late)(std::shared_ptr<Vertex> v));
