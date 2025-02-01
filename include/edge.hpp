#ifndef EDGE_HPP
#define EDGE_HPP

/**
 * @class Edge
 * @brief Representa uma aresta em um grafo.
 */
class Edge {
public:
  int from;   ///< Vértice de origem.
  int to;     ///< Vértice de destino.
  int weight; ///< Peso da aresta.

  /**
   * @brief Construtor da classe Edge.
   * @param from Vértice de origem.
   * @param to Vértice de destino.
   * @param weight Peso da aresta.
   */
  Edge(const int from, const int to, int weight);
};

#endif // EDGE_HPP
