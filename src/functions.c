#include "../include/structs.h"
#include "../include/functions.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

double calculateDistance(City city1, City city2) {
  double dx = city1.x - city2.x;
  double dy = city1.y - city2.y;
  return sqrt(dx * dx + dy * dy);
}

double **initializeGraph(int size) {
  double** graph = malloc(size * sizeof(double));
  for(int i = 0; i < size; i++){
    graph[i] = malloc(size * sizeof(double));
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

int ufFind(int i, int Id[]) {
  while (i != Id[i]) i = Id[i];
    return i; 
}

void ufUnion(int p, int q, int Id[]) {
  int i = ufFind(p, Id);
  int j = ufFind(q, Id);
  Id[i] = j;
}

void sort(Edge *edges, int edgeCount){
  qsort(edges, edgeCount, sizeof(Edge), compareEdges);
}

void printMstHeader(FILE* arq, int dimension){
  fprintf(arq, "NAME: berlin52\n");
  fprintf(arq, "TYPE: MST\n");
  fprintf(arq, "DIMENSION: %d\n", dimension);
  fprintf(arq, "MST_SECTION\n");
}

void printTourHeader(FILE* arq){
  fprintf(arq, "NAME: berlin52\n");
  fprintf(arq, "TYPE: TOUR\n");
  fprintf(arq, "DIMENSION: 52\n");
  fprintf(arq, "TOUR_SECTION\n");
}

void DFS(double **graph, int *visited, int vertex, int dimension, FILE* arq){
  fprintf(arq, "%d\n", vertex + 1);
  visited[vertex] = 1;
  int closestCity;
  double smallest = 9999;
  for(int j = 0; j < dimension; j++){
    if(visited[j] == 0 && graph[vertex][j] <= smallest){  
      smallest = graph[vertex][j];
      closestCity = j;
    }
  }
  if(smallest != 9999)
    DFS(graph, visited, closestCity, dimension, arq);
}