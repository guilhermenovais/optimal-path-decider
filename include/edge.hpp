#ifndef EDGE_HPP
#define EDGE_HPP

#include <string>

class Edge {
public:
  std::string from, to;
  int weight;

  Edge(const std::string &from, const std::string &to, int weight);
};

#endif // EDGE_HPP
