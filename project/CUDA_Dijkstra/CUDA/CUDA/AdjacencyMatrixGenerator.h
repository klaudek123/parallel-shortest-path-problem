#ifndef ADJACENCY_MATRIX_GENERATOR_H
#define ADJACENCY_MATRIX_GENERATOR_H

#include <vector>
#include <random>
#include <limits>
#include <omp.h>

class AdjacencyMatrixGenerator {
private:
    std::mt19937 gen;
    std::random_device rd;
    const int infinity = 100000;
    int RandomInt(int lowerBound, int upperBound);

    static std::vector<std::vector<int>> generateBaseMatrix(int numberOfVertices);
    static std::vector<std::vector<int>> generateRandomConnections(const std::vector<std::vector<int>>& baseMatrix);

public:
    AdjacencyMatrixGenerator();
    std::vector<std::vector<std::vector<int>>> generateGraph(int numberOfVertices);

};


#endif //ADJACENCY_MATRIX_GENERATOR_H