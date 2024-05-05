#include "cuda_runtime.h"
#include "device_launch_parameters.h"
#include "AdjacencyMatrixGenerator.h"
#include <iostream>
#include <chrono>
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



// Funkcja CUDA do wyznaczania najkrótszych ścieżek metodą Dijkstry
__global__
void dijkstraCUDA(const int* adjList, int numberOfVertices, int source, int* pathArray, bool* shortestPathSet) {
    // Identyfikator wątku
    int tid = blockIdx.x * blockDim.x + threadIdx.x;
    // Sprawdzenie czy wątek jest w granicach liczby wierzchołków
    if (tid >= numberOfVertices)
        return;

    // Inicjalizacja wartości najkrótszej ścieżki i zbioru odwiedzonych
    if (tid == source)
        pathArray[tid] = 0;
    else
        pathArray[tid] = INT_MAX;

    shortestPathSet[tid] = false;

    __syncthreads();

    for (int count = 0; count < numberOfVertices - 1; ++count) {
        // Znajdowanie wierzchołka o najmniejszej odległości
        int u;
        int minDistance = INT_MAX;
        for (int v = 0; v < numberOfVertices; ++v) {
            if (!shortestPathSet[v] && pathArray[v] <= minDistance) {
                minDistance = pathArray[v];
                u = v;
            }
        }

        // Oznaczenie wierzchołka jako odwiedzony
        shortestPathSet[u] = true;

        // Aktualizacja odległości dla sąsiednich wierzchołków
        for (int v = 0; v < numberOfVertices; ++v) {
            if (!shortestPathSet[v] && adjList[u * numberOfVertices + v] && pathArray[u] != INT_MAX &&
                pathArray[u] + adjList[u * numberOfVertices + v] < pathArray[v]) {
                pathArray[v] = pathArray[u] + adjList[u * numberOfVertices + v];
            }
        }

        __syncthreads();
    }
}


// Funkcja wywołująca algorytm Dijkstry na urządzeniu CUDA
int* dijkstraParallel(const int* adjList, int numEdges, int numberOfVertices, int source) {
    // Pomiar czasu wykonania
    auto startTime = std::chrono::high_resolution_clock::now();

    // Alokuje pamięć na wynikowe ścieżki i zbiór odwiedzonych wierzchołków na urządzeniu
    int* pathArray = new int[numberOfVertices];
    bool* shortestPathSet = new bool[numberOfVertices];
    int* devPathArray;
    bool* devVisited;
    int* devAdjList;

    cudaMalloc(&devPathArray, sizeof(int) * numberOfVertices);
    cudaMalloc(&devVisited, sizeof(bool) * numberOfVertices);
    cudaMalloc(&devAdjList, sizeof(int) * numberOfVertices * numberOfVertices);

    // Inicjalizacja odległości i zbioru odwiedzonych wierzchołków na hostingu
    for (int i = 0; i < numberOfVertices; ++i) {
        pathArray[i] = INT_MAX;
        shortestPathSet[i] = false;
    }
    pathArray[source] = 0;

    // Kopiowanie danych z hosta do urządzenia
    cudaMemcpy(devPathArray, pathArray, numberOfVertices * sizeof(int), cudaMemcpyHostToDevice);
    cudaMemcpy(devVisited, shortestPathSet, numberOfVertices * sizeof(bool), cudaMemcpyHostToDevice);
    cudaMemcpy(devAdjList, adjList, numberOfVertices * numberOfVertices * sizeof(int), cudaMemcpyHostToDevice);

    // Wywołanie funkcji dijkstraCUDA na urządzeniu
    dijkstraCUDA << <(numberOfVertices + 255) / 256, 256 >> > (devAdjList, numberOfVertices, source, devPathArray, devVisited);

    // Kopiowanie wyników z urządzenia do hosta
    cudaMemcpy(pathArray, devPathArray, numberOfVertices * sizeof(int), cudaMemcpyDeviceToHost);


    // Pomiar czasu wykonania
    auto endTime = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(endTime - startTime).count();

    // Synchronizacja urządzenia
    cudaDeviceSynchronize();

    

    // Wyświetlanie czasu wykonania
    std::cout << "Execution time for CUDA Dijkstra algorithm: " << duration << " microseconds" << std::endl;

    // Zwolnienie pamięci na urządzeniu i hostingu
    cudaFree(devPathArray);
    cudaFree(devVisited);
    cudaFree(devAdjList);
    delete[] shortestPathSet;

    return pathArray; // Zwraca wynikowe ścieżki
}


void PrintMinPath(int* pathArray, int numberOfVertices, int source) {
    std::cout << "Odleglosc od wierzcholka " << source << " do innych wierzcholkow:" << std::endl;

    for (int i = 0; i < numberOfVertices; ++i) {
        if (pathArray[i] == INT_MAX || pathArray[i] == 100000) {
            std::cout << "Unknown ";
        }
        else {
            std::cout << pathArray[i] << " ";
        }
    }
    std::cout << std::endl;

    delete[] pathArray;
}


int main()
{
    for (int i = 100; i < 1000; i = i + 100) {

        int numberOfVertices = i;
        const int adjListSize = numberOfVertices * numberOfVertices * numberOfVertices;
        int* adjList = new int[adjListSize];


        // Generowanie macierzy sąsiedztwa
        AdjacencyMatrixGenerator adj;
        std::vector<std::vector<std::vector<int>>> adjListWrapper = adj.generateGraph(numberOfVertices);

        // Wczytanie macierzy sąsiedztwa z pliku
        //std::string filename = "test_adj_matrix.txt";
        //std::vector<std::vector<std::vector<int>>> adjListWrapper = loadAdjacencyMatrixFromFile(filename, numberOfVertices);


        // Dostosowanie do listy jednowymiarowej
        for (int k = 0; k < numberOfVertices; ++k) {
            for (int i = 0; i < numberOfVertices; ++i) {
                for (int j = 0; j < numberOfVertices; ++j) {
                    adjList[k * numberOfVertices * numberOfVertices + i * numberOfVertices + j] = adjListWrapper[k][i][j];
                }
            }
        }

        std::cout << numberOfVertices << " vertices" << std::endl;
        // Wywołanie algorytmu Dijkstry na GPU
        printf("Results from GPU Dijkstra:\n");
        int* pathArray = dijkstraParallel(adjList, adjListSize, numberOfVertices, 0);
        //PrintMinPath(pathArray, numberOfVertices, 0);

        delete[] adjList;
    }
    return 0;
}
