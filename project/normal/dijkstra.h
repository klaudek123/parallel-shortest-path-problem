
#ifndef DIJKSTRA_H
#define DIJKSTRA_H

#include <vector>


class Dijkstra {
public:
    Dijkstra(int numberOfVertices);
    auto FindShortestPath(const std::vector<std::vector<std::vector<int> > > &adjList, int srcNode) -> void;

    std::vector<int> pathArray; // publicznie dostępna tablica ścieżek
private:
    int minDistance(const std::vector<int>& pathArray, const std::vector<bool>& shortestPathSet) const;
    int numberOfVertices;
    int infinity;
};



#endif //DIJKSTRA_H
