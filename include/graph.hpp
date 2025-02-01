#ifndef GRAPH_HPP
#define GRAPH_HPP

#include "../include/vertex.hpp"
#include <vector>

class Graph {
public:
  void addVertex(int id, const std::string &name);
  void addEdge(const int from, const int to, int weight);

  std::pair<int, std::vector<std::string>> tspBruteForce();
  std::pair<int, std::vector<std::string>> tspDynamicProgramming();
  std::pair<int, std::vector<std::string>> tspGreedy();
  Graph(int qtdVertices);

private:
  int qtdVertices;
  std::vector<Vertex> vertices;
  std::vector<std::vector<int>> adjMatrix;
  std::vector<std::vector<int>> memo;

  int calculatePathCost(std::vector<int> path);
  void findShortestPath(std::vector<int> &path, int start, int &minCost,
                        std::vector<int> &bestPath);
  int dynamicProgrammingRecursion(
      int visitedVerticesBitwise, int currentVertex,
      std::vector<std::vector<int>> &memoryTable,
      std::vector<std::vector<int>> &prevMemoryTable);
};

#endif // GRAPH_HPP
