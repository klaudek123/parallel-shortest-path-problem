#include "bellman_ford.h"
#include <iostream>

// Konstruktor klasy BellmanFord
BellmanFord::BellmanFord(int numberOfVertices) : numberOfVertices(numberOfVertices), infinity(100000) {}

// Metoda znajdująca najkrótszą ścieżkę za pomocą algorytmu Bellmana-Forda
void BellmanFord::FindShortestPath(const std::vector<std::vector<std::vector<int>>>& adjList) {
    // Inicjalizacja tablicy przechowującej długości najkrótszych ścieżek
    pathArray.assign(numberOfVertices, 0);

    // Inicjalizacja tablicy długości najkrótszych ścieżek na podstawie pierwszej warstwy listy sąsiedztwa
    for (int i = 0; i < numberOfVertices; ++i) {
        pathArray[i] = adjList[0][0][i];
    }

    for (int k = 1; k < numberOfVertices - 1; ++k) {
        for (int i = 1; i < numberOfVertices; ++i) {
            for (int j = 0; j < numberOfVertices; ++j) {
                int n;
                // Sprawdzenie czy suma długości ścieżki do sąsiada i długości krawędzi jest większa niż nieskończoność
                if (pathArray[j] + adjList[k][j][i] > infinity) {
                    n = infinity; // Jeśli tak, przypisz nieskończoność
                } else {
                    n = pathArray[j] + adjList[k][j][i]; // W przeciwnym razie oblicz sumę
                }
                // Aktualizacja długości najkrótszej ścieżki do wierzchołka i
                pathArray[i] = std::min(pathArray[i], n);
            }
        }
    }
}
