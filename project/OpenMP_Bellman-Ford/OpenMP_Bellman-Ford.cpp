#include <iostream>
#include <omp.h>
#include "AdjacencyMatrix.h"
#include "BellmanFord.h"
#include <string>
#include <fstream>
#include <sstream>

// Funkcja do wczytywania macierzy sąsiedztwa z pliku tekstowegostd::vector<std::vector<std::vector<int>>> loadAdjacencyMatrixFromFile(const std::string& filename, int numberOfVertices) {
std::vector<std::vector<std::vector<int>>> loadAdjacencyMatrixFromFile(const std::string& filename, int numberOfVertices) {
    std::ifstream file(filename);
    std::vector<std::vector<std::vector<int>>> adjMatrix;

    if (file.is_open()) {
        adjMatrix.resize(numberOfVertices, std::vector<std::vector<int>>(numberOfVertices, std::vector<int>(numberOfVertices)));

        int value;
        std::string line;
        for (int k = 0; k < numberOfVertices; ++k) {
            for (int i = 0; i < numberOfVertices; ++i) {
                std::getline(file, line);
                std::istringstream iss(line);
                for (int j = 0; j < numberOfVertices; ++j) {
                    if (!(iss >> value)) {
                        std::cerr << "Błąd: Nie udało się wczytać wartości z pliku" << std::endl;
                        return adjMatrix;
                    }
                    adjMatrix[k][i][j] = value;
                }
            }
            // Pominięcie dodatkowej linii nowego wiersza
            std::getline(file, line);
            std::getline(file, line);
        }

        file.close();
    }
    else {
        std::cerr << "Błąd: Nie udało się otworzyć pliku" << std::endl;
    }

    return adjMatrix;
}




int main() {
    for (int i = 100; i < 1000; i = i + 100) {

        int numberOfVertices = i;

        AdjacencyMatrixOpenMP adjMatrixGenerator;
        std::vector<std::vector<std::vector<int>>> adjListWrapper = adjMatrixGenerator.GenerateGraph(numberOfVertices, numberOfVertices);
    
        // Wczytanie macierzy sąsiedztwa z pliku
        /*std::string filename = "test_adj_matrix.txt";
        std::vector<std::vector<std::vector<int>>> adjListWrapper = loadAdjacencyMatrixFromFile(filename, numberOfVertices);*/

        BellmanFord bellmanFord(numberOfVertices);

        std::cout << i << " vertices" << std::endl;
        // Przetestuj algorytm Bellmana-Forda na wygenerowanych grafach
        std::cout << "Results from CPU Bellman-Ford"<< std::endl;
        bellmanFord.FindShortestPath(adjListWrapper);
        //bellmanFord.PrintShortestPaths();
        std::cout << std::endl;

    }

    return 0;
}