#ifndef EDGE_HPP
#define EDGE_HPP

class Edge {
public:
  int from, to;
  int weight;

  Edge(const int from, const int to, int weight);
};

#endif // EDGE_HPP
