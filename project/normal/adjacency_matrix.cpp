#include "adjacency_matrix.h"

// Konstruktor klasy AdjacencyMatrix
AdjacencyMatrix::AdjacencyMatrix(int numberOfVertices) : gen(rd()) {
    // Inicjalizacja macierzy sąsiedztwa
    graph.resize(numberOfVertices, std::vector<int>(numberOfVertices, 0));
}

// Metoda generująca losową liczbę całkowitą z określonego przedziału
int AdjacencyMatrix::RandomInt(int lowerBound, int upperBound) {
    std::uniform_int_distribution<> dis(lowerBound, upperBound);
    return dis(gen);
}

// Metoda generująca bazową macierz połączeń
std::vector<std::vector<int>> AdjacencyMatrix::GenerateBaseMatrix(int numberOfVertices) {
    std::vector<std::vector<int>> baseMatrix(numberOfVertices, std::vector<int>(numberOfVertices, 0));
    for (int i = 0; i < numberOfVertices; ++i) {
        for (int j = i; j < numberOfVertices; ++j) {
            if (i == j) {
                baseMatrix[i][j] = infinity; // Brak cyklu ze sobą
            } else {
                baseMatrix[i][j] = RandomInt(100, 199); // Losowa długość połączeń
                baseMatrix[j][i] = baseMatrix[i][j];
            }
        }
    }
    return baseMatrix;
}

// Metoda generująca losowe połączenia z zadanym poziomem gęstości
std::vector<std::vector<int>> AdjacencyMatrix::GenerateRandomConnections(const std::vector<std::vector<int>>& baseMatrix) {
    std::vector<std::vector<int>> connections = baseMatrix;
    for (int i = 0; i < connections.size(); ++i) {
        for (int j = i; j < connections.size(); ++j) {
            // Warunek na wprowadzenie braku połączenia z zadanym poziomem gęstości
            if (RandomInt(1, 100) > 10 && i != j) {
                connections[i][j] = infinity; // Brak połączenia między wierzchołkami
                connections[j][i] = connections[i][j];
            }
        }
    }
    return connections;
}

// Metoda aplikująca gęstość na bazową macierz połączeń
std::vector<std::vector<int>> AdjacencyMatrix::ApplyDensity(const std::vector<std::vector<int>>& baseMatrix) {
    return GenerateRandomConnections(baseMatrix);
}

// Metoda generująca graf poprzez aplikację gęstości na bazową macierz połączeń
std::vector<std::vector<std::vector<int>>> AdjacencyMatrix::GenerateGraph() {
    std::vector<std::vector<std::vector<int>>> graphWrapper;
    for (int i = 0; i < graph.size(); ++i) {
        std::vector<std::vector<int>> baseMatrix = GenerateBaseMatrix(graph.size());
        graph = ApplyDensity(baseMatrix);
        graphWrapper.push_back(graph);
    }

    return graphWrapper;
}
