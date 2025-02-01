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

int Graph::dynamicProgrammingRecursion(
    int visitedVerticesBitwise, int currentVertex,
    std::vector<std::vector<int>> &memoryTable,
    std::vector<std::vector<int>> &prevMemoryTable) {
  if (visitedVerticesBitwise == (1 << qtdVertices) - 1) {
    return adjMatrix[currentVertex][0];
  }

  if (memoryTable[currentVertex][visitedVerticesBitwise] != -1) {
    return memoryTable[currentVertex][visitedVerticesBitwise];
  }

  int minCost = std::numeric_limits<int>::max();
  int bestNext = -1;

  for (int next = 0; next < qtdVertices; next++) {
    if ((visitedVerticesBitwise & (1 << next)) == 0) {
      int newMask = visitedVerticesBitwise | (1 << next);
      int cost = adjMatrix[currentVertex][next] +
                 dynamicProgrammingRecursion(newMask, next, memoryTable,
                                             prevMemoryTable);
      if (cost < minCost) {
        minCost = cost;
        bestNext = next;
      }
    }
  }

  prevMemoryTable[currentVertex][visitedVerticesBitwise] = bestNext;
  return memoryTable[currentVertex][visitedVerticesBitwise] = minCost;
}

std::pair<int, std::vector<std::string>> Graph::tspDynamicProgramming() {
  std::vector<std::vector<int>> memoryTable(
      qtdVertices, std::vector<int>(1 << qtdVertices, -1));
  std::vector<std::vector<int>> prevMemoryTable(
      qtdVertices, std::vector<int>(1 << qtdVertices, -1));

  int minCost = dynamicProgrammingRecursion(1, 0, memoryTable, prevMemoryTable);

  std::vector<int> bestPath;
  int mask = 1, curr = 0;
  while (true) {
    bestPath.push_back(curr);
    int next = prevMemoryTable[curr][mask];
    if (next == -1)
      break;
    mask |= (1 << next);
    curr = next;
  }

  std::vector<std::string> bestPathStr;
  for (int id : bestPath) {
    bestPathStr.push_back(vertices[id].name);
  }

  return {minCost, bestPathStr};
}

std::pair<int, std::vector<std::string>> Graph::tspGreedy() {
  std::vector<int> cities(qtdVertices);
  for (int i = 0; i < qtdVertices; i++) {
    cities[i] = i;
  }

  int minCost = 0;
  std::vector<int> bestPath;
  std::vector<bool> visited(qtdVertices, false);

  int currentCity = 0;
  bestPath.push_back(currentCity);
  visited[currentCity] = true;

  for (int step = 1; step < qtdVertices; step++) {
    int nextCity = -1;
    int minDist = std::numeric_limits<int>::max();

    for (int i = 0; i < qtdVertices; i++) {
      if (!visited[i] && adjMatrix[currentCity][i] < minDist) {
        minDist = adjMatrix[currentCity][i];
        nextCity = i;
      }
    }

    if (nextCity == -1)
      break;

    bestPath.push_back(nextCity);
    visited[nextCity] = true;
    minCost += minDist;
    currentCity = nextCity;
  }

  minCost += adjMatrix[currentCity][0];
  bestPath.push_back(0);

  std::vector<std::string> bestPathStr;
  for (const int id : bestPath) {
    bestPathStr.push_back(vertices[id].name);
  }

  return {minCost, bestPathStr};
}
