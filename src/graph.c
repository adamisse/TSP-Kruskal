#include "../include/graph.h"
#include <stdlib.h>
#include <stdio.h>

double **initializeGraph(int size) {
  double **graph = malloc(size * sizeof(double));
  for (int i = 0; i < size; i++) {
    graph[i] = malloc(size * sizeof(long double));
  }
  return graph;
}

void DFS(double **graph, int *visited, int vertex, int dimension, FILE *arq) {
  fprintf(arq, "%d\n", vertex + 1);
  visited[vertex] = 1;
  int closestCity;
  double smallest = 9999;
  for (int j = 0; j < dimension; j++) {
    if (visited[j] == 0 && graph[vertex][j] <= smallest) {
      smallest = graph[vertex][j];
      closestCity = j;
    }
  }
  if (smallest != 9999){
    DFS(graph, visited, closestCity, dimension, arq);
  }
}

void freeGraph(double **graph, int size) {
  for (int i = 0; i < size; i++) {
    free(graph[i]);
  }
  
  free(graph);
}