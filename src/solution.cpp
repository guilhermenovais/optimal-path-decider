#include "../include/solution.hpp"
#include "../include/graph.hpp"
#include <iostream>
#include <string>
#include <unordered_map>

void Solution::run() {
  char strategy;
  int qtdVertices, qtdEdges;
  // std::cin >> strategy;
  strategy = 'b';
  std::cin >> qtdVertices >> qtdEdges;
  Graph graph = Graph(qtdVertices);
  std::unordered_map<std::string, int> nameToIdMap;
  int currentId = 0;

  for (int i = 0; i < qtdEdges; i++) {
    std::string from, to;
    int weight;
    std::cin >> from >> to >> weight;

    if (nameToIdMap.find(from) == nameToIdMap.end()) {
      nameToIdMap[from] = currentId;
      graph.addVertex(nameToIdMap[from], from);
      currentId++;
    }

    if (nameToIdMap.find(to) == nameToIdMap.end()) {
      nameToIdMap[to] = currentId;
      graph.addVertex(nameToIdMap[to], to);
      currentId++;
    }

    graph.addEdge(nameToIdMap[from], nameToIdMap[to], weight);
  }

  std::pair<int, std::vector<std::string>> result;
  switch (strategy) {
  case 'b':
    result = graph.tspBruteForce();
    break;
  case 'd':
    result = graph.tspDynamicProgramming();
    break;
  case 'g':
    result = graph.tspGreedy();
    break;
  default:
    std::cerr << "Estratégia inválida!" << std::endl;
    return;
  }

  std::cout << result.first << std::endl;
  for (const auto &city : result.second) {
    std::cout << city << " ";
  }
  std::cout << std::endl;
}
