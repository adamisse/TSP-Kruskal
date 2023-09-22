#ifndef GRAPH_H
#define GRAPH_H

#include <stdio.h>

// Inicializa uma matriz de adjacência para representar um grafo com o número especificado de vértices.
double **initializeGraph(int size);

// Implementa a busca em profundidade (DFS) para percorrer o grafo e registrar o tour no arquivo especificado.
void DFS(double **graph, int *visited, int vertex, int dimension, FILE *tourFile);

// Libera a memória alocada para a matriz de adjacência do grafo.
void freeGraph(double **graph, int size);

#endif
