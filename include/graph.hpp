#ifndef GRAPH_HPP
#define GRAPH_HPP

#include "../include/edge.hpp"
#include "../include/vertex.hpp"
#include <unordered_map>
#include <vector>

class Graph {
public:
  std::vector<Vertex> vertices;
  std::vector<Edge> edges;
  std::unordered_map<std::string, std::unordered_map<std::string, int>>
      adjMatrix;

  void addVertex(const std::string &name);
  void addEdge(const std::string &from, const std::string &to, int weight);

  std::pair<int, std::vector<std::string>> tspBruteForce();
  std::pair<int, std::vector<std::string>> tspDynamicProgramming();
  std::pair<int, std::vector<std::string>> tspGreedy();
};

#endif // GRAPH_HPP
