
#include "dijkstra.h"
#include <iostream>

// Konstruktor klasy Dijkstra ustawijący ilość wierzchołków oraz wartość infinity
Dijkstra::Dijkstra(int numberOfVertices) : numberOfVertices(numberOfVertices), infinity(100000) {
}

int Dijkstra::minDistance(const std::vector<int>& pathArray, const std::vector<bool>& shortestPathSet) const {
    int min = infinity, min_index = -1;

    for (int v = 0; v < numberOfVertices; ++v) {
        // Sprawdzenie czy wierzchołek nie należy jeszcze do najkrótszej ścieżki oraz czy ma mniejszą odległość
        if (!shortestPathSet[v] && pathArray[v] <= min) {
            // Aktualizacja minimalnej odległości i indeksu wierzchołka
            min = pathArray[v];
            min_index = v;
        }
    }

    return min_index;
}

void Dijkstra::FindShortestPath(const std::vector<std::vector<std::vector<int>>>& adjList, int srcNode) {
    // Inicjalizacja tablicy przechowującej odległości do wierzchołków
    pathArray.assign(numberOfVertices, infinity);
    // Inicjalizacja zbioru oznaczającego, czy dany wierzchołek należy już do najkrótszej ścieżki
    std::vector<bool> shortestPathSet(numberOfVertices, false);

    pathArray[srcNode] = 0;

    for (int count = 0; count < numberOfVertices - 1; count++) {
        // Wybór wierzchołka o najmniejszej odległości spośród wierzchołków nie należących jeszcze do najkrótszej ścieżki
        int u = minDistance(pathArray, shortestPathSet);
        shortestPathSet[u] = true;

        for (int v = 0; v < numberOfVertices; v++) {
            // Warunek sprawdzający czy sąsiedni wierzchołek nie należy jeszcze do najkrótszej ścieżki oraz czy istnieje krawędź między wierzchołkami
            if (!shortestPathSet[v] && adjList[count][u][v] != infinity &&
                adjList[count][u][v] != 0 && pathArray[u] != infinity &&
                ((pathArray[u] + adjList[count][u][v]) < pathArray[v])) {
                // Aktualizacja odległości do sąsiedniego wierzchołka, jeśli znaleziono krótszą ścieżkę
                pathArray[v] = pathArray[u] + adjList[count][u][v];
            }
        }
    }
}