#include "BellmanFord.h"
#include <iostream>
#include <chrono>

// Konstruktor klasy BellmanFord
BellmanFord::BellmanFord(int numberOfVertices) : numberOfVertices(numberOfVertices) {
}


void BellmanFord::FindShortestPath(const std::vector<std::vector<std::vector<int>>>& adjList) {
    // Inicjalizacja tablicy odleg�o�ci
    pathArray.assign(numberOfVertices, 0);

    // Przypisanie odleg�o�ci z wierzcho�ka �r�d�owego do tablicy
    for (int i = 0; i < numberOfVertices; ++i) {
        pathArray[i] = adjList[0][0][i];
    }

    // Pomiar czasu rozpocz�cia algorytmu
    auto start = std::chrono::high_resolution_clock::now();

    // Iteracja w celu relaksacji kraw�dzi i aktualizacji odleg�o�ci
    for (int k = 1; k < numberOfVertices - 1; ++k) {
        // Rozpocz�cie r�wnoleg�ej iteracji po wierzcho�kach i
        #pragma omp parallel for
        for (int i = 1; i < numberOfVertices; ++i) {
            // Rozpocz�cie r�wnoleg�ej iteracji po wierzcho�kach j
            #pragma omp parallel for
            for (int j = 0; j < numberOfVertices; ++j) {
                int n;
                if (pathArray[j] + adjList[k][j][i] > infinity) {
                    n = infinity;
                }
                else {
                    n = pathArray[j] + adjList[k][j][i];
                }
                // Aktualizacja najkr�tszej odleg�o�ci do wierzcho�ka i
                pathArray[i] = std::min(pathArray[i], n);
            }
        }
    }

    // Pomiar czasu zako�czenia algorytmu
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