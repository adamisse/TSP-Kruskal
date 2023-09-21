#include "structs.h"
#include "functions.h"
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

DisjointSet *initializeSet(int size) {
  DisjointSet *set = (DisjointSet *)malloc(sizeof(DisjointSet));
  set->parent = (int *)malloc(size * sizeof(int));
  for (int i = 0; i < size; i++) {
    set->parent[i] = i;
  }
  return set;
}

int compareEdges(const void *a, const void *b) {
  if ((*(Edge *)a).distance < (*(Edge *)b).distance)
    return -1;
  if ((*(Edge *)a).distance > (*(Edge *)b).distance)
    return 1;
  return 0;
}

int find(DisjointSet *set, int element) {
  if (set->parent[element] != element) {
    set->parent[element] = find(set, set->parent[element]);
  }
  return set->parent[element];
}

void unionSets(DisjointSet *set, int element1, int element2) {
  int root1 = find(set, element1);
  int root2 = find(set, element2);
  if (root1 != root2) {
    set->parent[root1] = root2;
  }
}

void freeDisjoint(DisjointSet *set){
  free(set->parent);
}

void sort(Edge *edges, int edgeCount){
  qsort(edges, edgeCount, sizeof(Edge), compareEdges);
}

void DFS(double **graph, int *visited, int vertex, int dimension){
  printf("visited %d\n", vertex + 1);
  visited[vertex] = 1;
  int closestCity;
  double smallest = 9999;
  for(int j = 0; j < dimension; j++){
    if(visited[j] == 0 && graph[vertex][j] <= smallest){  
      smallest = graph[vertex][j];
      closestCity = j;
      //printf("new closest: %d\nnew smallest: %.0lf\n", closestCity + 1, smallest);
    }
  }
  if(smallest != 9999)
    DFS(graph, visited, closestCity, dimension);
}