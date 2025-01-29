#include "../include/solution.hpp"
#include "../include/graph.hpp"
#include <iostream>

void Solution::run() {
  Graph graph;
  char strategy;
  int V, E;
  std::cin >> strategy >> V >> E;

  for (int i = 0; i < E; i++) {
    std::string from, to;
    int weight;
    std::cin >> from >> to >> weight;
    graph.addVertex(from);
    graph.addVertex(to);
    graph.addEdge(from, to, weight);
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
