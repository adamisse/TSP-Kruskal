#include "../include/graph.h"
#include <stdlib.h>
#include <stdio.h>
#include <float.h>

double **initializeGraph(int size) {
  double **graph = malloc(size * sizeof(double));
  for (int i = 0; i < size; i++) {
    graph[i] = malloc(size * sizeof(long double));
  }
  return graph;
}

void DFS(double **graph, int *visited, int vertex, int dimension, FILE *arq) {
  fprintf(arq, "%d\n", vertex + 1); // Registra o vértice atual no arquivo
  visited[vertex] = 1; // Marca o vértice como visitado
  int closestCity;
  double smallest = DBL_MAX; // Valor inicial arbitrário para a menor distância

  // Encontra a cidade mais próxima que ainda não foi visitada
  for (int j = 0; j < dimension; j++) {
    if (visited[j] == 0 && graph[vertex][j] <= smallest) {
      smallest = graph[vertex][j];
      closestCity = j;
    }
  }

  // Se encontrar uma cidade mais próxima, realiza a chamada recursiva do DFS
  if (smallest != DBL_MAX) {
    DFS(graph, visited, closestCity, dimension, arq);
  }
}

void freeGraph(double **graph, int size) {
  for (int i = 0; i < size; i++) {
    free(graph[i]);
  }
  
  free(graph);
}