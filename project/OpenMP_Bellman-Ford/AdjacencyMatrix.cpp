#include "AdjacencyMatrix.h"

AdjacencyMatrixOpenMP::AdjacencyMatrixOpenMP() : gen(rd()) {}

int AdjacencyMatrixOpenMP::RandomInt(int lowerBound, int upperBound) {
    std::uniform_int_distribution<> dis(lowerBound, upperBound);
    return dis(gen);
}

std::vector<std::vector<int>> AdjacencyMatrixOpenMP::GenerateBaseMatrix(int numberOfVertices) {
    std::vector<std::vector<int>> baseMatrix(numberOfVertices, std::vector<int>(numberOfVertices, 0));
    for (int i = 0; i < numberOfVertices; ++i) {
        for (int j = i; j < numberOfVertices; ++j) {
            if (i == j) {
                baseMatrix[i][j] = 0;
            }
            else {
                baseMatrix[i][j] = RandomInt(100, 199); // losowa d³ugoœæ po³¹czeñ
                baseMatrix[j][i] = baseMatrix[i][j];
            }
        }
    }
    return baseMatrix;
}

std::vector<std::vector<std::vector<int>>> AdjacencyMatrixOpenMP::GenerateGraph(int numGraphs, int numberOfVertices) {
    std::vector<std::vector<std::vector<int>>> graphWrapper;
    graphWrapper.reserve(numGraphs);

#pragma omp parallel for shared(graphWrapper) num_threads(4)
    for (int i = 0; i < numGraphs; ++i) {
        std::vector<std::vector<int>> baseMatrix = GenerateBaseMatrix(numberOfVertices);
        std::vector<std::vector<int>> connections = baseMatrix; // U¿yj baseMatrix jako podstawy dla connections

        // Losowo usuñ po³¹czenia
#pragma omp parallel for shared(connections) num_threads(4)
        for (int i = 0; i < connections.size(); ++i) {
            for (int j = i; j < connections.size(); ++j) {
                if (RandomInt(1, 100) > 10 && i != j) {
                    connections[i][j] = infinity; // Brak po³¹czenia
                    connections[j][i] = infinity;
                }
            }
        }

#pragma omp critical
        {
            graphWrapper.push_back(connections);
        }
    }

    return graphWrapper;
}
