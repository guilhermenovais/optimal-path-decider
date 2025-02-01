#include "../include/graph.hpp"
#include <limits>
#include <string>
#include <vector>

Graph::Graph(int qtdVertices)
    : qtdVertices(qtdVertices), vertices(std::vector<Vertex>(qtdVertices)),
      adjMatrix(std::vector<std::vector<int>>(qtdVertices)) {}

void Graph::addVertex(int id, const std::string &name) {
  Vertex newVertex = Vertex(id, name);
  vertices[id] = newVertex;
  adjMatrix[id] = std::vector<int>(qtdVertices);
}

void Graph::addEdge(const int from, const int to, int weight) {
  adjMatrix[from][to] = weight;
  adjMatrix[to][from] = weight;
}

int Graph::calculatePathCost(std::vector<int> path) {
  int cost = 0;
  for (int i = 1; i < int(path.size()); i++) {
    cost += adjMatrix[path[i - 1]][path[i]];
  }
  cost += adjMatrix[path[path.size() - 1]][path[0]];
  return cost;
}

void Graph::findShortestPath(std::vector<int> &path, int start, int &minCost,
                             std::vector<int> &bestPath) {
  if (start == int(path.size())) {
    int cost = calculatePathCost(path);
    if (cost < minCost) {
      minCost = cost;
      bestPath = path;
    }
    return;
  }

  for (int i = start; i < int(path.size()); i++) {
    std::swap(path[start], path[i]);
    findShortestPath(path, start + 1, minCost, bestPath);
    std::swap(path[start], path[i]);
  }
}

std::pair<int, std::vector<std::string>> Graph::tspBruteForce() {
  std::vector<int> cities = std::vector<int>(qtdVertices);
  for (int i = 0; i < qtdVertices; i++) {
    cities[i] = i;
  }

  int minCost = std::numeric_limits<int>::max();
  std::vector<int> bestPath = std::vector<int>(qtdVertices);

  findShortestPath(cities, 0, minCost, bestPath);

  std::vector<std::string> bestPathStr;
  for (const int id : bestPath) {
    bestPathStr.push_back(vertices[id].name);
  }

  return {minCost, bestPathStr};
}

int Graph::dynamicProgrammingRecursion(int mask, int curr,
                                       std::vector<int> &path,
                                       std::vector<int> &bestPath) {
  if (mask == (1 << qtdVertices) - 1) {
    return adjMatrix[curr][0];
  }

  if (memo[curr][mask] != -1)
    return memo[curr][mask];

  int minCost = std::numeric_limits<int>::max();
  for (int next = 0; next < qtdVertices; next++) {
    if ((mask & (1 << next)) == 0) {
      path.push_back(next);
      int cost =
          adjMatrix[curr][next] +
          dynamicProgrammingRecursion(mask | (1 << next), next, path, bestPath);
      path.pop_back();

      if (cost < minCost) {
        minCost = cost;
        bestPath = path;
      }
    }
  }

  return memo[curr][mask] = minCost;
}

std::pair<int, std::vector<std::string>> Graph::tspDynamicProgramming() {
  std::vector<int> path = {0}, bestPath;
  memo.assign(qtdVertices, std::vector<int>(1 << qtdVertices, -1));

  int minCost = dynamicProgrammingRecursion(1, 0, path, bestPath);

  std::vector<std::string> bestPathStr;
  std::vector<bool> isInside = std::vector<bool>(qtdVertices);
  for (int id : bestPath) {
    isInside[id] = true;
    bestPathStr.push_back(vertices[id].name);
  }

  for (int i = 0; i < qtdVertices; i++) {
    if (!isInside[i]) {
      bestPathStr.push_back(vertices[i].name);
    }
  }

  return {minCost, bestPathStr};
}

std::pair<int, std::vector<std::string>> Graph::tspGreedy() {
  // Implementação do algoritmo guloso
  return {0, {}};
}
