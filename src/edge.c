#include "../include/edge.h"
#include <stdlib.h>
#include <stdio.h>

// Função auxiliar para realizar a partição durante a ordenação personalizada das arestas (QuickSort personalizado).
int partition(Edge *edges, int lo, int hi) {
    Edge pivot = edges[hi];
    int i = lo - 1;

    for (int j = lo; j < hi; j++) {
        if (edges[j].distance < pivot.distance) {
            i++;
            // Troca as arestas
            Edge temp = edges[i];
            edges[i] = edges[j];
            edges[j] = temp;
        }
    }

    // Troca a posição da aresta pivot
    Edge temp = edges[i + 1];
    edges[i + 1] = edges[hi];
    edges[hi] = temp;

    return i + 1;
}

// Função para realizar a ordenação personalizada das arestas (QuickSort personalizado).
void edgeCustomQuickSort(Edge *edges, int lo, int hi) {
    if (lo < hi) {
        int j = partition(edges, lo, hi);
        edgeCustomQuickSort(edges, lo, j - 1);
        edgeCustomQuickSort(edges, j + 1, hi);
    }
}

// Função para ordenar um array de arestas com base na distância entre as cidades.
void sort(Edge *edges, int edgeCount) {
    edgeCustomQuickSort(edges, 0, edgeCount - 1);
}
