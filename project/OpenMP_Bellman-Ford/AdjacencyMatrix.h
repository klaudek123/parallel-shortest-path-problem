#ifndef ADJACENCY_MATRIX_OPENMP_H
#define ADJACENCY_MATRIX_OPENMP_H

#include <vector>
#include <random>
#include <limits>
#include <omp.h>

class AdjacencyMatrixOpenMP {
private:
    std::random_device rd;
    std::mt19937 gen;
    const int infinity = 100000;
    int RandomInt(int lowerBound, int upperBound);

    std::vector<std::vector<int>> GenerateBaseMatrix(int numberOfVertices);

public:
    AdjacencyMatrixOpenMP();

    std::vector<std::vector<std::vector<int>>> GenerateGraph(int numGraphs, int numberOfVertices);
};

#endif // ADJACENCY_MATRIX_OPENMP_H
