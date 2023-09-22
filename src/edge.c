#include "../include/edge.h"
#include <stdlib.h>
#include <stdio.h>

// Função de particionamento para o QuickSort
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

    // Troca o pivô
    Edge temp = edges[i + 1];
    edges[i + 1] = edges[hi];
    edges[hi] = temp;

    return i + 1;
}

// Função QuickSort para ordenar as arestas
void edgeCustomQuickSort(Edge *edges, int lo, int hi) {
    if (lo < hi) {
        int j = partition(edges, lo, hi);
        edgeCustomQuickSort(edges, lo, j - 1);
        edgeCustomQuickSort(edges, j + 1, hi);
    }
}

// Função para chamar o QuickSort e ordenar as arestas
void sort(Edge *edges, int edgeCount) {
    // Chame o QuickSort para ordenar as arestas
    edgeCustomQuickSort(edges, 0, edgeCount - 1);
}