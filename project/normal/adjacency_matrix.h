#ifndef ADJACENCY_MATRIX_H
#define ADJACENCY_MATRIX_H

#include <vector>
#include <random>

class AdjacencyMatrix {
public:
    AdjacencyMatrix(int numberOfVertices);
    std::vector<std::vector<std::vector<int>>> GenerateGraph();
private:
    int RandomInt(int lowerBound, int upperBound);
    std::vector<std::vector<int>> GenerateBaseMatrix(int numberOfVertices);
    std::vector<std::vector<int>> GenerateRandomConnections(const std::vector<std::vector<int>>& baseMatrix);
    std::vector<std::vector<int>> ApplyDensity(const std::vector<std::vector<int>>& baseMatrix);
    std::vector<std::vector<int>> graph;
    std::random_device rd;
    std::mt19937 gen;
    int infinity = 100000;
};


#endif //ADJACENCY_MATRIX_H
