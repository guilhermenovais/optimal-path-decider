#ifndef VERTEX_HPP
#define VERTEX_HPP

#include <string>

class Vertex {
public:
  int id;
  std::string name;
  Vertex(int id, const std::string &name);
  Vertex();
};

#endif // VERTEX_HPP
