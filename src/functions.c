#include "../include/functions.h"
#include "../include/structs.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

double calculateDistance(City city1, City city2) {
  // printf("CITY 1 - X: %Lf Y: %Lf\n", city1.x, city1.y);
  // printf("CITY 2 - X: %Lf Y: %Lf\n", city2.x, city2.y);

  double dx = city1.x - city2.x;
  double dy = city1.y - city2.y;
  
  // printf("DX: %Lf DY: %Lf\n", dx, dy);

  double sqrt1 = sqrt(dx * dx + dy * dy);

  return sqrt1;
}

double **initializeGraph(int size) {
  double **graph = malloc(size * sizeof(double));
  for (int i = 0; i < size; i++) {
    graph[i] = malloc(size * sizeof(long double));
  }
  return graph;
}

int compareEdges(const void *a, const void *b) {
  if ((*(Edge *)a).distance < (*(Edge *)b).distance)
    return -1;
  if ((*(Edge *)a).distance > (*(Edge *)b).distance)
    return 1;
  return 0;
}

void ufInit(int size, int Id[]){
  int N = size;
  for (int i = 0; i < N; i++) {
    Id[i] = i;
  }
}

int ufFind(int i, int Id[], int dimension) {
  while (i != Id[i]) i = Id[i];
  return i; 
}


void ufUnion(int p, int q, int Id[], int dimension) {
  int i = ufFind(p, Id, dimension);
  int j = ufFind(q, Id, dimension);
  Id[i] = j;
}

void sort(Edge *edges, int edgeCount) {
  qsort(edges, edgeCount, sizeof(Edge), compareEdges);
}

void printMstHeader(FILE *arq, char *fileName, int dimension) {
  fprintf(arq, "NAME: %s\n", fileName);
  fprintf(arq, "TYPE: MST\n");
  fprintf(arq, "DIMENSION: %d\n", dimension);
  fprintf(arq, "MST_SECTION\n");
}

void printTourHeader(FILE *arq, char *fileName, int dimension) {
  fprintf(arq, "NAME: %s\n", fileName);
  fprintf(arq, "TYPE: TOUR\n");
  fprintf(arq, "DIMENSION: %d\n", dimension);
  fprintf(arq, "TOUR_SECTION\n");
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
  if (smallest != 9999)
    DFS(graph, visited, closestCity, dimension, arq);
}