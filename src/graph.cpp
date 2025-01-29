#include "../include/graph.hpp"

void Graph::addVertex(const std::string &name) {
  vertices.emplace_back(name);
  adjMatrix[name] = {};
}

void Graph::addEdge(const std::string &from, const std::string &to,
                    int weight) {
  edges.emplace_back(from, to, weight);
  adjMatrix[from][to] = weight;
  adjMatrix[to][from] = weight;
}

std::pair<int, std::vector<std::string>> Graph::tspBruteForce() {
  // Implementação da força bruta
  return {0, {}};
}

std::pair<int, std::vector<std::string>> Graph::tspDynamicProgramming() {
  // Implementação da programação dinâmica
  return {0, {}};
}

std::pair<int, std::vector<std::string>> Graph::tspGreedy() {
  // Implementação do algoritmo guloso
  return {0, {}};
}
