#include "adjacency_matrix.h"
#include "dijkstra.h"
#include "bellman_ford.h"
#include "path_printer.h"
#include <chrono>
#include <iostream>
#include <vector>
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
    } else {
        std::cerr << "Błąd: Nie udało się otworzyć pliku" << std::endl;
    }

    return adjMatrix;
}





int main(int argc, char* argv[]) {
    // int firstArg = 25;
    // if (argc > 1) {
    //     try {
    //         firstArg = std::stoi(argv[1]);
    //     } catch (std::invalid_argument& e) {
    //         std::cerr << "Argument" << argv[1] << " must be an integer.";
    //         return 1;
    //     }
    // }

    // int numberOfVertices = firstArg;
    // std::vector<std::string> cities;
    // for (int i = 0; i < numberOfVertices; ++i) {
    //     cities.push_back("Vertex" + std::to_string(i));
    // }

    for (int i = 100; i < 1000; i = i + 100) {
        int numberOfVertices = i;
        int src = 0;
        int des = 3;

        // Wczytanie macierzy sąsiedztwa z pliku
        // std::string filename = "C:\\Users\\klaud\\Desktop\\studia\\sem_6\\przetwarzanie_rownolegle\\project\\normal\\test_adj_matrix.txt";
        // std::vector<std::vector<std::vector<int>>> adjListWrapper = loadAdjacencyMatrixFromFile(filename, numberOfVertices);

        AdjacencyMatrix adj(numberOfVertices);
        std::vector<std::vector<std::vector<int>>> adjListWrapper = adj.GenerateGraph();
        std::cout << std::endl;

        // for (int i = 0; i < numberOfVertices; ++i) {
        //     for (int j = 0; j < numberOfVertices; ++j) {
        //         for (int k = 0; k < numberOfVertices; ++k) {
        //             std::cout << adjListWrapper[i][j][k] << " ";
        //         }
        //         std::cout << std::endl; // Nowa linia po każdym wierszu
        //     }
        //     std::cout << std::endl; // Nowa linia po każdej macierzy
        //     std::cout << std::endl; // Nowa linia po każdej macierzy
        // }


        // // Pomiar czasu dla algorytmu Dijkstry
        // auto startDijkstra = std::chrono::high_resolution_clock::now();
        // Dijkstra dijkstra(numberOfVertices);
        // dijkstra.FindShortestPath(adjListWrapper, src);
        // auto stopDijkstra = std::chrono::high_resolution_clock::now();
        // auto durationDijkstra = std::chrono::duration_cast<std::chrono::microseconds>(stopDijkstra - startDijkstra);
        // std::cout << i << " vertices"<< std::endl;
        // // Wyświetlanie wyników i czasu wykonania algorytmu Dijkstry
        // std::cout << "Results for Dijkstra's Algorithm:"<< std::endl;
        // // PathPrinter::PrintMinPath("Vertex" + std::to_string(src), "Vertex" + std::to_string(des), dijkstra.pathArray, des);
        // std::cout << "Execution time for Dijkstra algorithm: " << durationDijkstra.count() << " microseconds";

        // Pomiar czasu dla algorytmu Bellmana-Forda
        auto startBellmanFord = std::chrono::high_resolution_clock::now();
        BellmanFord bellmanFord(numberOfVertices);
        bellmanFord.FindShortestPath(adjListWrapper);
        auto stopBellmanFord = std::chrono::high_resolution_clock::now();
        auto durationBellmanFord = std::chrono::duration_cast<std::chrono::microseconds>(stopBellmanFord - startBellmanFord);

        // Wyświetlanie wyników i czasu wykonania algorytmu Bellmana-Forda
        std::cout << std::endl << "Results for Bellman-Ford Algorithm:"<< std::endl;
        // PathPrinter::PrintMinPath("Vertex" + std::to_string(src), "Vertex" + std::to_string(des), bellmanFord.pathArray, des);
        std::cout << "Execution time for Bellman-Ford algorithm: " << durationBellmanFord.count() << " microseconds" << std::endl;

    }
    return 0;
}