#ifndef VERTEX_HPP
#define VERTEX_HPP

#include <string>

/**
 * @class Vertex
 * @brief Representa um vértice em um grafo.
 */
class Vertex {
public:
  int id;           ///< Identificador único do vértice.
  std::string name; ///< Nome do vértice.

  /**
   * @brief Construtor da classe Vertex.
   * @param id Identificador do vértice.
   * @param name Nome do vértice.
   */
  Vertex(int id, const std::string &name);

  /**
   * @brief Construtor padrão da classe Vertex.
   */
  Vertex();
};

#endif // VERTEX_HPP
