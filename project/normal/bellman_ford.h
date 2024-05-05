#ifndef BELLMAN_FORD_H
#define BELLMAN_FORD_H

#include <vector>
#include <string>

class BellmanFord {
public:
    BellmanFord(int numberOfVertices);
    void FindShortestPath(const std::vector<std::vector<std::vector<int>>>& adjList);
    std::vector<int> pathArray;
private:
    int numberOfVertices;
    int infinity;
};



#endif //BELLMAN_FORD_H
