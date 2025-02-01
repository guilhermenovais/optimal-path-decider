#ifndef GRAPH_HPP
#define GRAPH_HPP

#include "../include/vertex.hpp"
#include <vector>

/**
 * @class Graph
 * @brief Representa um grafo com vértices e arestas ponderadas.
 */
class Graph {
public:
  /**
   * @brief Adiciona um vértice ao grafo.
   * @param id Identificador único do vértice.
   * @param name Nome do vértice.
   */
  void addVertex(int id, const std::string &name);

  /**
   * @brief Adiciona uma aresta entre dois vértices do grafo.
   * @param from Identificador do vértice de origem.
   * @param to Identificador do vértice de destino.
   * @param weight Peso da aresta.
   */
  void addEdge(const int from, const int to, int weight);

  /**
   * @brief Resolve o problema do Caixeiro Viajante (TSP) usando força bruta.
   * @return Par contendo o custo mínimo e o caminho correspondente.
   */
  std::pair<int, std::vector<std::string>> tspBruteForce();

  /**
   * @brief Resolve o problema do Caixeiro Viajante (TSP) usando programação
   * dinâmica.
   * @return Par contendo o custo mínimo e o caminho correspondente.
   */
  std::pair<int, std::vector<std::string>> tspDynamicProgramming();

  /**
   * @brief Resolve o problema do Caixeiro Viajante (TSP) usando uma abordagem
   * gulosa.
   * @return Par contendo o custo mínimo e o caminho correspondente.
   */
  std::pair<int, std::vector<std::string>> tspGreedy();

  /**
   * @brief Construtor da classe Graph.
   * @param qtdVertices Número total de vértices no grafo.
   */
  Graph(int qtdVertices);

private:
  int qtdVertices;              ///< Número total de vértices no grafo.
  std::vector<Vertex> vertices; ///< Lista de vértices do grafo.
  std::vector<std::vector<int>> adjMatrix; ///< Matriz de adjacência do grafo.
  std::vector<std::vector<int>>
      memo; ///< Estrutura de memória usada na programação dinâmica.

  /**
   * @brief Calcula o custo total de um caminho no grafo.
   * @param path Vetor contendo a sequência de vértices no caminho.
   * @return Custo total do caminho.
   */
  int calculatePathCost(std::vector<int> path);

  /**
   * @brief Encontra o menor caminho entre os vértices.
   * @param path Caminho atual sendo avaliado.
   * @param start Índice do vértice inicial.
   * @param minCost Referência para armazenar o custo mínimo encontrado.
   * @param bestPath Referência para armazenar o melhor caminho encontrado.
   */
  void findShortestPath(std::vector<int> &path, int start, int &minCost,
                        std::vector<int> &bestPath);

  /**
   * @brief Função recursiva para resolver o TSP usando programação dinâmica.
   * @param visitedVerticesBitwise Máscara de bits representando os vértices
   * visitados.
   * @param currentVertex Índice do vértice atual.
   * @param memoryTable Tabela de memória para armazenar os custos já
   * calculados.
   * @param prevMemoryTable Tabela de memória para reconstrução do caminho.
   * @return O custo mínimo encontrado a partir do estado atual.
   */
  int dynamicProgrammingRecursion(
      int visitedVerticesBitwise, int currentVertex,
      std::vector<std::vector<int>> &memoryTable,
      std::vector<std::vector<int>> &prevMemoryTable);
};

#endif // GRAPH_HPP
