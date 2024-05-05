#include "AdjacencyMatrixGenerator.h"

AdjacencyMatrixGenerator adj;

AdjacencyMatrixGenerator::AdjacencyMatrixGenerator() : gen(rd()) {}

int AdjacencyMatrixGenerator::RandomInt(int lowerBound, int upperBound) {
    std::uniform_int_distribution<> dis(lowerBound, upperBound);
    return dis(gen);
}

std::vector<std::vector<std::vector<int>>> AdjacencyMatrixGenerator::generateGraph(int numberOfVertices) {
    std::vector<std::vector<std::vector<int>>> adjacency_list_wrapper;


    for (int k = 0; k < numberOfVertices; ++k) {
        std::vector<std::vector<int>> adjacency_list = generateBaseMatrix(numberOfVertices);
        adjacency_list_wrapper.push_back(generateRandomConnections(adjacency_list));
    }

    //std::vector<std::vector<int>> adjacency_list = generateBaseMatrix(numberOfVertices);
    //adjacency_list_wrapper.push_back(generateRandomConnections(adjacency_list));

    //return generateRandomConnections(adjacency_list);
    return adjacency_list_wrapper;
}

std::vector<std::vector<int>> AdjacencyMatrixGenerator::generateBaseMatrix(int numberOfVertices) {
    std::vector<std::vector<int>> baseMatrix(numberOfVertices, std::vector<int>(numberOfVertices, 0));
    for (int i = 0; i < numberOfVertices; ++i) {
        for (int j = i; j < numberOfVertices; ++j) {
            if (i == j) {
                baseMatrix[i][j] = 0;
            }
            else {
                
                baseMatrix[i][j] = adj.RandomInt(100,199); // losowa d³ugoœæ po³¹czeñ
                baseMatrix[j][i] = baseMatrix[i][j];
            }
        }
    }
    return baseMatrix;
}

std::vector<std::vector<int>> AdjacencyMatrixGenerator::generateRandomConnections(const std::vector<std::vector<int>>& baseMatrix) {
    

    std::vector<std::vector<int>> connections = baseMatrix;
    for (int i = 0; i < connections.size(); ++i) {
        for (int j = i + 1; j < connections.size(); ++j) {
            if (adj.RandomInt(1,100) > 10 && i != j) {
                connections[i][j] =  adj.infinity; // Ustaw brak po³¹czenia miêdzy i a j z 50% szans¹
                connections[j][i] = adj.infinity;
            }
        }
    }
    return connections;
}