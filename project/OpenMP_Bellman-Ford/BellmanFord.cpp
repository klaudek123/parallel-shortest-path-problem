#include "BellmanFord.h"
#include <iostream>
#include <chrono>

// Konstruktor klasy BellmanFord
BellmanFord::BellmanFord(int numberOfVertices) : numberOfVertices(numberOfVertices) {
}


void BellmanFord::FindShortestPath(const std::vector<std::vector<std::vector<int>>>& adjList) {
    // Inicjalizacja tablicy odleg³oœci
    pathArray.assign(numberOfVertices, 0);

    // Przypisanie odleg³oœci z wierzcho³ka Ÿród³owego do tablicy
    for (int i = 0; i < numberOfVertices; ++i) {
        pathArray[i] = adjList[0][0][i];
    }

    // Pomiar czasu rozpoczêcia algorytmu
    auto start = std::chrono::high_resolution_clock::now();

    // Iteracja w celu relaksacji krawêdzi i aktualizacji odleg³oœci
    for (int k = 1; k < numberOfVertices - 1; ++k) {
        // Rozpoczêcie równoleg³ej iteracji po wierzcho³kach i
        #pragma omp parallel for
        for (int i = 1; i < numberOfVertices; ++i) {
            // Rozpoczêcie równoleg³ej iteracji po wierzcho³kach j
            #pragma omp parallel for
            for (int j = 0; j < numberOfVertices; ++j) {
                int n;
                if (pathArray[j] + adjList[k][j][i] > infinity) {
                    n = infinity;
                }
                else {
                    n = pathArray[j] + adjList[k][j][i];
                }
                // Aktualizacja najkrótszej odleg³oœci do wierzcho³ka i
                pathArray[i] = std::min(pathArray[i], n);
            }
        }
    }

    // Pomiar czasu zakoñczenia algorytmu
    auto end = std::chrono::high_resolution_clock::now();
    // Obliczenie czasu wykonania w mikrosekundach
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
    std::cout << "Execution time for OpenMP Bellman-Ford algorithm: " << duration << " microseconds" << std::endl;
}

void BellmanFord::PrintShortestPaths() const {
    std::cout << "Shortest distance from vertex 0 to vertices: " << std::endl;
    for (int i = 0; i < numberOfVertices; ++i) {
        if (pathArray[i] == infinity) {
            std::cout << "Unknown" << " ";
        }
        else {
            std::cout << pathArray[i] << " ";
        }
    }
}