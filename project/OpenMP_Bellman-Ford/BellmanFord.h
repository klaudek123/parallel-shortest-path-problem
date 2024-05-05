#ifndef BELLMAN_FORD_H
#define BELLMAN_FORD_H

#include <vector>
#include <limits>

class BellmanFord {
public:
    BellmanFord(int numberOfVertices);
    void FindShortestPath(const std::vector<std::vector<std::vector<int>>>& adjList);
    void PrintShortestPaths() const;
private:
    int numberOfVertices;
    std::vector<int> pathArray;
    const int infinity = 100000;
};

#endif // BELLMAN_FORD_H
